#include "buffer.hpp"

namespace Hoshi {
namespace Document {

LineBuffer::LineBuffer() {}
LineBuffer::LineBuffer(const std::string& _str) : LineBuffer(std::string(_str)) {}
LineBuffer::LineBuffer(std::string&& _str) {
    std::istringstream iss(std::move(_str));
    std::string line;
    while (std::getline(iss, line)) {
        lines_.push_back(line);
    }
}
LineBuffer::LineBuffer(const std::vector<std::string>& _lines)
    : LineBuffer(std::vector<std::string>(_lines)) {}
LineBuffer::LineBuffer(std::vector<std::string>&& _lines)
    : lines_(std::move(_lines)) {}
LineBuffer::~LineBuffer() {}

size_t LineBuffer::line_count() const { return lines_.size(); }
size_t LineBuffer::column_count(size_t _index) const { return lines_[_index].size(); }
std::string LineBuffer::get_line(size_t _index) const { return lines_[_index]; }
std::string LineBuffer::get_block(size_t _line_start, size_t _line_end, 
                    size_t _column_start, size_t _column_end) const {
    std::string text;
    for (size_t i = 0; i < line_count(); i++) {
        if (i == 0) {
            text += get_line(i).substr(_column_start) + "\n";
        } else if (i == line_count() - 1) {
            text += get_line(i).substr(0, _column_end) + "\n";
        } else {
            text += get_line(i) + "\n";
        }
    }
    return text;
}

void LineBuffer::insert(size_t _line, size_t _column, const std::string& _str) {
    if (_line > lines_.size()) {
        return;
    }
    
    std::string new_str;
    if (_line == lines_.size()) {
        new_str = _str;
    } else {
        new_str = lines_[_line].substr(0, _column) + _str +
                    lines_[_line].substr(_column);
    }

    int i = 0;
    std::istringstream iss(new_str);
    for (std::string line; std::getline(iss, line);) {
        lines_.insert(lines_.begin() + _line + i++, line);
    }
}

void LineBuffer::erase(size_t _line_start, size_t _line_end, 
            size_t _column_start, size_t _column_end) {
    
    if (_line_start + 1 == _line_end && _column_start != 0 && _column_end != column_count(_line_start)) {
        lines_[_line_start] = lines_[_line_start].substr(_line_start, _line_end);
        return;
    }
    
    const size_t start = _column_start == 0 ? _line_start : _line_start + 1;
    const size_t end = _column_end < column_count(_line_end - 1) ? _line_end - 1 : _line_end;

    if (_column_start > 0) {
        lines_[_line_start] = lines_[_line_start].substr(0, _column_start);
    }
    if (_column_end < column_count(_line_end - 1)) {
        lines_[_line_end - 1] = lines_[_line_end - 1].substr(_column_end);
    }

    lines_.erase(lines_.begin() + start, lines_.begin() + end);
}

}  // namespace Document
}  // namespace Hoshi
