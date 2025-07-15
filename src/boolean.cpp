#include "boolean.hpp"

JSONBoolean::JSONBoolean() {}

JSONBoolean::JSONBoolean(const JSONBoolean& other) : value(other.value) {}

JSONBoolean::JSONBoolean(bool value) {
    this->value = value;
}

JSONBoolean::~JSONBoolean() {}

JSONBoolean* JSONBoolean::parse(const std::string& json_string) {
    if (json_string.compare("true") == 0) {
        value = true;
        return this;
    } else {
        value = false;
        return this;
    }
}

std::unique_ptr<Value> JSONBoolean::clone() const {
    return std::make_unique<JSONBoolean>(*this);
}

std::string JSONBoolean::toString() const {
    return value ? "true" : "false";
}

std::string JSONBoolean::toJson() const {
    return value ? "\"true\"" : "\"false\"";
}
