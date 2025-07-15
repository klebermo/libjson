#ifndef array_hpp
#define array_hpp

#include "boolean.hpp"
#include "object.hpp"

class JSONObject;

class JSONArray : public Value {
private:
    std::vector<std::unique_ptr<Value>> values;
public:
    JSONArray();
    JSONArray(const JSONArray& value);
    ~JSONArray();

    JSONArray(std::initializer_list<std::string> values);
    JSONArray(std::initializer_list<const char*> values);
    JSONArray(std::initializer_list<int> values);
    JSONArray(std::initializer_list<float> values);
    JSONArray(std::initializer_list<double> values);
    JSONArray(std::initializer_list<bool> values);

    JSONArray& operator=(std::initializer_list<std::string> values);
    JSONArray& operator=(std::initializer_list<const char*> values);
    JSONArray& operator=(std::initializer_list<int> values);
    JSONArray& operator=(std::initializer_list<float> values);
    JSONArray& operator=(std::initializer_list<double> values);
    JSONArray& operator=(std::initializer_list<bool> values);

    JSONArray& operator+=(std::string value);
    JSONArray& operator+=(const char * value);
    JSONArray& operator+=(int value);
    JSONArray& operator+=(float value);
    JSONArray& operator+=(double value);
    JSONArray& operator+=(bool value);
    JSONArray& operator+=(const JSONArray& value);
    JSONArray& operator+=(const JSONObject& value);

    JSONArray* parse(const std::string& json_tring) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    Value& operator[](int index);

    int size() const;
    void add(std::unique_ptr<Value> value);

    void add(std::string value);
    void add(const char * value);
    void add(int value);
    void add(float value);
    void add(double value);
    void add(bool value);

    void add(std::initializer_list<std::string> values);
    void add(std::initializer_list<const char*> values);
    void add(std::initializer_list<int> values);
    void add(std::initializer_list<float> values);
    void add(std::initializer_list<double> values);
    void add(std::initializer_list<bool> values);
};

#endif
