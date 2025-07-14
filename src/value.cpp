#include "value.hpp"

Value::~Value() {}

Value * Value::parse_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::in);

    if(!file.is_open()) {
        return nullptr;
    }

    std::string json_string, line;

    while(getline(file, line)) {
        json_string += trim(line);
    }

    return this->parse(json_string);
}

std::ostream& operator<<(std::ostream& os, const Value& value) {
    os << value.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Value& value) {
    std::string jsonString;
    is >> jsonString;
    Value* parsedValue = value.parse(jsonString);
    if (parsedValue) {
        value = std::move(*parsedValue);
        delete parsedValue;
    }
    return is;
}

std::string_view ltrim(std::string_view str)
{
    const auto pos(str.find_first_not_of(" \t\n\r\f\v"));
    str.remove_prefix(std::min(pos, str.length()));
    return str;
}

std::string_view rtrim(std::string_view str)
{
    const auto pos(str.find_last_not_of(" \t\n\r\f\v"));
    str.remove_suffix(std::min(str.length() - pos - 1, str.length()));
    return str;
}

std::string_view trim(std::string_view str)
{
    str = ltrim(str);
    str = rtrim(str);
    return str;
}

void skip_whitespace(const std::string& str, size_t& i) {
    while (i < str.size() && std::isspace(str[i])) ++i;
}

std::string parse_string(const std::string& str, size_t& i) {
    if (str[i] != '"') throw std::runtime_error("Expected '\"'");
    ++i;
    std::string result;
    //result += str[i++];  // Include initial quote
    while (i < str.size()) {
        char c = str[i++];
        if (c == '"' && str[i - 2] != '\\') break;
        result += c;
    }
    return result;
}

std::string parse_primitive(const std::string& str, size_t& i) {
    size_t start = i;
    while (i < str.size() && !std::isspace(str[i]) && str[i] != ',' && str[i] != ']' && str[i] != '}') ++i;
    return str.substr(start, i - start);
}

std::string parse_block(const std::string& str, size_t& i, char open, char close) {
    if (str[i] != open) throw std::runtime_error("Expected block start");
    size_t start = i;
    int depth = 0;
    do {
        if (str[i] == open) ++depth;
        else if (str[i] == close) --depth;
        ++i;
    } while (i < str.size() && depth > 0);
    return str.substr(start, i - start);
}

std::string parse_value(const std::string& str, size_t& i) {
    skip_whitespace(str, i);
    if (str[i] == '"') return parse_string(str, i);
    else if (str[i] == '{') return parse_block(str, i, '{', '}');
    else if (str[i] == '[') return parse_block(str, i, '[', ']');
    else return parse_primitive(str, i);
}

bool somenteNumeros(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}
