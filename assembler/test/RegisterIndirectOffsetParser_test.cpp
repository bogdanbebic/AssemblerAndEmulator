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

BOOST_AUTO_TEST_CASE(sp)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, 6, { 0, 0 } };
    statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, 6, { 7, 0 } };
    statement::operand_t expected_offset_two_byte{ statement::REGISTER_INDIRECT_OFFSET,
                                                   6,
                                                   { 5, 2 } };

    auto res = reg_ind_off_parser->parse("0(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_off_parser->parse("7(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset, *res);

    res = reg_ind_off_parser->parse("517(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset_two_byte, *res);

    res = reg_ind_off_parser->parse("*0(%sp)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, 7, { 0, 0 } };
    statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, 7, { 7, 0 } };
    statement::operand_t expected_offset_two_byte{ statement::REGISTER_INDIRECT_OFFSET,
                                                   7,
                                                   { 5, 2 } };

    auto res = reg_ind_off_parser->parse("0(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_off_parser->parse("7(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset, *res);

    res = reg_ind_off_parser->parse("517(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset_two_byte, *res);

    res = reg_ind_off_parser->parse("*0(%pc)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, 0xF, { 0, 0 } };
    statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, 0xF, { 7, 0 } };
    statement::operand_t expected_offset_two_byte{ statement::REGISTER_INDIRECT_OFFSET,
                                                   0xF,
                                                   { 5, 2 } };

    auto res = reg_ind_off_parser->parse("0(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_off_parser->parse("7(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset, *res);

    res = reg_ind_off_parser->parse("517(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset_two_byte, *res);

    res = reg_ind_off_parser->parse("*0(%psw)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, i, { 0, 0 } };
        statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, i, { 7, 0 } };
        statement::operand_t expected_offset_two_byte{
            statement::REGISTER_INDIRECT_OFFSET, i, { 5, 2 }
        };

        std::string operand                 = "0(%r" + std::to_string(i) + ")";
        std::string operand_offset          = "7(%r" + std::to_string(i) + ")";
        std::string operand_offset_two_byte = "517(%r" + std::to_string(i) + ")";

        auto res = reg_ind_off_parser->parse(operand);
        BOOST_TEST(res != nullptr);
        test_equal(expected, *res);

        res = reg_ind_off_parser->parse(operand_offset);
        BOOST_TEST(res != nullptr);
        test_equal(expected_offset, *res);

        res = reg_ind_off_parser->parse(operand_offset_two_byte);
        BOOST_TEST(res != nullptr);
        test_equal(expected_offset_two_byte, *res);

        std::string operand_asterisk = "*0(%r" + std::to_string(i) + ")";
        res = reg_ind_off_parser->parse(operand_asterisk);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(sp_jump)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, 6, { 0, 0 } };
    statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, 6, { 7, 0 } };
    statement::operand_t expected_offset_two_byte{ statement::REGISTER_INDIRECT_OFFSET,
                                                   6,
                                                   { 5, 2 } };

    auto res = reg_ind_off_parser->parse_jump_instruction("*0(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_off_parser->parse_jump_instruction("*7(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset, *res);

    res = reg_ind_off_parser->parse_jump_instruction("*517(%sp)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset_two_byte, *res);

    res = reg_ind_off_parser->parse_jump_instruction("0(%sp)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(pc_jump)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, 7, { 0, 0 } };
    statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, 7, { 7, 0 } };
    statement::operand_t expected_offset_two_byte{ statement::REGISTER_INDIRECT_OFFSET,
                                                   7,
                                                   { 5, 2 } };

    auto res = reg_ind_off_parser->parse_jump_instruction("*0(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_off_parser->parse_jump_instruction("*7(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset, *res);

    res = reg_ind_off_parser->parse_jump_instruction("*517(%pc)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset_two_byte, *res);

    res = reg_ind_off_parser->parse_jump_instruction("0(%pc)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(psw_jump)
{
    statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, 0xF, { 0, 0 } };
    statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, 0xF, { 7, 0 } };
    statement::operand_t expected_offset_two_byte{ statement::REGISTER_INDIRECT_OFFSET,
                                                   0xF,
                                                   { 5, 2 } };

    auto res = reg_ind_off_parser->parse_jump_instruction("*0(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected, *res);

    res = reg_ind_off_parser->parse_jump_instruction("*7(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset, *res);

    res = reg_ind_off_parser->parse_jump_instruction("*517(%psw)");
    BOOST_TEST(res != nullptr);
    test_equal(expected_offset_two_byte, *res);

    res = reg_ind_off_parser->parse_jump_instruction("0(%psw)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(r_index_jump)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        statement::operand_t expected{ statement::REGISTER_INDIRECT_OFFSET, i, { 0, 0 } };
        statement::operand_t expected_offset{ statement::REGISTER_INDIRECT_OFFSET, i, { 7, 0 } };
        statement::operand_t expected_offset_two_byte{
            statement::REGISTER_INDIRECT_OFFSET, i, { 5, 2 }
        };

        std::string operand_asterisk        = "*0(%r" + std::to_string(i) + ")";
        std::string operand_asterisk_offset = "*7(%r" + std::to_string(i) + ")";
        std::string operand_asterisk_offset_two_byte = "*517(%r" + std::to_string(i) + ")";

        auto res = reg_ind_off_parser->parse_jump_instruction(operand_asterisk);
        BOOST_TEST(res != nullptr);
        test_equal(expected, *res);

        res = reg_ind_off_parser->parse_jump_instruction(operand_asterisk_offset);
        BOOST_TEST(res != nullptr);
        test_equal(expected_offset, *res);

        res = reg_ind_off_parser->parse_jump_instruction(operand_asterisk_offset_two_byte);
        BOOST_TEST(res != nullptr);
        test_equal(expected_offset_two_byte, *res);

        std::string operand = "0(%r" + std::to_string(i) + ")";
        res = reg_ind_off_parser->parse_jump_instruction(operand);
        BOOST_TEST(res == nullptr);
    }
}

BOOST_AUTO_TEST_CASE(r_index_out_of_range)
{
    auto res = reg_ind_off_parser->parse("0(%r9)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_CASE(random_string)
{
    auto res = reg_ind_off_parser->parse("0(%rx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_off_parser->parse("0(%spx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_off_parser->parse("0(%pcx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_off_parser->parse("0(%pswx)");
    BOOST_TEST(res == nullptr);

    res = reg_ind_off_parser->parse("0(gibberish_string)");
    BOOST_TEST(res == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
