#include <boost/test/unit_test.hpp>

#include "RegisterIndirectParser.hpp"

#include <memory>

struct RegisterIndirectParserFixture
{
    std::unique_ptr<parsers::RegisterIndirectParser> reg_ind_parser =
        std::make_unique<parsers::RegisterIndirectParser>();
    void test_equal(statement::operand_t expected, statement::operand_t actual)
    {
        BOOST_TEST(expected.addressing_mode == actual.addressing_mode);
        BOOST_TEST(expected.register_index == actual.register_index);
        BOOST_TEST(expected.operand == actual.operand); // element-wise compare
    }
};

BOOST_FIXTURE_TEST_SUITE(TestRegisterIndirectParser, RegisterIndirectParserFixture)

BOOST_AUTO_TEST_CASE(empty_string)
{
    auto res = reg_ind_parser->parse("");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(sp)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT, 6, { 0, 0 } };
    auto res = reg_ind_parser->parse("(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_parser->parse("*(%sp)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT, 7, { 0, 0 } };
    auto res = reg_ind_parser->parse("(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_parser->parse("*(%pc)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT, 0xF, { 0, 0 } };
    auto res = reg_ind_parser->parse("(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_parser->parse("*(%psw)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected{ statement::REGISTER_INDIRECT, i, { 0, 0 } };

        std::string operand = "(%r" + std::to_string(i) + ")";
        auto res            = reg_ind_parser->parse(operand);
        BOOST_TEST(res != nullptr);
        test_equal(expected, *res);

        std::string operand_asterisk = "*(%r" + std::to_string(i) + ")";
        res                          = reg_ind_parser->parse(operand_asterisk);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(sp_jump)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT, 6, { 0, 0 } };
    auto res = reg_ind_parser->parse_jump_instruction("*(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_parser->parse_jump_instruction("(%sp)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc_jump)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT, 7, { 0, 0 } };
    auto res = reg_ind_parser->parse_jump_instruction("*(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_parser->parse_jump_instruction("(%pc)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw_jump)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT, 0xF, { 0, 0 } };
    auto res = reg_ind_parser->parse_jump_instruction("*(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_parser->parse_jump_instruction("(%psw)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index_jump)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected{ statement::REGISTER_INDIRECT, i, { 0, 0 } };

        std::string operand_asterisk = "*(%r" + std::to_string(i) + ")";
        auto res = reg_ind_parser->parse_jump_instruction(operand_asterisk);
        BOOST_TEST(res != nullptr);
        test_equal(expected, *res);

        std::string operand = "(%r" + std::to_string(i) + ")";
        res                 = reg_ind_parser->parse_jump_instruction(operand);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(r_index_out_of_range)
{
    auto res = reg_ind_parser->parse("(%r9)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(random_string)
{
    auto res = reg_ind_parser->parse("(%rx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_parser->parse("(%spx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_parser->parse("(%pcx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_parser->parse("(%pswx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_parser->parse("(gibberish_string)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
