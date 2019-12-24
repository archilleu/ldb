//---------------------------------------------------------------------------
#ifndef DB_STRING_VALUE_H_
#define DB_STRING_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

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
    StringValue(size_t value);
    StringValue(double value);
    StringValue(StringValue& other)=default;
    StringValue(StringValue&& other)=default;
    StringValue& operator=(const StringValue& other)=default;
    StringValue& operator=(StringValue&& other)=default;
    virtual ~StringValue();

    StringValue& operator=(const char* str);
    StringValue& operator=(const String& str);
    StringValue& operator=(const int32_t value);
    StringValue& operator=(const int64_t value);
    StringValue& operator=(const double value);

public:
    const char* val() const;

    std::string AsString() const;
    int64_t AsInt() const;
    double AsDouble() const;

private:
    bool IsNumber(const char* value, size_t len) const;
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_STRING_VALUE_H_
