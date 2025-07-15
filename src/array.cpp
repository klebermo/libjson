#include "array.hpp"

JSONArray::JSONArray() {}

JSONArray::JSONArray(const JSONArray& value) {
    for (auto& item : value.values) {
        std::unique_ptr<Value> newItem = item->clone();
        values.push_back(std::move(newItem));
    }
}

JSONArray::JSONArray(std::initializer_list<std::string> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONString>(val));
    }
}

JSONArray::JSONArray(std::initializer_list<const char*> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONString>(val));
    }
}

JSONArray::JSONArray(std::initializer_list<int> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
}

JSONArray::JSONArray(std::initializer_list<float> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
}

JSONArray::JSONArray(std::initializer_list<double> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
}

JSONArray::JSONArray(std::initializer_list<bool> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONBoolean>(val));
    }
}

JSONArray& JSONArray::operator=(std::initializer_list<std::string> values) {
    this->values.clear();
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONString>(val));
    }
    return *this;
}

JSONArray& JSONArray::operator=(std::initializer_list<const char*> values) {
    this->values.clear();
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONString>(val));
    }
    return *this;
}

JSONArray& JSONArray::operator=(std::initializer_list<int> values) {
    this->values.clear();
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
    return *this;
}

JSONArray& JSONArray::operator=(std::initializer_list<float> values) {
    this->values.clear();
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
    return *this;
}

JSONArray& JSONArray::operator=(std::initializer_list<double> values) {
    this->values.clear();
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
    return *this;
}

JSONArray& JSONArray::operator=(std::initializer_list<bool> values) {
    this->values.clear();
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONBoolean>(val));
    }
    return *this;
}

JSONArray& JSONArray::operator+=(std::string value) {
    this->values.push_back(std::make_unique<JSONString>(value));
    return *this;
}

JSONArray& JSONArray::operator+=(const char* value) {
    this->values.push_back(std::make_unique<JSONString>(value));
    return *this;
}

JSONArray& JSONArray::operator+=(int value) {
    this->values.push_back(std::make_unique<JSONNumber>(value));
    return *this;
}

JSONArray& JSONArray::operator+=(float value) {
    this->values.push_back(std::make_unique<JSONNumber>(value));
    return *this;
}

JSONArray& JSONArray::operator+=(double value) {
    this->values.push_back(std::make_unique<JSONNumber>(value));
    return *this;
}

JSONArray& JSONArray::operator+=(bool value) {
    this->values.push_back(std::make_unique<JSONBoolean>(value));
    return *this;
}

JSONArray& JSONArray::operator+=(const JSONArray& value) {
    for (const auto& item : value.values) {
        this->values.push_back(item->clone());
    }
    return *this;
}

JSONArray& JSONArray::operator+=(const JSONObject& value) {
    this->values.push_back(std::make_unique<JSONObject>(value));
    return *this;
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
            JSONObject object;
            object.parse(value);
            add(std::make_unique<JSONObject>(object));
        } else if (value.front() == '[') {
            JSONArray array;
            array.parse(value);
            add(std::make_unique<JSONArray>(array));
        } else if (somenteNumeros(value)) {
            JSONNumber number;
            number.parse(value);
            add(std::make_unique<JSONNumber>(number));
        } else if (value == "true" || value == "false") {
            JSONBoolean boolean;
            boolean.parse(value);
            add(std::make_unique<JSONBoolean>(boolean));
        } else if(isalnum(value.front())) {
            JSONString string;
            string.parse(value);
            add(std::make_unique<JSONString>(string));
        } else {
            JSONNullable nullable;
            nullable.parse(value);
            add(std::make_unique<JSONNullable>(nullable));
        }

        skip_whitespace(json_string, i);
        if (json_string[i] == ',') ++i;
    }

    return this;
}

std::unique_ptr<Value> JSONArray::clone() const {
    return std::make_unique<JSONArray>(*this);
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
    result += "]";
    return result;
}

Value& JSONArray::operator[](int index) {
    return *values[index];
}

int JSONArray::size() const {
    return this->values.size();
}

void JSONArray::add(std::unique_ptr<Value> value) {
    this->values.push_back(std::move(value));
}

void JSONArray::add(std::string value) {
    this->values.push_back(std::make_unique<JSONString>(value));
}

void JSONArray::add(const char * value) {
    this->values.push_back(std::make_unique<JSONString>(value));
}

void JSONArray::add(int value) {
    this->values.push_back(std::make_unique<JSONNumber>(value));
}

void JSONArray::add(float value) {
    this->values.push_back(std::make_unique<JSONNumber>(value));
}

void JSONArray::add(double value) {
    this->values.push_back(std::make_unique<JSONNumber>(value));
}

void JSONArray::add(bool value) {
    this->values.push_back(std::make_unique<JSONBoolean>(value));
}

void JSONArray::add(std::initializer_list<std::string> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONString>(val));
    }
}

void JSONArray::add(std::initializer_list<const char*> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONString>(val));
    }
}

void JSONArray::add(std::initializer_list<int> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
}

void JSONArray::add(std::initializer_list<float> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
}

void JSONArray::add(std::initializer_list<double> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONNumber>(val));
    }
}

void JSONArray::add(std::initializer_list<bool> values) {
    for (const auto& val : values) {
        this->values.push_back(std::make_unique<JSONBoolean>(val));
    }
}
