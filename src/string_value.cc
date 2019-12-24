//---------------------------------------------------------------------------
#include <cctype>
#include <cstring>
#include "string_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
thread_local char t_cache_val[21];
//---------------------------------------------------------------------------
StringValue::StringValue()
:   Value(STRING, INT)
{
    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(const char* str)
:   Value(STRING)
{
    if(IsNumber(str, strlen(str)))
    {
        this->encoding_ = INT;
        this->InitPayload(0);
        this->val_.string = reinterpret_cast<String*>(::atoll(str));
    }
    else
    {
        this->encoding_ = RAW;
        this->InitPayload(0);
        this->val_.string->assign(str);
    }

    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(const char* ptr, size_t len)
:   Value(STRING)
{
    if(IsNumber(ptr, len))
    {
        this->encoding_ = INT;
        this->InitPayload(0);
        this->val_.string = reinterpret_cast<String*>(::atoll(String(ptr, len).c_str()));
    }
    else
    {
        this->encoding_ = RAW;
        this->InitPayload(0);
        this->val_.string->assign(ptr, len);
    }

    return;
}
//---------------------------------------------------------------------------
StringValue::StringValue(const std::string& str)
:   Value(STRING)
{
    if(IsNumber(str.c_str(), str.length()))
    {
        this->encoding_ = INT;
        this->InitPayload(0);
        this->val_.string = reinterpret_cast<String*>(::atoll(str.c_str()));
    }
    else
    {
        this->encoding_ = RAW;
        this->InitPayload(0);
        this->val_.string->assign(str);
    }

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
const char* StringValue::val() const
{
    if(INT == this->encoding_)
    {
        snprintf(t_cache_val, sizeof(t_cache_val), "%ld", reinterpret_cast<int64_t>(this->val_.string));
        return t_cache_val;
    }
    else
    {
        return this->val_.string->c_str();
    }
}
//---------------------------------------------------------------------------
std::string StringValue::AsString() const
{
    if(INT == this->encoding_)
    {
       return std::to_string(reinterpret_cast<int64_t>(this->val_.string));
    }
    else
    {
        return *(this->val_.string);
    }
}
//---------------------------------------------------------------------------
int64_t StringValue::AsInt() const
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
double StringValue::AsDouble() const
{
    //无参构造函数
    if(INT == this->encoding_)
    {
        return static_cast<double>(reinterpret_cast<int64_t>(this->val_.string));
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
bool StringValue::IsNumber(const char* value, size_t len) const
{
    for(size_t i=0; i<len; i++)
    {
        if(!isdigit(value[i]))
            return false;
    }

    return true;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
