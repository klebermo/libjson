#ifndef string_hpp
#define string_hpp

#include "nullable.hpp"

class JSONString : public Value {
private:
    std::string value;
public:
    JSONString();
    JSONString(const JSONString& other);
    JSONString(const std::string& value);
    ~JSONString();

    JSONString* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;
};

#endif
