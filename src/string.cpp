#include "string.hpp"

JSONString::JSONString() {
    this->type = string;
}

JSONString::JSONString(const std::string& json_string) {
    this->type = string;
    this->parse(json_string);
}

JSONString::~JSONString() {
    //
}

std::string JSONString::getValue() {
    return this->value;
}

std::string JSONString::toString() const {
    return "\"" + value + "\"";
}

JSONString* JSONString::parse(const std::string& json_string) {
    value = json_string.substr(1, json_string.length() - 2);
    return this;
}
