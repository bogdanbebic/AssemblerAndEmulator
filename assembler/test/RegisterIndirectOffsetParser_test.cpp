#include <boost/test/unit_test.hpp>

#include "RegisterIndirectOffsetParser.hpp"

#include <memory>

struct RegisterIndirectOffsetParserFixture
{
    std::unique_ptr<parsers::RegisterIndirectOffsetParser> reg_ind_off_parser =
        std::make_unique<parsers::RegisterIndirectOffsetParser>(nullptr);
    void test_equal(statement::operand_t expected, statement::operand_t actual)
    {
        BOOST_TEST(expected.addressing_mode == actual.addressing_mode);
        BOOST_TEST(expected.register_index == actual.register_index);
        BOOST_TEST(expected.operand == actual.operand); // element-wise compare
    }
};

BOOST_FIXTURE_TEST_SUITE(TestRegisterIndirectOffsetParser, RegisterIndirectOffsetParserFixture)

BOOST_AUTO_TEST_CASE(empty_string)
{
    auto res = reg_ind_off_parser->parse("");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
