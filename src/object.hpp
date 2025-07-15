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

    JSONObject(std::initializer_list<std::pair<std::string, std::string>> values);
    JSONObject(std::initializer_list<std::pair<std::string, const char*>> values);
    JSONObject(std::initializer_list<std::pair<std::string, int>> values);
    JSONObject(std::initializer_list<std::pair<std::string, float>> values);
    JSONObject(std::initializer_list<std::pair<std::string, double>> values);
    JSONObject(std::initializer_list<std::pair<std::string, bool>> values);

    JSONObject& operator=(std::initializer_list<std::pair<std::string, std::string>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, const char*>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, int>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, float>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, double>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, bool>> values);

    JSONObject& operator+=(std::pair<std::string, std::string> value);
    JSONObject& operator+=(std::pair<std::string, const char*> value);
    JSONObject& operator+=(std::pair<std::string, int> value);
    JSONObject& operator+=(std::pair<std::string, float> value);
    JSONObject& operator+=(std::pair<std::string, double> value);
    JSONObject& operator+=(std::pair<std::string, bool> value);
    JSONObject& operator+=(std::pair<std::string, JSONObject> value);
    JSONObject& operator+=(std::pair<std::string, JSONArray> value);

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

    void add(std::string key, std::initializer_list<std::string> values);
    void add(std::string key, std::initializer_list<const char*> values);
    void add(std::string key, std::initializer_list<int> values);
    void add(std::string key, std::initializer_list<float> values);
    void add(std::string key, std::initializer_list<double> values);
    void add(std::string key, std::initializer_list<bool> values);


};

#endif
