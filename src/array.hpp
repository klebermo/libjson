#ifndef array_hpp
#define array_hpp

#include "boolean.hpp"
#include "object.hpp"

class JSONArray : public Value {
private:
    std::vector<std::unique_ptr<Value>> values;
public:
    JSONArray();
    JSONArray(JSONArray* value);
    JSONArray(const std::string& json_string);
    ~JSONArray();

    std::string toString() const override;
    JSONArray* parse(const std::string& json_tring) override;

    JSONArray& operator+(std::unique_ptr<Value> value);
    JSONArray& operator+(const char* value);

    Value& operator[](int index) override;
};

#endif
