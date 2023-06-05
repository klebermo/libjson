#include "value.hpp"

Value::~Value() {
    //
}

Type Value::getType()  {
        return this->type;
}

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
