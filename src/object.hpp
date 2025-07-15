#ifndef object_hpp
#define object_hpp

#include "array.hpp"

class JSONArray;

class JSONObject : public Value {
private:
    std::map<std::string, std::unique_ptr<Value>> values;
public:
    JSONObject();
    JSONObject(const JSONObject& value);
    ~JSONObject();

    JSONObject* parse(const std::string& json_tring) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    Value& operator[](std::string key);

    int size() const;
    void add(std::string key, std::unique_ptr<Value> value);

    void add(std::string key, std::string value);
    void add(std::string key, const char * value);
    void add(std::string key, int value);
    void add(std::string key, float value);
    void add(std::string key, double value);
    void add(std::string key, bool value);

    void add(std::string key, std::string values[]);
    void add(std::string key, const char * values[]);
    void add(std::string key, int values[]);
    void add(std::string key, float values[]);
    void add(std::string key, double values[]);
    void add(std::string key, bool values[]);
};

#endif
