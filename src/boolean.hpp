#ifndef boolean_hpp
#define boolean_hpp

#include "number.hpp"

class JSONBoolean : public Value {
private:
    bool value;
public:
    JSONBoolean();
    JSONBoolean(const std::string& json_string);
    JSONBoolean(bool value);
    ~JSONBoolean();

    JSONBoolean* parse(const std::string& json_string) override;
    std::string toString() const override;
    std::string toJson() const override;
};

#endif
