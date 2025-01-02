#include <exception>

class illegal_exc : public std::exception {
public:
    const char* what() const noexcept override {
        return "illegal argument";
    }
};