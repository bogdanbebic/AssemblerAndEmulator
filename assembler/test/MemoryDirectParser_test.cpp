#include <boost/test/unit_test.hpp>

#include "MemoryDirectParser.hpp"

#include <memory>

struct MemoryDirectParserFixture
{
    std::unique_ptr<parsers::MemoryDirectParser> mem_dir_parser =
        std::make_unique<parsers::MemoryDirectParser>(nullptr);
    void test_equal(statement::operand_t expected, statement::operand_t actual)
    {
        BOOST_TEST(expected.addressing_mode == actual.addressing_mode);
        BOOST_TEST(expected.register_index == actual.register_index);
        BOOST_TEST(expected.operand == actual.operand); // element-wise compare
    }
};

BOOST_FIXTURE_TEST_SUITE(TestMemoryDirectParser, MemoryDirectParserFixture)

BOOST_AUTO_TEST_CASE(empty_string)
{
    auto res = mem_dir_parser->parse("");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(gibberish_operand)
{
    auto res = mem_dir_parser->parse("%gibberish");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("%rx");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("%spx");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("%pcx");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("%pswx");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("gibberish*");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("rx*");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("spx*");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("pcx*");
    BOOST_TEST(res == nullptr);

    res = mem_dir_parser->parse("pswx*");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
