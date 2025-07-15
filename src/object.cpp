#include "object.hpp"

JSONObject::JSONObject() {}

JSONObject::JSONObject(const JSONObject& value) {
    for (const auto& [key, val] : value.values) {
        std::unique_ptr<Value> newItem = val->clone();
        values[key] = std::move(newItem);
    }
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
            JSONObject object;
            object.parse(value);
            values[key] = std::make_unique<JSONObject>(object);
        } else if (value.front() == '[') {
            JSONArray array;
            array.parse(value);
            values[key] = std::make_unique<JSONArray>(array);
        } else if (somenteNumeros(value)) {
            JSONNumber number;
            number.parse(value);
            values[key] = std::make_unique<JSONNumber>(number);
        } else if (value == "true" || value == "false") {
            JSONBoolean boolean;
            boolean.parse(value);
            values[key] = std::make_unique<JSONBoolean>(boolean);
        } else if(isalnum(value.front())) {
            JSONString string;
            string.parse(value);
            values[key] = std::make_unique<JSONString>(string);
        } else {
            JSONNullable nullable;
            nullable.parse(value);
            values[key] = std::make_unique<JSONNullable>(nullable);
        }

        skip_whitespace(json_string, i);
        if (json_string[i] == ',') ++i;

    }

    return this;
}

std::unique_ptr<Value> JSONObject::clone() const {
    return std::make_unique<JSONObject>(*this);
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

Value& JSONObject::operator[](std::string key) {
    return *values[key];
}

int JSONObject::size() const {
    return this->values.size();
}

void JSONObject::add(std::string key, std::unique_ptr<Value> value) {
    this->values[key] = std::move(value);
}

void JSONObject::add(std::string key, std::string value) {
    this->values[key] = std::make_unique<JSONString>(value);
}

void JSONObject::add(std::string key, const char * value) {
    this->values[key] = std::make_unique<JSONString>(value);
}

void JSONObject::add(std::string key, int value) {
    this->values[key] = std::make_unique<JSONNumber>(value);
}

void JSONObject::add(std::string key, float value) {
    this->values[key] = std::make_unique<JSONNumber>(value);
}

void JSONObject::add(std::string key, double value) {
    this->values[key] = std::make_unique<JSONNumber>(value);
}

void JSONObject::add(std::string key, bool value) {
    this->values[key] = std::make_unique<JSONBoolean>(value);
}

void JSONObject::add(std::string key, std::string values[]) {
    //
}

void JSONObject::add(std::string key, const char * values[]) {
    //
}

void JSONObject::add(std::string key, int values[]) {
    //
}

void JSONObject::add(std::string key, float values[]) {
    //
}

void JSONObject::add(std::string key, double values[]) {
    //
}

void JSONObject::add(std::string key, bool values[]) {
    //
}


