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

class JSONNullable : public Value {
public:
    JSONNullable();
    JSONNullable(const JSONNullable& other);
    ~JSONNullable();

    JSONNullable* parse(const std::string& json_string) override;
    std::unique_ptr<Value> clone() const override;
    std::string toString() const override;
    std::string toJson() const override;
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
};

class JSONArray : public Value {
private:
    std::vector<std::unique_ptr<Value>> values;
public:
    JSONArray();
    JSONArray(JSONArray* array);
    ~JSONArray();

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

    void add(const std::string values[]);
    void add(const char * values[]);
    void add(const int values[]);
    void add(const float values[]);
    void add(const double values[]);
    void add(const bool values[]);
};

class JSONObject : public Value {
private:
    std::map<std::string, std::unique_ptr<Value>> values;
public:
    JSONObject();
    JSONObject(JSONObject* value);
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
