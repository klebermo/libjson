#include <string>
#include <vector>
#include <map>

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
    virtual std::string toString() const = 0;
    virtual Value* parse(const std::string& jsonString) = 0;
};

class JSONNullable : public Value {
public:
    JSONNullable();
    JSONNullable(const std::string& json_string);
    ~JSONNullable();
    std::string getValue();
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
    std::string getValue();
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
    double getValue();
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
    bool getValue();
    std::string toString() const override;
    JSONBoolean* parse(const std::string& json_string) override;
};

class JSONArray : public Value {
private:
    std::vector<const Value*> values;
public:
    JSONArray();
    JSONArray(const std::string& json_string);
    ~JSONArray();
    std::vector<const Value*> getValues();

    std::string toString() const override;
    JSONArray* parse(const std::string& json_string) override;

    void add(const Value* value);
    const Value* get(int index);
};

class JSONObject : public Value {
private:
    std::map<const std::string, const Value*> values;
public:
    JSONObject();
    JSONObject(const std::string& json_string);
    ~JSONObject();
    std::map<std::string, const Value*> getValues();

    std::string toString() const override;
    JSONObject* parse(const std::string& json_string) override;

    void add(const std::string& key, const Value* value);
    const Value* get(const std::string key);
};
