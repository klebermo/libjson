#include "object.hpp"

JSONObject::JSONObject() {}

JSONObject::JSONObject(const JSONObject& value) {
    for (const auto& [key, val] : value.values) {
        std::unique_ptr<Value> newItem = val->clone();
        values[key] = std::move(newItem);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, std::string>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONString>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, const char*>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONString>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, int>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, float>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, double>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, bool>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONBoolean>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSONString>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONString>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSONNumber>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSONBoolean>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONBoolean>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSONArray>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONArray>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSONObject>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONObject>(val);
    }
}

JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSONNullable>> values) {
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNullable>(val);
    }
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, std::string>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONString>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, const char*>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONString>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, int>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, float>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, double>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, bool>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONBoolean>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, JSONString>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONString>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, JSONNumber>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNumber>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, JSONBoolean>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONBoolean>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, JSONArray>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONArray>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, JSONObject>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONObject>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator=(std::initializer_list<std::pair<std::string, JSONNullable>> values) {
    this->values.clear();
    for (const auto& [key, val] : values) {
        this->values[key] = std::make_unique<JSONNullable>(val);
    }
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, std::string> value) {
    this->values[value.first] = std::make_unique<JSONString>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, const char*> value) {
    this->values[value.first] = std::make_unique<JSONString>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, int> value) {
    this->values[value.first] = std::make_unique<JSONNumber>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, float> value) {
    this->values[value.first] = std::make_unique<JSONNumber>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, double> value) {
    this->values[value.first] = std::make_unique<JSONNumber>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, bool> value) {
    this->values[value.first] = std::make_unique<JSONBoolean>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, JSONString> value) {
    this->values[value.first] = std::make_unique<JSONString>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, JSONNumber> value) {
    this->values[value.first] = std::make_unique<JSONNumber>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, JSONBoolean> value) {
    this->values[value.first] = std::make_unique<JSONBoolean>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, JSONArray> value) {
    this->values[value.first] = std::make_unique<JSONArray>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, JSONObject> value) {
    this->values[value.first] = std::make_unique<JSONObject>(value.second);
    return *this;
}

JSONObject& JSONObject::operator+=(std::pair<std::string, JSONNullable> value) {
    this->values[value.first] = std::make_unique<JSONNullable>(value.second);
    return *this;
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
