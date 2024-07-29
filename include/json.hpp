#include <memory>
#include <string>
#include <vector>
#include <map>
#include <any>

enum Type {
    object,
    array,
    string,
    number,
    boolean,
    null
};

class Value {
protected:
    Type type;
public:
    virtual ~Value() = 0;
    Type getType();
    Value * parse_file(const std::string& filename);
    virtual std::string toString() const = 0;
    virtual Value* parse(const std::string& jsonString) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Value& value);
    friend std::istream& operator>>(std::istream& is, Value& value);

    virtual Value& operator[](int index);
    virtual Value& operator[](const std::string key);
};

class JSONNullable : public Value {
public:
    JSONNullable();
    JSONNullable(const std::string& json_string);
    ~JSONNullable();

    std::string toString() const override;
    JSONNullable* parse(const std::string& json_string) override;
};

class JSONString : public Value {
private:
    std::string value;
public:
    JSONString();
    JSONString(const std::string& json_string);
    ~JSONString();

    std::string toString() const override;
    JSONString* parse(const std::string& json_string) override;
};

class JSONNumber : public Value {
private:
    double value;
public:
    JSONNumber();
    JSONNumber(const std::string& json_string);
    ~JSONNumber();

    std::string toString() const override;
    JSONNumber* parse(const std::string& json_string) override;
};

class JSONBoolean : public Value {
private:
    bool value;
public:
    JSONBoolean();
    JSONBoolean(const std::string& json_string);
    ~JSONBoolean();

    std::string toString() const override;
    JSONBoolean* parse(const std::string& json_string) override;
};

class JSONArray : public Value {
private:
    std::vector<std::unique_ptr<Value>> values;
public:
    JSONArray();
    JSONArray(JSONArray* array);
    JSONArray(const std::string& json_string);
    ~JSONArray();

    std::string toString() const override;
    JSONArray* parse(const std::string& json_tring) override;

    JSONArray& operator+(std::unique_ptr<Value> value);
    JSONArray& operator+(const char* value);

    Value& operator[](int index);
};

class JSONObject : public Value {
private:
    std::map<const std::string, std::unique_ptr<Value>> values;
public:
    JSONObject();
    JSONObject(JSONObject* value);
    JSONObject(const std::string& json_string);
    ~JSONObject();

    std::string toString() const override;
    JSONObject* parse(const std::string& json_tring) override;

    JSONObject& operator+(std::pair<const std::string, std::unique_ptr<Value>> pair);
    JSONObject& operator+(std::pair<const std::string, std::string> pair);
    JSONObject& operator+(std::pair<const std::string, double> pair);
    JSONObject& operator+(std::pair<const std::string, JSONArray*> pair);

    Value& operator[](std::string key);
};
