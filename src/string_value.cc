//---------------------------------------------------------------------------
#include <climits>
#include <cassert>
#include "string_value.h"
#include <iostream>
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
StringValue::StringValue()
:   Value(STRING)
{
    this->encoding_ = RAW;
    InitPayload();
}
//---------------------------------------------------------------------------
StringValue::StringValue(const char* str)
:   Value(STRING)
{
    this->encoding_ = RAW;
    InitPayload();
    this->val_.string->assign(str);
}
//---------------------------------------------------------------------------
StringValue::StringValue(const char* ptr, size_t len)
:   Value(STRING)
{
    this->encoding_ = RAW;
    InitPayload();
    this->val_.string->assign(ptr, len);
}
//---------------------------------------------------------------------------
StringValue::StringValue(const std::string& str)
:   Value(STRING)
{
    this->encoding_ = RAW;
    InitPayload();
    this->val_.string->assign(str);
}
//---------------------------------------------------------------------------
StringValue::StringValue(int32_t value)
:   Value(STRING)
{
    //TODO:use shared int

    this->encoding_ = INT;
    InitPayload();
    this->val_.string = reinterpret_cast<String*>(value);
}
//---------------------------------------------------------------------------
StringValue::StringValue(int64_t value)
:   Value(STRING)
{
    //TODO:use shared int

    this->encoding_ = INT;
    InitPayload();
    this->val_.string = reinterpret_cast<String*>(value);
}
//---------------------------------------------------------------------------
StringValue::StringValue(double value)
:   Value(STRING)
{
    this->encoding_ = RAW;
    InitPayload();
    std::string str = std::to_string(value);
    this->val_.string->assign(str);
}
//---------------------------------------------------------------------------
StringValue::StringValue(const StringValue& other)
:   Value(STRING)
{
    this->encoding_ = other.encoding_;
    InitPayload();

    if(RAW == this->encoding_)
        *(this->val_.string) = *(other.val_.string);
    else
        this->val_.string = other.val_.string;

    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(StringValue&& other)
:   Value(STRING)
{
    this->encoding_ = INT;
    InitPayload();
    Swap(other);
}
//---------------------------------------------------------------------------
StringValue& StringValue::operator=(const StringValue& other)
{
    if(this == &other)
        return *this;

    StringValue(other).Swap(*this);
    return *this;
}
//---------------------------------------------------------------------------
StringValue& StringValue::operator=(StringValue&& other)
{
    other.Swap(*this);
    return *this;
}
//---------------------------------------------------------------------------
StringValue::~StringValue()
{
    if(INT == this->encoding_)
        return;

    delete this->val_.string;
}
//---------------------------------------------------------------------------
void StringValue::Swap(StringValue& other)
{
    std::swap(this->encoding_, other.encoding_);
    std::swap(this->val_, other.val_);
    std::swap(this->lru_, other.lru_);
}
//---------------------------------------------------------------------------
const Value::String& StringValue::val()
{
    //如果是INT编码，则转换为RAW编码，因为返回值是字符串引用，INT内部没有空间
    if(INT == this->encoding_)
    {
        this->encoding_ = Value::Encoding::RAW;
        this->val_.string = new String(std::to_string(reinterpret_cast<int64_t>(this->val_.string)));
    }

    return *(this->val_.string);
}
//---------------------------------------------------------------------------
int64_t StringValue::AsInt()
{
    if(INT == this->encoding_)
    {
        return reinterpret_cast<int64_t>(this->val_.string);
    }

    if(this->val_.string->empty())
        return 0;

    try
    {
        return std::stoll(this->val_.string->c_str());
    }
    catch(std::exception e)
    {
        return 0;
    }
}
//---------------------------------------------------------------------------
double StringValue::AsDouble()
{
    if(this->val_.string->empty())
        return 0;

    try
    {
        return std::stod(this->val_.string->c_str());
    }
    catch(std::exception e)
    {
        return 0;
    }
}
//---------------------------------------------------------------------------
void StringValue::InitPayload()
{
    assert(this->type() == STRING);

    if(RAW == this->encoding())
        this->val_.string = new String();
    else
        this->val_.string = 0;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
