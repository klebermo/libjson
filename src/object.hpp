#ifndef object_hpp
#define object_hpp

#include "array.hpp"

class JSONArray;

class JSONObject : public Value {
private:
    std::map<const std::string, std::unique_ptr<Value>> values;
public:
    JSONObject();
    JSONObject(JSONObject* value);
    JSONObject(const std::string& json_string);
    ~JSONObject();

    void add(const std::string& key, std::unique_ptr<Value> value);
    const Value& get(const std::string key);

    std::string toString() const override;
    JSONObject* parse(const std::string& json_tring) override;

    JSONObject& operator+(std::pair<const std::string, std::unique_ptr<Value>> pair);
    JSONObject& operator+(std::pair<const std::string, std::string> pair);
    JSONObject& operator+(std::pair<const std::string, double> pair);
    JSONObject& operator+(std::pair<const std::string, JSONArray*> pair);

    Value& operator[](std::string key) override;
};

#endif
