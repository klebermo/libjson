#ifndef value_hpp
#define value_hpp

#include <string>
#include <vector>
#include <map>
#include <any>
#include <regex>
#include <string_view>
#include <fstream>
#include <memory>
#include <algorithm>
#include <cctype>

class Value {
public:
    Value * parse_file(const std::string& filename);
    virtual ~Value() = default;

    virtual Value* parse(const std::string& jsonString) = 0;
    virtual std::unique_ptr<Value> clone() const = 0;
    virtual std::string toString() const = 0;
    virtual std::string toJson() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Value& value);
    friend std::istream& operator>>(std::istream& is, Value& value);
};

std::string_view ltrim(std::string_view str);
std::string_view rtrim(std::string_view str);
std::string_view trim(std::string_view str);

void skip_whitespace(const std::string& str, size_t& i);
std::string parse_string(const std::string& str, size_t& i);
std::string parse_primitive(const std::string& str, size_t& i);
std::string parse_block(const std::string& str, size_t& i, char open, char close);
std::string parse_value(const std::string& str, size_t& i);
bool somenteNumeros(const std::string& str);

#endif
