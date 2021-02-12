#include <boost/test/unit_test.hpp>

#include "ImmediateParser.hpp"
#include "SymbolTable.hpp"

#include <memory>

struct ImmediateParserFixture
{
    std::unique_ptr<parsers::ImmediateParser> immediate_parser =
        std::make_unique<parsers::ImmediateParser>(
            std::make_shared<assembler::SymbolTable>());
    void test_equal(statement::operand_t expected, statement::operand_t actual)
    {
        BOOST_TEST(expected.addressing_mode == actual.addressing_mode);
        BOOST_TEST(expected.register_index == actual.register_index);
        BOOST_TEST(expected.operand == actual.operand); // element-wise compare
    }
};

BOOST_FIXTURE_TEST_SUITE(TestImmediateParser, ImmediateParserFixture)

BOOST_AUTO_TEST_CASE(empty_string)
{
    auto res = immediate_parser->parse("");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(gibberish_operand)
{
    auto res = immediate_parser->parse("%gibberish");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("%rx");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("%spx");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("%pcx");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("%pswx");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("gibberish*");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("rx*");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("spx*");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("pcx*");
    BOOST_TEST(res == nullptr);

    res = immediate_parser->parse("pswx*");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(literals)
{
    statement::operand_t expected{ statement::IMMEDIATE, 0, { 0, 0 } };
    auto res = immediate_parser->parse("$0");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 5, 0 } };
    res      = immediate_parser->parse("$5");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 022, 0 } };
    res      = immediate_parser->parse("$022");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0xf, 0 } };
    res      = immediate_parser->parse("$0xf");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    // Literals in immediate parsing cannot be chars or negative integers!
    /*
    expected = { statement::IMMEDIATE, 0, { 'a', 0 } };
    res = immediate_parser->parse("$'a'");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0xff, 0xff } };
    res = immediate_parser->parse("$-1");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);
    */

    res = immediate_parser->parse("0");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(literals_two_byte)
{
    statement::operand_t expected{ statement::IMMEDIATE, 0, { 5, 2 } };
    auto res = immediate_parser->parse("$517");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0x03, 0x08 } };
    res      = immediate_parser->parse("$04003");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0x0f, 0x0f } };
    res      = immediate_parser->parse("$0x0f0f");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);
}

BOOST_AUTO_TEST_CASE(literals_jump)
{
    statement::operand_t expected{ statement::IMMEDIATE, 0, { 0, 0 } };
    auto res = immediate_parser->parse_jump_instruction("0");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 5, 0 } };
    res      = immediate_parser->parse_jump_instruction("5");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 022, 0 } };
    res      = immediate_parser->parse_jump_instruction("022");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0xf, 0 } };
    res      = immediate_parser->parse_jump_instruction("0xf");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    // Literals in immediate parsing cannot be chars or negative integers!
    /*
    expected = { statement::IMMEDIATE, 0, { 'a', 0 } };
    res = immediate_parser->parse_jump_instruction("'a'");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0xff, 0xff } };
    res = immediate_parser->parse_jump_instruction("-1");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);
    */

    res = immediate_parser->parse_jump_instruction("$0");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(literals_two_byte_jump)
{
    statement::operand_t expected{ statement::IMMEDIATE, 0, { 5, 2 } };
    auto res = immediate_parser->parse_jump_instruction("517");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0x03, 0x08 } };
    res      = immediate_parser->parse_jump_instruction("04003");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    expected = { statement::IMMEDIATE, 0, { 0x0f, 0x0f } };
    res      = immediate_parser->parse_jump_instruction("0x0f0f");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);
}

BOOST_AUTO_TEST_SUITE_END()
