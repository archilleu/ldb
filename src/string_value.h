//---------------------------------------------------------------------------
#ifndef DB_STRING_VALUE_H_
#define DB_STRING_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
//string pointer define
using StringValuePtr = std::shared_ptr<class StringValue>;
//---------------------------------------------------------------------------
class StringValue : public Value
{
public:
    StringValue();
    StringValue(const char* str);
    StringValue(const char* ptr, size_t len);
    StringValue(const std::string& str);
    StringValue(int32_t value);
    StringValue(int64_t value);
    StringValue(double value);
    StringValue(StringValue& other)=default;
    StringValue(StringValue&& other)=default;
    StringValue& operator=(const StringValue& other)=default;
    StringValue& operator=(StringValue&& other)=default;
    virtual ~StringValue();

public:
    const std::string& val();

    int64_t AsInt();
    double AsDouble();

    static StringValuePtr AsStringPtr(const ValuePtr& value);

public:
    const static std::shared_ptr<StringValue> NullPtr;
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_STRING_VALUE_H_
