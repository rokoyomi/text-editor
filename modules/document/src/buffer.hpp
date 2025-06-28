#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

namespace Hoshi {
namespace Document {

class LineBuffer {
public:
    LineBuffer();
    LineBuffer(const std::string& _str);
    LineBuffer(std::string&& _str);
    LineBuffer(const std::vector<std::string>& _lines);
    LineBuffer(std::vector<std::string>&& _lines);
    ~LineBuffer();

    size_t line_count() const;
    size_t column_count(size_t _index) const;
    std::string get_line(size_t _index) const;
    std::string get_block(size_t _line_start, size_t _line_end, 
                        size_t _column_start, size_t _column_end) const;

    void insert(size_t _line, size_t _column, const std::string& _str);

    void erase(size_t _line_start, size_t _line_end, 
                size_t _column_start, size_t _column_end);
private:
    std::vector<std::string> lines_;
};

}  // namespace Document
}  // namespace Hoshi
