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
class ZSetValue;
class HashValue;
class ListValue;
using ValuePtr = std::shared_ptr<Value>;
using StringValuePtr = std::shared_ptr<StringValue>;
using SetValuePtr = std::shared_ptr<SetValue>;
using ZSetValuePtr = std::shared_ptr<ZSetValue>;
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
    ListValuePtr AsListPtr() const;
    SetValuePtr AsSetPtr() const;
    ZSetValuePtr AsZSetPtr() const;

    std::string ToString() const;

private:
    std::string AddTabs(int deep) const;
    std::string ToString(int deep) const;

    template<typename T> std::string UnaryContainerToString(const T& val, int deep) const;
    template<typename T> std::string BinaryContainerToString(const T& val, int deep) const;

private:
    ValuePtr object_;

    template<typename T, typename... Args>
    friend ObjectPtr MakeObject(Args&& ... args);
};
//---------------------------------------------------------------------------
template<typename T, typename... Args>
ObjectPtr MakeObject(Args&& ... args)
{
    ObjectPtr op;
    op.object_ = std::make_shared<T>(args...);
    return op;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_VALUE_PTR_H_
