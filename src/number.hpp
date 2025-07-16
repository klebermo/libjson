#ifndef number_hpp
#define number_hpp

#include "string.hpp"

class JSONNumber : public Value {
private:
    double value;
public:
    JSONNumber();
    JSONNumber(const JSONNumber& other);
    JSONNumber(int value);
    JSONNumber(float value);
    JSONNumber(double value);
    ~JSONNumber();

    JSONNumber* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    JSONNumber& operator=(const JSONNumber& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }

    JSONNumber& operator=(int value) {
        this->value = static_cast<double>(value);
        return *this;
    }

    JSONNumber& operator=(float value) {
        this->value = static_cast<double>(value);
        return *this;
    }

    JSONNumber& operator=(double value) {
        this->value = value;
        return *this;
    }

    JSONNumber& operator=(const std::string& value) {
        this->parse(value);
        return *this;
    }
};

#endif
