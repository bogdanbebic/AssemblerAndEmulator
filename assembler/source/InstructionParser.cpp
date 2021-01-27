#include "InstructionParser.hpp"

#include <iostream>
#include <map>
#include <regex>
#include <utility>

#include "ImmediateParser.hpp"
#include "MemoryDirectParser.hpp"
#include "RegisterDirectParser.hpp"
#include "RegisterIndirectOffsetParser.hpp"
#include "RegisterIndirectParser.hpp"

#include "ObjectCodeArray.hpp"

parsers::InstructionParser::InstructionParser(
    std::shared_ptr<assembler::SymbolTable> symbol_table,
    std::shared_ptr<assembler::ObjectCodeArray> object_code,
    std::shared_ptr<assembler::RelocationTable> relocation_table)
    : symbol_table_(std::move(symbol_table))
    , object_code_(std::move(object_code))
    , relocation_table_(std::move(relocation_table))
{
    // initialize operand parsing chain

    auto immediate_parser = std::make_shared<ImmediateParser>(this->symbol_table_);
    auto memory_direct_parser = std::make_shared<MemoryDirectParser>(this->symbol_table_);
    auto register_direct_parser   = std::make_shared<RegisterDirectParser>();
    auto register_indirect_parser = std::make_shared<RegisterIndirectParser>();
    auto register_indirect_offset_parser =
        std::make_shared<RegisterIndirectOffsetParser>(this->symbol_table_);

    register_indirect_parser->set_next(register_indirect_offset_parser);
    register_direct_parser->set_next(register_indirect_parser);
    memory_direct_parser->set_next(register_direct_parser);
    immediate_parser->set_next(memory_direct_parser);

    this->operand_parser_chain_ = immediate_parser;
}

std::shared_ptr<statements::Statement> parsers::InstructionParser::parse(std::string statement)
{
    if (!this->can_parse(statement))
    {
        return StatementParser::parse(statement);
    }

    const std::regex zero_operand_regex{ "^(halt"
                                         "|iret"
                                         "|ret)"
                                         "\\s*$" };

    const std::regex one_operand_regex{ "^((int"
                                        "|call"
                                        "|jmp"
                                        "|jeq"
                                        "|jne"
                                        "|jgt"
                                        "|push"
                                        "|pop)"
                                        "[bw]?)"
                                        "\\s+([^,\\s]+)\\s*$" };

    const std::regex two_operand_regex{ "^((xchg"
                                        "|mov"
                                        "|add"
                                        "|sub"
                                        "|mul"
                                        "|div"
                                        "|cmp"
                                        "|not"
                                        "|and"
                                        "|or"
                                        "|xor"
                                        "|test"
                                        "|shl"
                                        "|shr)"
                                        "[bw]?)"
                                        "\\s+([^,\\s]+)\\s*,\\s*([^,\\s]+)\\s*$" };

    std::smatch match;
    if (std::regex_match(statement, match, zero_operand_regex))
    {
        std::string mnemonic = match[1].str();
        std::cout << "INSTRUCTION 0:'" << statement << "'" << mnemonic << "\n";
        this->object_code_->push_back_byte(to_object_code(mnemonic));
        return std::make_shared<statements::Statement>(1, false);
    }

    if (std::regex_match(statement, match, one_operand_regex))
    {
        constexpr char DEFAULT_SIZE_OPERAND_SPECIFIER = 'w';

        std::string mnemonic       = match[1].str();
        std::string short_mnemonic = match[2].str();
        if (short_mnemonic == mnemonic)
        {
            mnemonic += DEFAULT_SIZE_OPERAND_SPECIFIER;
        }

        char operand_size_specifier = mnemonic.back();
        std::cout << "INSTRUCTION 1:'" << statement << "'" << mnemonic << "\n";

        std::string operand0_str = match[3].str();
        std::cout << "Operand0:'" << operand0_str << "'\n";
        auto operand0 = is_jump_instruction(statement)
                            ? this->operand_parser_chain_->parse_jump_instruction(operand0_str)
                            : this->operand_parser_chain_->parse(operand0_str);

        if (operand0 == nullptr)
        {
            throw std::invalid_argument{ "Invalid operand for instruction: " + statement };
        }

        if (operand_size_specifier == 'w' && operand0->low_high_byte_exists)
        {
            throw std::invalid_argument{ "Invalid operand - operand size mismatch for instruction: " +
                                         statement };
        }

        size_t location_counter_increment = 1;
        this->object_code_->push_back_byte(to_object_code(short_mnemonic, operand_size_specifier));

        size_t operand_size = operand_size_specifier == 'b' ? 1 : 2;
        location_counter_increment += this->add_operand_object_code(operand0, operand_size);
        return std::make_shared<statements::Statement>(location_counter_increment, false);
    }

    if (std::regex_match(statement, match, two_operand_regex))
    {
        constexpr char DEFAULT_SIZE_OPERAND_SPECIFIER = 'w';

        std::string mnemonic       = match[1].str();
        std::string short_mnemonic = match[2].str();
        if (short_mnemonic == mnemonic)
        {
            mnemonic += DEFAULT_SIZE_OPERAND_SPECIFIER;
        }

        char operand_size_specifier = mnemonic.back();
        std::cout << "INSTRUCTION 2:'" << statement << "'" << mnemonic << "\n";

        std::string operand0_str = match[3].str();
        std::string operand1_str = match[4].str();
        std::cout << "Operand0:'" << operand0_str << "'\n";
        std::cout << "Operand1:'" << operand1_str << "'\n";
        auto operand0 = is_jump_instruction(statement)
                            ? this->operand_parser_chain_->parse_jump_instruction(operand0_str)
                            : this->operand_parser_chain_->parse(operand0_str);
        auto operand1 = is_jump_instruction(statement)
                            ? this->operand_parser_chain_->parse_jump_instruction(operand1_str)
                            : this->operand_parser_chain_->parse(operand1_str);

        if (operand0 == nullptr && operand1 == nullptr)
        {
            throw std::invalid_argument{ "Invalid operands for instruction: " + statement };
        }

        if (operand_size_specifier == 'w' &&
            (operand0->low_high_byte_exists || operand1->low_high_byte_exists))
        {
            throw std::invalid_argument{ "Invalid operand - operand size mismatch for instruction: " +
                                         statement };
        }

        size_t location_counter_increment = 1;
        this->object_code_->push_back_byte(to_object_code(short_mnemonic, operand_size_specifier));

        size_t operand_size = operand_size_specifier == 'b' ? 1 : 2;
        location_counter_increment += this->add_operand_object_code(operand0, operand_size);
        location_counter_increment += this->add_operand_object_code(operand1, operand_size);

        return std::make_shared<statements::Statement>(location_counter_increment, false);
    }

    throw std::invalid_argument{ "Invalid number of operands for instruction: " + statement };
}

bool parsers::InstructionParser::is_jump_instruction(const std::string &statement)
{
    const std::regex jump_instructions_regex{ "^(int"
                                              "|call"
                                              "|jmp"
                                              "|jeq"
                                              "|jne"
                                              "|jgt)"
                                              ".*$" };

    return std::regex_match(statement, jump_instructions_regex);
}

uint8_t parsers::InstructionParser::to_object_code(const std::string &mnemonic, char size_char)
{
    std::map<std::string, uint8_t> mnemonic_to_op_code = {
        { "halt", 0 }, { "iret", 1 }, { "ret", 2 },   { "int", 3 },
        { "call", 4 }, { "jmp", 5 },  { "jeq", 6 },   { "jne", 7 },
        { "jgt", 8 },  { "push", 9 }, { "pop", 10 },  { "xchg", 11 },
        { "mov", 12 }, { "add", 13 }, { "sub", 14 },  { "mul", 15 },
        { "div", 16 }, { "cmp", 17 }, { "not", 18 },  { "and", 19 },
        { "or", 20 },  { "xor", 21 }, { "test", 22 }, { "shl", 23 },
        { "shr", 24 },
    };
    uint8_t op_code = mnemonic_to_op_code[mnemonic];
    uint8_t size    = size_char == 'b' ? 0 : 1;
    return (op_code << 3) | (size << 2);
}

bool parsers::InstructionParser::can_parse(const std::string &statement) const
{
    const std::regex instructions_regex{ "^(halt"
                                         "|iret"
                                         "|ret"
                                         "|int"
                                         "|call"
                                         "|jmp"
                                         "|jeq"
                                         "|jne"
                                         "|jgt"
                                         "|push"
                                         "|pop"
                                         "|xchg"
                                         "|mov"
                                         "|add"
                                         "|sub"
                                         "|mul"
                                         "|div"
                                         "|cmp"
                                         "|not"
                                         "|and"
                                         "|or"
                                         "|xor"
                                         "|test"
                                         "|shl"
                                         "|shr)"
                                         ".*$" };

    return std::regex_match(statement, instructions_regex);
}

size_t parsers::InstructionParser::add_operand_object_code(
    const std::shared_ptr<statement::operand_t> &operand, size_t operand_size)
{
    uint8_t op_descr = (operand->addressing_mode << 5) |
                       (operand->register_index << 1) | operand->low_high_byte;
    this->object_code_->push_back_byte(op_descr);
    size_t ret = 1;

    if (operand->relocation != nullptr &&
        (operand->addressing_mode == statement::MEMORY_DIRECT ||
         operand->addressing_mode == statement::REGISTER_INDIRECT_OFFSET))
    {
        operand->relocation->offset = this->object_code_->size();
        this->relocation_table_->insert(*operand->relocation);
    }

    if (operand->addressing_mode == statement::IMMEDIATE ||
        operand->addressing_mode == statement::MEMORY_DIRECT ||
        operand->addressing_mode == statement::REGISTER_INDIRECT_OFFSET)
    {
        for (size_t i = 0; i < operand_size; i++)
        {
            this->object_code_->push_back_byte(operand->operand[i]);
            ret += 1;
        }
    }

    return ret;
}
