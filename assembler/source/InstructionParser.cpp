#include "InstructionParser.hpp"

#include <iostream>
#include <regex>
#include <utility>

#include "ImmediateParser.hpp"
#include "MemoryDirectParser.hpp"
#include "RegisterDirectParser.hpp"
#include "RegisterIndirectOffsetParser.hpp"
#include "RegisterIndirectParser.hpp"

parsers::InstructionParser::InstructionParser(std::shared_ptr<assembler::SymbolTable> symbol_table,
                                              std::shared_ptr<assembler::ObjectCodeArray> object_code)
    : symbol_table_(std::move(symbol_table)), object_code_(std::move(object_code))
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
        std::cout << "INSTRUCTION 0:'" << statement << "'" << match[1].str() << "\n";

        return nullptr;
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

        return nullptr;
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

        return nullptr;
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
