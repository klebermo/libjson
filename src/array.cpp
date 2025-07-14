#include "array.hpp"

JSONArray::JSONArray() {}

JSONArray::JSONArray(JSONArray* value) {
    for (auto& item : value->values) {
        values.push_back(std::move(item));
    }
}

JSONArray::JSONArray(const std::string& json_string) {
    this->parse(json_string);
}

JSONArray::~JSONArray() {
    this->values.clear();
}

JSONArray* JSONArray::parse(const std::string& json_string) {
    size_t i = 0;
    skip_whitespace(json_string, i);
    if (json_string[i++] != '[') throw std::runtime_error("Array must start with '['");

    while (i < json_string.size()) {
        skip_whitespace(json_string, i);
        if (json_string[i] == ']') break;

        std::string value = parse_value(json_string, i);

        if (value.front() == '{') {
            values.push_back(std::make_unique<JSONObject>(value));
        } else if (value.front() == '[') {
            values.push_back(std::make_unique<JSONArray>(value));
        } else if (somenteNumeros(value)) {
            values.push_back(std::make_unique<JSONNumber>(value));
        } else if (value == "true" || value == "false") {
            values.push_back(std::make_unique<JSONBoolean>(value));
        } else if(isalnum(value.front())) {
            values.push_back(std::make_unique<JSONString>(value));
        } else {
            values.push_back(std::make_unique<JSONNullable>(value));
        }

        skip_whitespace(json_string, i);
        if (json_string[i] == ',') ++i;
    }

    return this;
}

std::string JSONArray::toString() const {
    std::string result = "[";
    for (size_t i = 0; i < values.size(); ++i) {
        result += values[i]->toString();
        if (i < values.size() - 1) {
            result += ",";
        }
    }
    result += "]";
    return result;
}

std::string JSONArray::toJson() const {
    std::string result = "[";
    for (size_t i = 0; i < values.size(); ++i) {
        result += values[i]->toJson();
        if (i < values.size() - 1) {
            result += ",";
        }
    }
    return result;
}

int JSONArray::size() const {
    return this->values.size();
}

Value& JSONArray::operator[](int index) {
    return *values[index];
}

void JSONArray::add(std::unique_ptr<Value> value) {
    this->values.push_back(std::move(value));
}