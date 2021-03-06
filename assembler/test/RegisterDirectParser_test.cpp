#include <boost/test/unit_test.hpp>

#include "RegisterDirectParser.hpp"

#include <memory>

struct RegisterDirectParserFixture
{
    std::unique_ptr<parsers::RegisterDirectParser> reg_dir_parser =
        std::make_unique<parsers::RegisterDirectParser>();
    void test_equal(statement::operand_t expected, statement::operand_t actual)
    {
        BOOST_TEST(expected.addressing_mode == actual.addressing_mode);
        BOOST_TEST(expected.register_index == actual.register_index);
        BOOST_TEST(expected.operand == actual.operand); // element-wise compare
    }
};

BOOST_FIXTURE_TEST_SUITE(TestRegisterDirectParser, RegisterDirectParserFixture)

BOOST_AUTO_TEST_CASE(empty_string)
{
    auto res = reg_dir_parser->parse("");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(sp)
{
    statement::operand_t expected{ statement::REGISTER, 6, { 0, 0 } };
    auto res = reg_dir_parser->parse("%sp");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_dir_parser->parse("*%sp");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc)
{
    statement::operand_t expected{ statement::REGISTER, 7, { 0, 0 } };
    auto res = reg_dir_parser->parse("%pc");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_dir_parser->parse("*%pc");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw)
{
    statement::operand_t expected{ statement::REGISTER, 0xF, { 0, 0 } };
    auto res = reg_dir_parser->parse("%psw");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_dir_parser->parse("*%psw");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected{ statement::REGISTER, i, { 0, 0 } };

        std::string operand = "%r" + std::to_string(i);
        auto res            = reg_dir_parser->parse(operand);
        BOOST_TEST(res != nullptr);
        test_equal(expected, *res);

        std::string operand_asterisk = "*%r" + std::to_string(i);
        res                          = reg_dir_parser->parse(operand_asterisk);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(sp_jump)
{
    statement::operand_t expected{ statement::REGISTER, 6, { 0, 0 } };
    auto res = reg_dir_parser->parse_jump_instruction("*%sp");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_dir_parser->parse_jump_instruction("%sp");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc_jump)
{
    statement::operand_t expected{ statement::REGISTER, 7, { 0, 0 } };
    auto res = reg_dir_parser->parse_jump_instruction("*%pc");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_dir_parser->parse_jump_instruction("%pc");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw_jump)
{
    statement::operand_t expected{ statement::REGISTER, 0xF, { 0, 0 } };
    auto res = reg_dir_parser->parse_jump_instruction("*%psw");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_dir_parser->parse_jump_instruction("%psw");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index_jump)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected{ statement::REGISTER, i, { 0, 0 } };

        std::string operand_asterisk = "*%r" + std::to_string(i);
        auto res = reg_dir_parser->parse_jump_instruction(operand_asterisk);
        BOOST_TEST(res != nullptr);
        test_equal(expected, *res);

        std::string operand = "%r" + std::to_string(i);
        res                 = reg_dir_parser->parse_jump_instruction(operand);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(sp_byte)
{
    statement::operand_t expected_low{ statement::REGISTER, 6, { 0, 0 }, 0, 1 };
    auto res = reg_dir_parser->parse("%spl");
    BOOST_TEST(res != nullptr);
    test_equal(expected_low, *res);

    res = reg_dir_parser->parse("*%spl");
    BOOST_TEST(res == nullptr);

    statement::operand_t expected_high{ statement::REGISTER, 6, { 0, 0 }, 1, 1 };
    res = reg_dir_parser->parse("%sph");
    BOOST_TEST(res != nullptr);
    test_equal(expected_high, *res);

    res = reg_dir_parser->parse("*%sph");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc_byte)
{
    statement::operand_t expected_low{ statement::REGISTER, 7, { 0, 0 }, 0, 1 };
    auto res = reg_dir_parser->parse("%pcl");
    BOOST_TEST(res != nullptr);
    test_equal(expected_low, *res);

    res = reg_dir_parser->parse("*%pcl");
    BOOST_TEST(res == nullptr);

    statement::operand_t expected_high{ statement::REGISTER, 7, { 0, 0 }, 1, 1 };
    res = reg_dir_parser->parse("%pch");
    BOOST_TEST(res != nullptr);
    test_equal(expected_high, *res);

    res = reg_dir_parser->parse("*%pch");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw_byte)
{
    statement::operand_t expected_low{ statement::REGISTER, 0xF, { 0, 0 }, 0, 1 };
    auto res = reg_dir_parser->parse("%pswl");
    BOOST_TEST(res != nullptr);
    test_equal(expected_low, *res);

    res = reg_dir_parser->parse("*%pswl");
    BOOST_TEST(res == nullptr);

    statement::operand_t expected_high{ statement::REGISTER, 0xF, { 0, 0 }, 1, 1 };
    res = reg_dir_parser->parse("%pswh");
    BOOST_TEST(res != nullptr);
    test_equal(expected_high, *res);

    res = reg_dir_parser->parse("*%pswh");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index_byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected_low{ statement::REGISTER, i, { 0, 0 }, 0, 1 };

        std::string operand = "%r" + std::to_string(i) + "l";
        auto res            = reg_dir_parser->parse(operand);
        BOOST_TEST(res != nullptr);
        test_equal(expected_low, *res);

        std::string operand_asterisk = "*%r" + std::to_string(i) + "l";
        res                          = reg_dir_parser->parse(operand_asterisk);
        BOOST_TEST(res == nullptr);

        statement::operand_t expected_high{ statement::REGISTER, i, { 0, 0 }, 1, 1 };

        operand = "%r" + std::to_string(i) + "h";
        res     = reg_dir_parser->parse(operand);
        BOOST_TEST(res != nullptr);
        test_equal(expected_high, *res);

        operand_asterisk = "*%r" + std::to_string(i) + "h";
        res              = reg_dir_parser->parse(operand_asterisk);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(sp_jump_byte)
{
    statement::operand_t expected_low{ statement::REGISTER, 6, { 0, 0 }, 0, 1 };
    auto res = reg_dir_parser->parse_jump_instruction("*%spl");
    BOOST_TEST(res != nullptr);
    test_equal(expected_low, *res);

    res = reg_dir_parser->parse_jump_instruction("%spl");
    BOOST_TEST(res == nullptr);

    statement::operand_t expected_high{ statement::REGISTER, 6, { 0, 0 }, 1, 1 };
    res = reg_dir_parser->parse_jump_instruction("*%sph");
    BOOST_TEST(res != nullptr);
    test_equal(expected_high, *res);

    res = reg_dir_parser->parse_jump_instruction("%sph");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc_jump_byte)
{
    statement::operand_t expected_low{ statement::REGISTER, 7, { 0, 0 }, 0, 1 };
    auto res = reg_dir_parser->parse_jump_instruction("*%pcl");
    BOOST_TEST(res != nullptr);
    test_equal(expected_low, *res);

    res = reg_dir_parser->parse_jump_instruction("%pcl");
    BOOST_TEST(res == nullptr);

    statement::operand_t expected_high{ statement::REGISTER, 7, { 0, 0 }, 1, 1 };
    res = reg_dir_parser->parse_jump_instruction("*%pch");
    BOOST_TEST(res != nullptr);
    test_equal(expected_high, *res);

    res = reg_dir_parser->parse_jump_instruction("%pch");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw_jump_byte)
{
    statement::operand_t expected_low{ statement::REGISTER, 0xF, { 0, 0 }, 0, 1 };
    auto res = reg_dir_parser->parse_jump_instruction("*%pswl");
    BOOST_TEST(res != nullptr);
    test_equal(expected_low, *res);

    res = reg_dir_parser->parse_jump_instruction("%pswl");
    BOOST_TEST(res == nullptr);

    statement::operand_t expected_high{ statement::REGISTER, 0xF, { 0, 0 }, 1, 1 };
    res = reg_dir_parser->parse_jump_instruction("*%pswh");
    BOOST_TEST(res != nullptr);
    test_equal(expected_high, *res);

    res = reg_dir_parser->parse_jump_instruction("%pswh");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index_jump_byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected_low{ statement::REGISTER, i, { 0, 0 }, 0, 1 };

        std::string operand_asterisk = "*%r" + std::to_string(i) + "l";
        auto res = reg_dir_parser->parse_jump_instruction(operand_asterisk);
        BOOST_TEST(res != nullptr);
        test_equal(expected_low, *res);

        std::string operand = "%r" + std::to_string(i) + "l";
        res                 = reg_dir_parser->parse_jump_instruction(operand);
        BOOST_TEST(res == nullptr);

        statement::operand_t expected_high{ statement::REGISTER, i, { 0, 0 }, 1, 1 };

        operand_asterisk = "*%r" + std::to_string(i) + "h";
        res = reg_dir_parser->parse_jump_instruction(operand_asterisk);
        BOOST_TEST(res != nullptr);
        test_equal(expected_high, *res);

        operand = "%r" + std::to_string(i) + "h";
        res     = reg_dir_parser->parse_jump_instruction(operand);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(r_index_out_of_range)
{
    auto res = reg_dir_parser->parse("%r9");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(random_string)
{
    auto res = reg_dir_parser->parse("%rx");
    BOOST_TEST(res == nullptr);

    res = reg_dir_parser->parse("%spx");
    BOOST_TEST(res == nullptr);

    res = reg_dir_parser->parse("%pcx");
    BOOST_TEST(res == nullptr);

    res = reg_dir_parser->parse("%pswx");
    BOOST_TEST(res == nullptr);

    res = reg_dir_parser->parse("gibberish_string");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
