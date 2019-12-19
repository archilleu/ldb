//---------------------------------------------------------------------------
#include <sstream>
#include "../thirdpart/base/include/function.h"
#include "value.h"
#include "object_ptr.h"
#include "string_value.h"
#include "set_value.h"
#include "hash_value.h"
#include "list_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
ObjectPtr::ObjectPtr(Value* value)
{
    object_.reset(value);
}
//---------------------------------------------------------------------------
ObjectPtr ObjectPtr::Dup()
{
    return ObjectPtr(new Value(*object_));
}
//---------------------------------------------------------------------------
StringValuePtr ObjectPtr::AsStringPtr() const
{
    return std::dynamic_pointer_cast<StringValue>(object_);
}
//---------------------------------------------------------------------------
HashValuePtr ObjectPtr::AsHashPtr() const
{
    return std::dynamic_pointer_cast<HashValue>(object_);
}
//---------------------------------------------------------------------------
ListValuePtr ObjectPtr::AsListPtr() const
{
    return std::dynamic_pointer_cast<ListValue>(object_);
}
//---------------------------------------------------------------------------
SetValuePtr ObjectPtr::AsSetPtr() const
{
    return std::dynamic_pointer_cast<SetValue>(object_);
}
//---------------------------------------------------------------------------
std::string ObjectPtr::ToString() const
{
    return ToString(0);
}
//---------------------------------------------------------------------------
std::string ObjectPtr::AddTabs(int deep) const
{
    std::string str;
    for(int i=0; i<deep; i++)
        str += "\t";

    return str;
}
//---------------------------------------------------------------------------
std::string ObjectPtr::ToString(int deep) const
{
    std::stringstream ss;
    switch(object_->type())
    {
        case Value::LIST:   ss << AddTabs(deep); ss << "[" << std::endl; break;
        case Value::SET:
        case Value::ZSET:   ss << AddTabs(deep); ss << "(" << std::endl; break;
        case Value::HASH:   ss << AddTabs(deep); ss << "{" << std::endl; break;
        case Value::STRING:
        case Value::BINARY:
        default:break;
    }

    switch(object_->type())
    {
        case Value::STRING:    ss << "\"" << AsStringPtr()->val() << "\""; break;
        //case Value::BINARY:    ss << "x\'" << base::BinToString(val_.binary->data(), val_.binary->size()) << "\'"; break;
        case Value::LIST:   ss << UnaryContainerToString(AsListPtr(), deep+1); break;
        case Value::SET:    ss << UnaryContainerToString(AsSetPtr(), deep+1); break;
        //case Value::ZSET:   ss << BinaryContainerToString(AsZSetPtr(), deep+1); break;
        case Value::HASH:   ss << BinaryContainerToString(AsHashPtr(), deep+1); break;
        default:break;
    }

    switch(object_->type())
    {
        case Value::LIST:   ss << AddTabs(deep); ss << "]" << std::endl; break;
        case Value::SET:
        case Value::ZSET:   ss << AddTabs(deep); ss << ")" << std::endl; break;
        case Value::HASH:   ss << AddTabs(deep); ss << "}" << std::endl; break;
        case Value::STRING:
        case Value::BINARY:
        default:break;
    }

    return ss.str();
}
//---------------------------------------------------------------------------
template<typename T>
std::string ObjectPtr::UnaryContainerToString(const T& val, int deep) const
{
    std::stringstream ss;
    for(auto it=val->Begin(); it!=val->End(); it++)
    {
        switch(it->object_->type())
        {
            case Value::STRING: ss << AddTabs(deep) << "\"" << it->AsStringPtr()->val() << "\""; break;
            case Value::BINARY: ss << "x\'" << "\'"; break;
            case Value::LIST:
            case Value::SET:
            case Value::ZSET:
            case Value::HASH:   ss << it->ToString(deep); break;
        }

        ss << "," << std::endl;
    }

    std::string str = ss.str();
    if(2 <= str.size())
    {
        str.pop_back();
        str.pop_back();
    }

    return str;
}
//---------------------------------------------------------------------------
template<typename T>
std::string ObjectPtr::BinaryContainerToString(const T& val, int deep) const
{
    std::stringstream ss;
    for(auto it=val->Begin(); it!=val->End(); it++)
    {
        ss << AddTabs(deep);
        ss << it->first << ":";

        switch(it->second.object_->type())
        {
            case Value::STRING: ss << AddTabs(deep) << "\"" << it->second.AsStringPtr()->val() << "\""; break;
            case Value::BINARY: ss << "x\'" << "\'"; break;
            case Value::LIST:
            case Value::SET:
            case Value::ZSET:
            case Value::HASH:   ss << it->second.ToString(deep); break;
        }

        ss << "," << std::endl;
    }

    std::string str = ss.str();
    if(2 <= str.size())
    {
        str.pop_back();
        str.pop_back();
    }

    return str;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
