#include <boost/test/unit_test.hpp>

#include "ElfStructs.hpp"

#include <memory>

struct ElfStructsFixture
{
    void test_equal(linker::elf::symbol_table_entry_t expected,
                    linker::elf::symbol_table_entry_t actual)
    {
        BOOST_TEST(expected.symbol == actual.symbol);
        BOOST_TEST(expected.value == actual.value);
        BOOST_TEST(expected.section_index == actual.section_index);
        BOOST_TEST(expected.is_global == actual.is_global);
    }

    void test_equal(linker::elf::section_table_entry_t expected,
                    linker::elf::section_table_entry_t actual)
    {
        BOOST_TEST(expected.section == actual.section);
        BOOST_TEST(expected.idx == actual.idx);
        BOOST_TEST(expected.size == actual.size);
    }
};

BOOST_FIXTURE_TEST_SUITE(TestElfStructs, ElfStructsFixture)

BOOST_AUTO_TEST_CASE(symbol_table_entry)
{
    auto res = linker::elf::parse_symbol_table_entry("byte_label,0,1,L");
    test_equal(res, { "byte_label", 0, 1, false });
    res = linker::elf::parse_symbol_table_entry("ext_f,0,0,G");
    test_equal(res, { "ext_f", 0, 0, true });
    res = linker::elf::parse_symbol_table_entry("ext_g,0,0,G");
    test_equal(res, { "ext_g", 0, 0, true });
    res = linker::elf::parse_symbol_table_entry("ext_h,0,0,G");
    test_equal(res, { "ext_h", 0, 0, true });
    res = linker::elf::parse_symbol_table_entry("main,0,2,L");
    test_equal(res, { "main", 0, 2, false });
    res = linker::elf::parse_symbol_table_entry("multiple_words,11,1,L");
    test_equal(res, { "multiple_words", 11, 1, false });
    res = linker::elf::parse_symbol_table_entry("skip_label,1,1,L");
    test_equal(res, { "skip_label", 1, 1, false });
    res = linker::elf::parse_symbol_table_entry("word_label,9,1,L");
    test_equal(res, { "word_label", 9, 1, false });
}

BOOST_AUTO_TEST_CASE(section_und_with_asterisks)
{
    auto res = linker::elf::parse_section_table_entry("*UND*,0,0");
    test_equal(res, { "*UND*", 0, 0 });
}

BOOST_AUTO_TEST_CASE(section_table_entry)
{
    auto res = linker::elf::parse_section_table_entry("data_section,1,29");
    test_equal(res, { "data_section", 1, 29 });
    res = linker::elf::parse_section_table_entry("section_name,2,17");
    test_equal(res, { "section_name", 2, 17 });
}

BOOST_AUTO_TEST_SUITE_END()
