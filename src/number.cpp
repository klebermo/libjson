#include "number.hpp"

JSONNumber::JSONNumber() {}

JSONNumber::JSONNumber(int value) {
    this->value = value;
}

JSONNumber::JSONNumber(double value) {
    this->value = value;
}

JSONNumber::JSONNumber(const std::string& json_string) {
    this->parse(json_string);
}

JSONNumber::JSONNumber(const Value& value) {
    this->parse(value.toString());
}

JSONNumber::~JSONNumber() {}

JSONNumber* JSONNumber::parse(const std::string& json_string) {
    value = std::stod(json_string);
    return this;
}

std::string JSONNumber::toString() const {
    return std::to_string(value);
}

std::string JSONNumber::toJson() const {
    return std::to_string(value);
}
