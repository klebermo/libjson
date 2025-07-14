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

    JSONArray* parse(const std::string& json_tring) override;
    std::string toString() const override;
    std::string toJson() const override;

    Value& operator[](int index);
    int size() const;
    void add(std::unique_ptr<Value> value);
};

#endif
