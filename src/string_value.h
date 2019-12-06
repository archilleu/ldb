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
    StringValue(const StringValue& other);
    StringValue(StringValue&& other);
    StringValue& operator=(const StringValue& other);
    StringValue& operator=(StringValue&& other);
    virtual ~StringValue();

    void Swap(StringValue& other);

public:
    const std::string& val();

    int64_t AsInt();
    double AsDouble();

    static StringValuePtr AsStringPtr(const ValuePtr& value);

public:
    const static std::shared_ptr<StringValue> NullPtr;

private:
    virtual void InitPayload();
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_STRING_VALUE_H_
