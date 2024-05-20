#include "boolean.hpp"

JSONBoolean::JSONBoolean() {
    this->type = boolean;
}

JSONBoolean::JSONBoolean(const std::string& json_string) {
    this->type = boolean;
    this->parse(json_string);
}

JSONBoolean::JSONBoolean(bool value) {
    this->type = boolean;
    this->value = value;
}

JSONBoolean::~JSONBoolean() {
    //
}

std::string JSONBoolean::toString() const {
    return value ? "true" : "false";
}

JSONBoolean* JSONBoolean::parse(const std::string& json_string) {
    if (json_string.compare("true") == 0) {
        value = true;
        return this;
    } else {
        value = false;
        return this;
    }
}
