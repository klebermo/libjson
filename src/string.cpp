#include "string.hpp"

JSONString::JSONString() {}

JSONString::JSONString(const std::string& json_string) {
    this->parse(json_string);
}

JSONString::~JSONString() {}

JSONString* JSONString::parse(const std::string& json_string) {
    value = json_string.substr(0, json_string.length());
    return this;
}

std::string JSONString::toString() const {
    return value;
}

std::string JSONString::toJson() const {
    return "\"" + value + "\"";
}
