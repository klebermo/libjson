#ifndef boolean_hpp
#define boolean_hpp

#include "number.hpp"

class JSONBoolean : public Value {
private:
    bool value;
public:
    JSONBoolean();
    JSONBoolean(const JSONBoolean& other);
    JSONBoolean(bool value);
    ~JSONBoolean();

    JSONBoolean* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    JSONBoolean& operator=(const JSONBoolean& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }

    JSONBoolean& operator=(bool value) {
        this->value = value;
        return *this;
    }
};

#endif
