#ifndef nullable_hpp
#define nullable_hpp

#include "value.hpp"

class JSONNullable : public Value {
public:
    JSONNullable();
    JSONNullable(const JSONNullable& other);
    ~JSONNullable();

    JSONNullable* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    JSONNullable& operator=(const JSONNullable& other) {
        if (this != &other) {
            // No specific data to copy for a null type
        }
        return *this;
    }

    JSONNullable& operator=(std::nullptr_t) {
        // No specific data to set for a null type
        return *this;
    }
};

#endif
