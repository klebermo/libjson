#ifndef array_hpp
#define array_hpp

#include "boolean.hpp"
#include "object.hpp"

class JSONArray : public Value {
private:
    std::vector<std::unique_ptr<Value>> values;
public:
    JSONArray();
    JSONArray(const JSONArray& value);
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

#endif
