#pragma once
#include <stdexcept>

namespace Hoshi {
namespace Document {
class DocumentException : public std::exception {
public:
    DocumentException(const std::string& _message) {}
    virtual ~DocumentException() throw() {}
    // const char* what() const throw() { return "Document Exception"; }
private:
};
}  // namespace Document
}  // namespace Hoshi
