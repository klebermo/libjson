#ifndef value_hpp
#define value_hpp

#include <vector>
#include <map>
#include <string>
#include <string_view>
#include <fstream>

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
    virtual ~Value() = 0;
    Type getType();
    Value * parse_file(const std::string& filename);
    virtual std::string toString() const = 0;
    virtual Value* parse(const std::string& jsonString) = 0;
};

std::string_view ltrim(std::string_view str);
std::string_view rtrim(std::string_view str);
std::string_view trim(std::string_view str);

#endif
