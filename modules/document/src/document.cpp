#include "document/document.hpp"
#include "buffer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include "document/document_exception.hpp"

namespace Hoshi {
namespace Document {

Document::Document(const std::string& _filename) noexcept
    : filename_(_filename), line_buffer_(std::make_unique<LineBuffer>()) {}

Document::~Document() {}

const std::string& Document::get_filename() const noexcept {
    return filename_;
}

void Document::set_filename(const std::string& _filename) noexcept {
    filename_ = _filename;
}

int Document::line_count() const noexcept {
    return line_buffer_->line_count();
}

int Document::column_count(int index) const {
    return line_buffer_->column_count(index);
}

std::string Document::get_line(int index) const {
    return line_buffer_->get_line(index);
}

std::string Document::get_block(
    int line_start, int line_end, int column_start, int column_end) const {
    return line_buffer_->get_block(
        line_start, line_end, column_start, column_end);
}

std::string Document::get_block() const {
    const size_t lines = line_buffer_->line_count();
    if (lines == 0) {
        return "";
    }
    return get_block(0, lines, 0, line_buffer_->column_count(lines - 1));
}

void Document::insert(int _line, int _column, const std::string& _str) {
    line_buffer_->insert(_line, _column, _str);
}

void Document::remove(int _line_start, int _line_end, int _column_start, int _column_end) {
    line_buffer_->erase(_line_start, _line_end, _column_start, _column_end);
}

void Document::set_line(int _index, const std::string& _line) {
    if (_index < 0 || _index >= line_buffer_->line_count()) {
        throw DocumentException("Index out of range");
    }
    line_buffer_->erase(_index, _index + 1, 0, line_buffer_->column_count(_index));
    std::cout << "deleted" << std::endl;
    line_buffer_->insert(_index, 0, _line);
}

void Document::add_line(const std::string& _line) {
    line_buffer_->insert(line_buffer_->line_count(), 0, _line);
}

bool Document::save() {
    std::ofstream file(filename_);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename_ << std::endl;
        return false;
    }
    file << get_block();
    return true;
}

std::shared_ptr<Document> Document::load(const std::string& _filename) {
    std::ifstream file(_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << _filename << std::endl;
        return nullptr;
    }

    auto doc = std::make_shared<Document>(_filename);
    for (std::string line; std::getline(file, line); ) {
        doc->add_line(line);
    }
    return doc;
}

std::shared_ptr<Document> Document::create(const std::string& _filename) {
    return std::make_shared<Document>(_filename);
}

}  // namespace Document
}  // namespace Hoshi
