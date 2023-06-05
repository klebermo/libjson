#include "array.hpp"

JSONArray::JSONArray() {
    this->type = array;
}

JSONArray::JSONArray(const std::string& json_string) {
    this->type = array;
    this->parse(json_string);
}

JSONArray::~JSONArray() {
    this->values.clear();
}

std::vector<const Value*> JSONArray::getValues() {
    return this->values;
}

void JSONArray::add(const Value* value) {
    values.push_back(value);
}

const Value* JSONArray::get(int index) {
    return values[index];
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
