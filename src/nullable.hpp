#ifndef nullable_hpp
#define nullable_hpp

#include "value.hpp"

class JSONNullable : public Value {
public:
    JSONNullable();
    JSONNullable(const std::string& json_string);
    ~JSONNullable();

    JSONNullable* parse(const std::string& json_string) override;
    std::string toString() const override;
    std::string toJson() const override;
};

#endif
