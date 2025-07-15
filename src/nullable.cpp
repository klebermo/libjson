#include "nullable.hpp"

JSONNullable::JSONNullable() {}

JSONNullable::JSONNullable(const JSONNullable& other) {}

JSONNullable::~JSONNullable() {}

JSONNullable* JSONNullable::parse(const std::string& json_string) {
    if(json_string.compare("null") == 0) {
        return this;
    }
    return nullptr;
}

std::unique_ptr<Value> JSONNullable::clone() const {
    return std::make_unique<JSONNullable>(*this);
}

std::string JSONNullable::toString() const {
    return "null";
}

std::string JSONNullable::toJson() const {
    return "\"\"";
}
