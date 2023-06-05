#include "boolean.hpp"

JSONBoolean::JSONBoolean() {
    this->type = boolean;
}

JSONBoolean::JSONBoolean(const std::string& json_string) {
    this->type = boolean;
    this->parse(json_string);
}

JSONBoolean::~JSONBoolean() {
    //
}

std::string JSONBoolean::toString() const {
    return value ? "true" : "false";
}

bool JSONBoolean::getValue() {
    return this->value;
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
