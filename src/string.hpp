#ifndef string_hpp
#define string_hpp

#include "nullable.hpp"

class JSONString : public Value {
private:
    std::string value;
public:
    JSONString();
    JSONString(const std::string& json_string);
    ~JSONString();

    JSONString* parse(const std::string& json_string) override;
    std::string toString() const override;
    std::string toJson() const override;
};

#endif
