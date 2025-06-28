#pragma once

#include <memory>
#include <vector>

// Add exception handling

namespace Hoshi {
namespace Document {

class LineBuffer;
class Document {
public:
    Document(const std::string& _filename) noexcept;
    Document(const Document&) = delete;
    Document& operator=(const Document&) = delete;
    virtual ~Document();

    const std::string& get_filename() const noexcept;
    void set_filename(const std::string& _filename) noexcept;

    int line_count() const noexcept;
    int column_count(int _index) const;
    std::string get_line(int _index) const;
    std::string get_block(int _line_start, int _line_end,
                        int _column_start, int _column_end) const;
    std::string get_block() const;
    void insert(int _line, int _column, const std::string& _str);
    void remove(int _line_start, int _line_end,
                int _column_start, int _column_end);

    void set_line(int _index, const std::string& _line);
    void add_line(const std::string& _line);

    bool save();
    static std::shared_ptr<Document> load(const std::string& _filename);
    static std::shared_ptr<Document> create(const std::string& _filename);
private:
    std::string filename_;
    std::unique_ptr<LineBuffer> line_buffer_;
};

}  // namespace Document
}  // namespace Hoshi
