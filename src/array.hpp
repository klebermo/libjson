#ifndef array_hpp
#define array_hpp

#include "boolean.hpp"

class JSONArray : public Value {
private:
    std::vector<const Value*> values;
public:
    JSONArray();
    JSONArray(const std::string& json_string);
    ~JSONArray();
    std::vector<const Value*> getValues();

    void add(const Value* value);
    const Value* get(int index);

    std::string toString() const override;
    JSONArray* parse(const std::string& json_tring) override;
};

#endif
