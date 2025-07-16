#include <memory>
#include <string>
#include <vector>
#include <map>
#include <any>

class Value {
public:
    Value * parse_file(const std::string& filename);
    virtual ~Value() = default;

    virtual Value* parse(const std::string& jsonString) = 0;
    virtual std::unique_ptr<Value> clone() const = 0;
    virtual std::string toString() const = 0;
    virtual std::string toJson() const = 0;;

    friend std::ostream& operator<<(std::ostream& os, const Value& value);
    friend std::istream& operator>>(std::istream& is, Value& value);
};

template<typename T>
T value_as(const Value& value) {
    const T* casted = dynamic_cast<const T*>(&value);
    if (!casted) {
        throw std::runtime_error("Invalid type cast");
    }
    return *casted; // cópia
}

class JSONNullable : public Value {
public:
    JSONNullable();
    JSONNullable(const JSONNullable& other);
    ~JSONNullable();

    JSONNullable* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    JSONNullable& operator=(const JSONNullable& other);
    JSONNullable& operator=(std::nullptr_t);
};

class JSONString : public Value {
private:
    std::string value;
public:
    JSONString();
    JSONString(const JSONString& other);
    JSONString(const std::string& value);
    ~JSONString();

    JSONString* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    JSONString& operator=(const JSONString& other);
    JSONString& operator=(const std::string& value);
};

class JSONNumber : public Value {
private:
    double value;
public:
    JSONNumber();
    JSONNumber(const JSONNumber& other);
    JSONNumber(int value);
    JSONNumber(float value);
    JSONNumber(double value);
    ~JSONNumber();

    JSONNumber* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    JSONNumber& operator=(const JSONNumber& other);
    JSONNumber& operator=(int value);
    JSONNumber& operator=(float value);
    JSONNumber& operator=(double value);
    JSONNumber& operator=(const std::string& value);
};

class JSONBoolean : public Value {
private:
    bool value;
public:
    JSONBoolean();
    JSONBoolean(const JSONBoolean& other);
    JSONBoolean(const bool value);
    ~JSONBoolean();

    JSONBoolean* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    JSONBoolean& operator=(const JSONBoolean& other);
    JSONBoolean& operator=(bool value);
};

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

    JSONArray(std::initializer_list<JSONString> values);
    JSONArray(std::initializer_list<JSONNumber> values);
    JSONArray(std::initializer_list<JSONBoolean> values);
    JSONArray(std::initializer_list<JSONArray> values);
    JSONArray(std::initializer_list<JSONObject> values);
    JSONArray(std::initializer_list<JSONNullable> values);

    JSONArray& operator=(std::initializer_list<std::string> values);
    JSONArray& operator=(std::initializer_list<const char*> values);
    JSONArray& operator=(std::initializer_list<int> values);
    JSONArray& operator=(std::initializer_list<float> values);
    JSONArray& operator=(std::initializer_list<double> values);
    JSONArray& operator=(std::initializer_list<bool> values);

    JSONArray& operator=(std::initializer_list<JSONString> values);
    JSONArray& operator=(std::initializer_list<JSONNumber> values);
    JSONArray& operator=(std::initializer_list<JSONBoolean> values);
    JSONArray& operator=(std::initializer_list<JSONArray> values);
    JSONArray& operator=(std::initializer_list<JSONObject> values);
    JSONArray& operator=(std::initializer_list<JSONNullable> values);

    JSONArray& operator+=(std::string value);
    JSONArray& operator+=(const char * value);
    JSONArray& operator+=(int value);
    JSONArray& operator+=(float value);
    JSONArray& operator+=(double value);
    JSONArray& operator+=(bool value);

    JSONArray& operator+=(const JSONString& value);
    JSONArray& operator+=(const JSONNumber& value);
    JSONArray& operator+=(const JSONBoolean& value);
    JSONArray& operator+=(const JSONNullable& value);
    JSONArray& operator+=(const JSONArray& value);
    JSONArray& operator+=(const JSONObject& value);

    JSONArray* parse(const std::string& json_tring) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    Value& operator[](int index);
    int size() const;
};

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

    JSONObject(std::initializer_list<std::pair<std::string, JSONString>> values);
    JSONObject(std::initializer_list<std::pair<std::string, JSONNumber>> values);
    JSONObject(std::initializer_list<std::pair<std::string, JSONBoolean>> values);
    JSONObject(std::initializer_list<std::pair<std::string, JSONArray>> values);
    JSONObject(std::initializer_list<std::pair<std::string, JSONObject>> values);
    JSONObject(std::initializer_list<std::pair<std::string, JSONNullable>> values);

    JSONObject& operator=(std::initializer_list<std::pair<std::string, std::string>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, const char*>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, int>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, float>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, double>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, bool>> values);

    JSONObject& operator=(std::initializer_list<std::pair<std::string, JSONString>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, JSONNumber>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, JSONBoolean>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, JSONArray>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, JSONObject>> values);
    JSONObject& operator=(std::initializer_list<std::pair<std::string, JSONNullable>> values);

    JSONObject& operator+=(std::pair<std::string, std::string> value);
    JSONObject& operator+=(std::pair<std::string, const char*> value);
    JSONObject& operator+=(std::pair<std::string, int> value);
    JSONObject& operator+=(std::pair<std::string, float> value);
    JSONObject& operator+=(std::pair<std::string, double> value);
    JSONObject& operator+=(std::pair<std::string, bool> value);

    JSONObject& operator+=(std::pair<std::string, JSONString> value);
    JSONObject& operator+=(std::pair<std::string, JSONNumber> value);
    JSONObject& operator+=(std::pair<std::string, JSONBoolean> value);
    JSONObject& operator+=(std::pair<std::string, JSONArray> value);
    JSONObject& operator+=(std::pair<std::string, JSONObject> value);
    JSONObject& operator+=(std::pair<std::string, JSONNullable> value);

    JSONObject* parse(const std::string& json_tring) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;

    Value& operator[](std::string key);
    int size() const;
};
