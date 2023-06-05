#include "number.hpp"

JSONNumber::JSONNumber() {
    this->type = number;
}

JSONNumber::JSONNumber(const std::string& json_string) {
    this->type = number;
    this->parse(json_string);
}

JSONNumber::~JSONNumber() {
    //
}

std::string JSONNumber::toString() const {
    return std::to_string(value);
}

double JSONNumber::getValue() {
    return this->value;
}    

JSONNumber* JSONNumber::parse(const std::string& json_string) {
    value = std::stod(json_string);
    return this;
}
