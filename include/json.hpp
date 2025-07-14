#include <memory>
#include <string>
#include <vector>
#include <map>
#include <any>

class Value {
public:
    Value * parse_file(const std::string& filename);

    virtual ~Value() = 0;
    virtual Value* parse(const std::string& jsonString) = 0;
    virtual std::string toString() const = 0;
    virtual std::string toJson() const = 0;;

    friend std::ostream& operator<<(std::ostream& os, const Value& value);
    friend std::istream& operator>>(std::istream& is, Value& value);
};

class JSONNullable : public Value {
public:
    JSONNullable();
    JSONNullable(const std::string& json_string);
    ~JSONNullable();

    std::string toString() const override;
    std::string toJson() const override;
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
    std::string toJson() const override;
    JSONString* parse(const std::string& json_string) override;
};

class JSONNumber : public Value {
private:
    double value;
public:
    JSONNumber();
    JSONNumber(int value);
    JSONNumber(double value);
    JSONNumber(const std::string& json_string);
    JSONNumber(const Value& value);
    ~JSONNumber();

    std::string toString() const override;
    std::string toJson() const override;
    JSONNumber* parse(const std::string& json_string) override;
};

class JSONBoolean : public Value {
private:
    bool value;
public:
    JSONBoolean();
    JSONBoolean(const bool value);
    JSONBoolean(const std::string& json_string);
    ~JSONBoolean();

    std::string toString() const override;
    std::string toJson() const override;
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
    std::string toJson() const override;
    JSONArray* parse(const std::string& json_tring) override;

    Value& operator[](int index);
    int size() const;
    void add(std::unique_ptr<Value> value);
};

class JSONObject : public Value {
private:
    std::map<std::string, std::unique_ptr<Value>> values;
public:
    JSONObject();
    JSONObject(JSONObject* value);
    JSONObject(const std::string& json_string);
    ~JSONObject();

    std::string toString() const override;
    std::string toJson() const override;
    JSONObject* parse(const std::string& json_tring) override;

    Value& operator[](std::string key);
    int size() const;
    void add(std::string key, std::unique_ptr<Value> value);
};
