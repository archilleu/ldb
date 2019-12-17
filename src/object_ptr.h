//---------------------------------------------------------------------------
#ifndef DB_VALUE_PTR_H_
#define DB_VALUE_PTR_H_
//---------------------------------------------------------------------------
#include <memory>
//---------------------------------------------------------------------------
namespace db
{

class Value;
class StringValue;
class SetValue;
class HashValue;
class ListValue;
using ValuePtr = std::shared_ptr<Value>;
using StringValuePtr = std::shared_ptr<StringValue>;
using SetValuePtr = std::shared_ptr<SetValue>;
using HashValuePtr = std::shared_ptr<HashValue>;
using ListValuePtr = std::shared_ptr<ListValue>;
//---------------------------------------------------------------------------
class ObjectPtr
{
public:
    //copy
    ObjectPtr()=default;
    ObjectPtr(Value* value);

public:
    ObjectPtr Dup();
    
    ValuePtr object() const { return object_; }

    StringValuePtr AsStringPtr() const;
    HashValuePtr AsHashPtr() const;
    //ListValuePtr AsListPtr() const;
    SetValuePtr AsSetPtr() const;
    
private:
    ValuePtr object_;
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_VALUE_PTR_H_
