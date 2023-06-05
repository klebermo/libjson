#include "value.hpp"

Value::~Value() {
    //
}

Type Value::getType()  {
        return this->type;
}
