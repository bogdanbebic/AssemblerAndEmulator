#include <boost/test/unit_test.hpp>

#include "../include/RegisterDirectParser.hpp"

#include <memory>

struct RegisterDirectParserFixture
{
    std::unique_ptr<parsers::RegisterDirectParser> reg_dir_parser = std::make_unique<parsers::RegisterDirectParser>();
};

BOOST_FIXTURE_TEST_SUITE(TestRegisterDirectParser, RegisterDirectParserFixture)

BOOST_AUTO_TEST_CASE(empty_string)
{
    auto res = reg_dir_parser->parse("");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
