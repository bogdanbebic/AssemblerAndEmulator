#include "Parser.h"

#include <string>
#include <sstream>

#include "ParsingException.h"

#include "AssemblyDirectiveParser.h"
#include "DataDefinitionParser.h"
#include "InstructionParser.h"

parsers::Parser::Parser()
{
	auto assembly_directive_parser = std::make_shared<AssemblyDirectiveParser>(this->section_table_, this->symbol_table_);
	auto data_definition_parser = std::make_shared<DataDefinitionParser>(this->object_code_, this->symbol_table_);
	auto instruction_parser = std::make_shared<InstructionParser>(this->symbol_table_, this->object_code_);

	data_definition_parser->set_next(instruction_parser);
	assembly_directive_parser->set_next(data_definition_parser);
	this->statement_parser_chain_ = assembly_directive_parser;
}

void parsers::Parser::parse(std::istream &is)
{
	std::string line;
	is >> std::ws;
	while (std::getline(is, line))
	{
		try
		{
			bool is_end = this->parse_line(line);
			if (is_end)
			{
				this->section_table_->update_section_size(this->current_section_name_, this->line_counter_);
				break;
			}
		}
		catch (std::exception &exception)
		{
			// TODO: LOG error
			std::cerr << exception.what() << "\n";
		}

		is >> std::ws;
	}
}

std::stringstream parsers::Parser::to_school_elf() const
{
	std::stringstream ret;
	ret << this->symbol_table_->to_school_elf().str()
		<< this->section_table_->to_school_elf().str()
		<< this->object_code_->to_school_elf().str();
	return ret;
}

bool parsers::Parser::parse_line(const std::string& line)
{
	std::string line_without_comments = this->line_comment_stripper_.strip_line_comment(line);
	std::string statement_line = this->label_parser_.parse(line_without_comments, this->current_section_index_, this->line_counter_);
	if (this->statement_parser_chain_ == nullptr)
	{
		return false;
	}
	
	const std::shared_ptr<statements::Statement> statement = this->statement_parser_chain_->parse(statement_line);
	if (statement != nullptr)
	{
		this->line_counter_ += statement->location_counter_increment();
		std::cout << "INCREMENT LC:" << statement_line << "\n";
		if (statement->is_section_end())
		{
			this->section_table_->update_section_size(this->current_section_name_, this->line_counter_);
			this->current_section_index_++;
			this->current_section_name_ = statement->next_section();
			this->line_counter_ = 0;
		}
		
		return statement->is_end();
	}

	return false;
}