#ifndef value_hpp
#define value_hpp

#include <string>
#include <vector>
#include <map>
#include <any>

#include <string_view>
#include <fstream>
#include <memory>

enum Type {
    object,
    array,
    string,
    number,
    boolean,
    nullable
};

class Value {
protected:
    Type type;
public:
    Value();
    Value(Value* value);
    virtual ~Value() = 0;
    Type getType();
    Value * parse_file(const std::string& filename);
    virtual std::string toString() const = 0;
    virtual Value* parse(const std::string& jsonString) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Value& value);
    friend std::istream& operator>>(std::istream& is, Value& value);

    virtual Value& operator[](int index);
    virtual Value& operator[](const std::string key);
};

std::string_view ltrim(std::string_view str);
std::string_view rtrim(std::string_view str);
std::string_view trim(std::string_view str);

#endif
