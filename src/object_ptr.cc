//---------------------------------------------------------------------------
#include "../thirdpart/base/include/function.h"
#include "value.h"
#include "object_ptr.h"
#include "string_value.h"
#include "set_value.h"
#include "zset_value.h"
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
ZSetValuePtr ObjectPtr::AsZSetPtr() const
{
    return std::dynamic_pointer_cast<ZSetValue>(object_);
}
//---------------------------------------------------------------------------
std::string ObjectPtr::ToString() const
{
    return object_->ToString();
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
