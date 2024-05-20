#include "array.hpp"

JSONArray::JSONArray() {
    //
}

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

Value& JSONArray::operator[](int index) {
    return *values[index];
}

JSONArray& JSONArray::operator+(std::unique_ptr<Value> value) {
    values.push_back(std::move(value));
    return *this;
}

JSONArray& JSONArray::operator+(const char* value) {
    return *this + std::make_unique<JSONString>(value);
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
            this->operator+(std::move(data));
            pos = endPos + 1;
        }
    }
    return this;
}
