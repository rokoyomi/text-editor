#include <document/document.hpp>
#include <gtest/gtest.h>


using Document = Hoshi::Document::Document;


TEST(document, create_document) {
    EXPECT_NE(Document::create("create_document.txt"), nullptr);
}

TEST(document, load_empty_document) {
    Document::create("load_empty_document.txt")->save();
    EXPECT_NE(Document::load("load_empty_document.txt"), nullptr);
}

TEST(document, save_and_read_single_line) {
    auto document = Document::create("save_and_read_single_line.txt");
    if (document == nullptr) {
        GTEST_FATAL_FAILURE_("Failed to load document");
    }
    document->add_line("test1");
    document->save();
    EXPECT_EQ(
        Document::load("save_and_read_single_line.txt")->get_block(),
        "test1\n");
}

TEST(document, save_and_read_multiple_lines) {
    auto document = Document::create("save_and_read_multiple_lines.txt");
    if (document == nullptr) {
        GTEST_FATAL_FAILURE_("Failed to load document");
    }
    document->add_line("test_line_1");
    document->add_line("test_line_2");
    document->save();
    EXPECT_EQ(
        Document::load("save_and_read_multiple_lines.txt")->get_block(),
        "test_line_1\ntest_line_2\n");
}

TEST(document, insert_between_line) {
    auto document = Document::create("insert_between_line.txt");
    if (document == nullptr) {
        GTEST_FATAL_FAILURE_("Failed to load document");
    }
    document->add_line("test_line_1");
    document->set_line(0, "test_li__ne_1");
    document->add_line("test_line_2");
    document->save();
    EXPECT_EQ(
        Document::load("insert_between_line.txt")->get_block(),
        "test_li__ne_1\ntest_line_2\n");
}

TEST(document, delete_line) {
    auto document = Document::create("delete_line.txt");
    if (document == nullptr) {
        GTEST_FATAL_FAILURE_("Failed to load document");
    }
    document->add_line("test_line_1");
    document->add_line("test_line_2");
    document->remove(0, 1, 0, document->column_count(0));
    document->save();
    EXPECT_EQ(Document::load("delete_line.txt")->get_block(), "test_line_2\n");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
