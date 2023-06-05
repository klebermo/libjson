#ifndef object_hpp
#define object_hpp

#include "array.hpp"

class JSONObject : public Value {
private:
    std::map<const std::string, const Value*> values;
public:
    JSONObject();
    JSONObject(const std::string& json_string);
    ~JSONObject();
    std::map<const std::string, const Value*> getValues();

    void add(const std::string& key, const Value* value);
    const Value* get(const std::string key);

    std::string toString() const override;
    JSONObject* parse(const std::string& json_tring) override;
};

#endif
