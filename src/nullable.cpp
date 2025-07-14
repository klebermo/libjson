#include "nullable.hpp"

JSONNullable::JSONNullable() {}

JSONNullable::JSONNullable(const std::string& json_string) {}

JSONNullable::~JSONNullable() {}


JSONNullable* JSONNullable::parse(const std::string& json_string) {
    if(json_string.compare("null") == 0) {
        return this;
    }
    return nullptr;
}

std::string JSONNullable::toString() const {
    return "null";
}

std::string JSONNullable::toJson() const {
    return "\"\"";
}
