#ifndef value_hpp
#define value_hpp

#include <vector>
#include <map>
#include <string>
#include <string_view>
#include <iostream>

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
    virtual std::string toString() const = 0;
    virtual Value* parse(const std::string& jsonString) = 0;
};

#endif
