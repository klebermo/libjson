#ifndef number_hpp
#define number_hpp

#include "string.hpp"

class JSONNumber : public Value {
private:
    double value;
public:
    JSONNumber();
    JSONNumber(const std::string& json_string);
    ~JSONNumber();
    double getValue();
    std::string toString() const override;
    JSONNumber* parse(const std::string& json_string) override;
};

#endif
