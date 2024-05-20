#include "object.hpp"

#include <iostream>

JSONObject::JSONObject() {
    //
}

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

JSONObject& JSONObject::operator+(std::pair<const std::string, std::unique_ptr<Value>> pair) {
    values[pair.first] = std::move(pair.second);
    return *this;
}

JSONObject& JSONObject::operator+(std::pair<const std::string, std::string> pair) {
    values[pair.first] = std::make_unique<JSONString>(pair.second);
    return *this;
}

JSONObject& JSONObject::operator+(std::pair<const std::string, double> pair) {
    values[pair.first] = std::make_unique<JSONNumber>(pair.second);
    return *this;
}

JSONObject& JSONObject::operator+(std::pair<const std::string, JSONArray*> pair) {
    values[pair.first] = std::make_unique<JSONArray>(pair.second);
    return *this;
}

Value& JSONObject::operator[](std::string key) {
    return *values[key];
}

JSONObject* JSONObject::parse(const std::string& json_string) {
    if (json_string.length() >= 2 && json_string.front() == '{' && json_string.back() == '}') {
        std::string element = json_string.substr(1, json_string.length() - 2);
        size_t pos = 0;

        while(pos < element.length()) {
            size_t startPos = element.find_first_of('"', pos);
            size_t endPos = element.find_first_of(':', startPos);
            std::string key = element.substr(startPos + 1, endPos - startPos - 2);

            startPos = element.find_first_not_of(" \b\f\n\r\t", endPos + 1);
            std::string value;
            if(element[startPos] == '"') {
                endPos = element.find_first_of('"', startPos+1);
                value = element.substr(startPos, endPos - startPos + 1);
            } else {
                int commaPos = 0;
                for(endPos=startPos; endPos<element.length(); endPos++) {
                    if(element[endPos] == '{' || element[endPos] == '[') commaPos++;
                    if(element[endPos] == '}' || element[endPos] == ']') commaPos--;

                    if(element[endPos] == '}' && commaPos == 0) break;
                    if(element[endPos] == ']' && commaPos == 0) break;

                    if(element[endPos] == ',' && commaPos != 0) endPos++;
                    if(element[endPos] == ',' && commaPos == 0) break;
                }
                value = element.substr(startPos, endPos - startPos + 1);
            }

            std::unique_ptr<Value> data;
            if(value.front() == '{' && value.back() == '}') {
                data = std::make_unique<JSONObject>(value);
            } else if(value.front() == '[' && value.back() == ']') {
                data = std::make_unique<JSONArray>(value);
            } else if(value.front() == '"' && value.back() == '"') {
                data = std::make_unique<JSONString>(value);
            } else if(value.front() >= '0' && value.front() <= '9') {
                data = std::make_unique<JSONNumber>(value);
            } else if(value.compare("true") == 0 || value.compare("false") == 0) {
                data = std::make_unique<JSONBoolean>(value);
            } else if(value.compare("null") == 0) {
                data = std::make_unique<JSONNullable>(value);
            }
            this->operator+(std::make_pair(key, std::move(data)));
            pos = endPos + 1;
        }
    }
    return this;
}

