#include "string.hpp"

JSONString::JSONString() {}

JSONString::JSONString(const JSONString& other) {
    this->value = other.value;
}

JSONString::JSONString(const std::string& value) {
    this->value = value;
}

JSONString::~JSONString() {}

JSONString* JSONString::parse(const std::string& json_string) {
    value = json_string.substr(0, json_string.length());
    return this;
}

std::unique_ptr<Value> JSONString::clone() const {
    return std::make_unique<JSONString>(*this);
}

std::string JSONString::toString() const {
    return value;
}

std::string JSONString::toJson() const {
    return "\"" + value + "\"";
}
