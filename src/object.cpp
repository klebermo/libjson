#include "object.hpp"

#include <iostream>

JSONObject::JSONObject() {
    this->type = object;
}

JSONObject::JSONObject(const std::string& json_string) {
    this->type = object;
    this->parse(json_string);
}

JSONObject::~JSONObject() {
    this->values.clear();
}

std::map<const std::string, const Value*> JSONObject::getValues() {
    return this->values;
}

void JSONObject::add(const std::string& key, const Value* value) {
    values[key] = value;
}

const Value* JSONObject::get(const std::string key) {
    return values[key];
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

            Value * data = nullptr;
            if(value.front() == '{' && value.back() == '}') {
                data = new JSONObject(value);
            } else if(value.front() == '[' && value.back() == ']') {
                data = new JSONArray(value);
            } else if(value.front() == '"' && value.back() == '"') {
                data = new JSONString(value);
            } else if(value.front() >= '0' && value.front() <= '9') {
                data = new JSONNumber(value);
            } else if(value.compare("true") == 0 || value.compare("false") == 0) {
                data = new JSONBoolean(value);
            } else if(value.compare("null") == 0) {
                data = new JSONNullable(value);
            }
            add(key, data);
            pos = endPos + 1;
        }
    }
    return this;
}

JSONArray* JSONArray::parse(const std::string& json_string) {
    if (json_string.length() >= 2 && json_string.front() == '[' && json_string.back() == ']') {
        std::string element = json_string.substr(1, json_string.length() - 2);
        size_t pos = 0;

        while(pos < element.length()) {
            size_t startPos = element.find_first_of('"', pos), endPos;
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

            Value * data = nullptr;
            if(value.front() == '{' && value.back() == '}') {
                data = new JSONObject(value);
            } else if(value.front() == '[' && value.back() == ']') {
                data = new JSONArray(value);
            } else if(value.front() == '"' && value.back() == '"') {
                data = new JSONString(value);
            } else if(value.front() >= '0' && value.front() <= '9') {
                data = new JSONNumber(value);
            } else if(value.compare("true") == 0 || value.compare("false") == 0) {
                data = new JSONBoolean(value);
            } else if(value.compare("null") == 0) {
                data = new JSONNullable(value);
            }
            add(data);
            pos = endPos + 1;
        }
    }
    return this;
}
