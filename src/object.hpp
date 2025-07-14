#ifndef object_hpp
#define object_hpp

#include "array.hpp"

class JSONArray;

class JSONObject : public Value {
private:
    std::map<std::string, std::unique_ptr<Value>> values;
public:
    JSONObject();
    JSONObject(JSONObject* value);
    JSONObject(const std::string& json_string);
    ~JSONObject();

    JSONObject* parse(const std::string& json_tring) override;
    std::string toString() const override;
    std::string toJson() const override;

    Value& operator[](std::string key);
    int size() const;
    void add(std::string key, std::unique_ptr<Value> value);
};

#endif
