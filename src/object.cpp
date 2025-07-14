#include "object.hpp"

JSONObject::JSONObject() {}

JSONObject::JSONObject(JSONObject* value) {
    for (auto& item : value->values) {
        values.insert(std::move(item));
    }
}

JSONObject::JSONObject(const std::string& json_string) {
    this->parse(json_string);
}

JSONObject::~JSONObject() {
    this->values.clear();
}

JSONObject* JSONObject::parse(const std::string& json_string) {
    size_t i = 0;
    skip_whitespace(json_string, i);
    if (json_string[i++] != '{') throw std::runtime_error("Object must start with '{'");

    while(i < json_string.size()) {
        skip_whitespace(json_string, i);
        if(json_string[i] == '}') break;

        const std::string key = parse_string(json_string, i);
        skip_whitespace(json_string, i);
        if (json_string[i++] != ':') throw std::runtime_error("Expected ':' after key");
        std::string value = parse_value(json_string, i);

        if (value.front() == '{') {
            values[key] = std::make_unique<JSONObject>(value);
        } else if (value.front() == '[') {
            values[key] = std::make_unique<JSONArray>(value);
        } else if (somenteNumeros(value)) {
            values[key] = std::make_unique<JSONNumber>(value);
        } else if (value == "true" || value == "false") {
            values[key] = std::make_unique<JSONBoolean>(value);
        } else if(isalnum(value.front())) {
            values[key] = std::make_unique<JSONString>(value);
        } else {
            values[key] = std::make_unique<JSONNullable>(value);
        }

        skip_whitespace(json_string, i);
        if (json_string[i] == ',') ++i;

    }

    return this;
}

std::string JSONObject::toString() const {
    std::string result = "{";
    for (auto it = values.begin(); it != values.end(); it++) {
        result += "\"" + it->first + "\":" + it->second->toString();
        if (std::next(it) != values.end()) {
            result += ",";
        }
    }
    result += "}";
    return result;
}

std::string JSONObject::toJson() const {
    std::string result = "{";
    for (auto it = values.begin(); it != values.end(); it++) {
        result += "\"" + it->first + "\":" + it->second->toJson();
        if (std::next(it) != values.end()) {
            result += ",";
        }
    }
    result += "}";
    return result;
}

int JSONObject::size() const {
    return this->values.size();
}

Value& JSONObject::operator[](std::string key) {
    return *values[key];
}

void JSONObject::add(std::string key, std::unique_ptr<Value> value) {
    this->values[key] = std::move(value);
}
