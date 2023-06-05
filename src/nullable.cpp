#include "nullable.hpp"

JSONNullable::JSONNullable() {
    this->type = nullable;
}

JSONNullable::JSONNullable(const std::string& json_string) {
    this->type = nullable;
}

JSONNullable::~JSONNullable() {
    //
}

std::string JSONNullable::getValue() {
    return nullptr;
}

std::string JSONNullable::toString() const {
    return "\"null\"";
}

JSONNullable* JSONNullable::parse(const std::string& json_string) {
    if(json_string.compare("null") == 0) {
        return this;
    }
    return nullptr;
}
