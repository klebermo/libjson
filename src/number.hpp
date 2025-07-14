#ifndef number_hpp
#define number_hpp

#include "string.hpp"

class JSONNumber : public Value {
private:
    double value;
public:
    JSONNumber();
    JSONNumber(int value);
    JSONNumber(double value);
    JSONNumber(const std::string& json_string);
    JSONNumber(const Value& value);
    ~JSONNumber();

    JSONNumber* parse(const std::string& json_string) override;
    std::string toString() const override;
    std::string toJson() const override;
};

#endif
