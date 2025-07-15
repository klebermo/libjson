#include "number.hpp"

JSONNumber::JSONNumber() {}

JSONNumber::JSONNumber(const JSONNumber& other) {
    this->value = other.value;
}

JSONNumber::JSONNumber(int value) {
    this->value = static_cast<double>(value);
}

JSONNumber::JSONNumber(float value) {
    this->value = static_cast<double>(value);
}

JSONNumber::JSONNumber(double value) {
    this->value = value;
}

JSONNumber::~JSONNumber() {}

JSONNumber* JSONNumber::parse(const std::string& json_string) {
    value = std::stod(json_string);
    return this;
}

std::unique_ptr<Value> JSONNumber::clone() const {
    return std::make_unique<JSONNumber>(*this);
}

std::string JSONNumber::toString() const {
    return std::to_string(value);
}

std::string JSONNumber::toJson() const {
    return std::to_string(value);
}
