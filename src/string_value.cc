//---------------------------------------------------------------------------
#include "string_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
StringValue::StringValue()
:   Value(STRING, INT)
{
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(const char* str)
:   Value(STRING, RAW)
{
    this->val_.string->assign(str);
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(const char* ptr, size_t len)
:   Value(STRING, RAW)
{
    this->val_.string->assign(ptr, len);
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(const std::string& str)
:   Value(STRING, RAW)
{
    this->val_.string->assign(str);
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(int32_t value)
:   Value(STRING, INT)
{
    //TODO:use shared int

    this->val_.string = reinterpret_cast<String*>(value);
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(int64_t value)
:   Value(STRING, INT)
{
    //TODO:use shared int

    this->val_.string = reinterpret_cast<String*>(value);
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(size_t value)
:   Value(STRING, INT)
{
    //TODO:use shared int

    this->val_.string = reinterpret_cast<String*>(value);
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(double value)
:   Value(STRING, RAW)
{
    std::string str = std::to_string(value);
    this->val_.string->assign(str);
    return;
}
//---------------------------------------------------------------------------
StringValue::~StringValue()
{
    return;
}
//---------------------------------------------------------------------------
StringValue& StringValue::operator=(const char* str)
{
    if(RAW == this->encoding_)
    {
        this->val_.string->assign(str);
    }
    else
    {
        this->encoding_ = RAW;
        this->val_.string = new String(str);
    }

    return *this;
}
//---------------------------------------------------------------------------
StringValue& StringValue::operator=(const String& str)
{
    *this = str.c_str();
    return *this;
}
//---------------------------------------------------------------------------
StringValue& StringValue::operator=(const int32_t value)
{
    return *this = static_cast<int64_t>(value);
}
//---------------------------------------------------------------------------
StringValue& StringValue::operator=(const int64_t value)
{
    if(INT == this->encoding_)
    {
        this->val_.string = reinterpret_cast<String*>(value);
    }
    else
    {
        this->val_.string->assign(std::to_string(value));
    }

    return *this;
}
//---------------------------------------------------------------------------
StringValue& StringValue::operator=(const double value)
{
    std::string str = std::to_string(value);
    if(INT == this->encoding_)
    {
        this->encoding_ = RAW;
        this->val_.string = new String(str);
    }
    else
    {
        this->val_.string->assign(str);
    }

    return *this;
}
//---------------------------------------------------------------------------
const std::string& StringValue::val()
{
    //如果是INT编码，则转换为RAW编码，因为返回值是字符串引用，INT内部没有空间
    if(INT == this->encoding_)
    {
        this->encoding_ = Value::Encoding::RAW;
        if(0 == this->val_.string)
            this->val_.string = new String();
        else
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
    //无参构造函数
    if(INT == this->encoding_)
    {
        return 0;
    }

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

}//namespace db
//---------------------------------------------------------------------------
