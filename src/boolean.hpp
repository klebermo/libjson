#ifndef boolean_hpp
#define boolean_hpp

#include "number.hpp"

class JSONBoolean : public Value {
private:
    bool value;
public:
    JSONBoolean();
    JSONBoolean(const std::string& json_string);
    ~JSONBoolean();
    bool getValue();
    std::string toString() const override;
    JSONBoolean* parse(const std::string& json_string) override;
};

#endif
