//---------------------------------------------------------------------------
#include "ldb.h"
#include <assert.h>
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
ObjectPtr Ldb::kNullObject = std::make_shared<Object>(TYPE_INT, std::make_shared<int>(1)); //this val just for compare
//---------------------------------------------------------------------------
bool Ldb::UnarySetBoolean(const String& key, bool val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_BOOLEAN, std::make_shared<bool>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnarySetInt(const String& key, int64_t val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_INT, std::make_shared<int64_t>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnarySetUInt(const String& key, uint64_t val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_UINT, std::make_shared<uint64_t>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnarySetFloat(const String& key, double val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_FLOAT, std::make_shared<double>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnarySetBinary(const String& key, const Binary& val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_BINARY, std::make_shared<Binary>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnarySetBinary(const String& key, Binary&& val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_BINARY, std::make_shared<Binary>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnarySetString(const String& key, const String& val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_STRING, std::make_shared<String>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnarySetString(const String& key, String&& val)
{
    ObjectPtr obj_val = std::make_shared<Object>(TYPE_STRING, std::make_shared<String>(val));

    return UnarySet(key, obj_val);
}
//---------------------------------------------------------------------------
bool Ldb::UnaryGetBoolean(const String& key, bool* val)
{
    auto iter = dict_.find(key);
    if(dict_.end() == iter)
        return false;

    if(TYPE_BOOLEAN == iter->second->type())
    {
        *val = *reinterpret_cast<bool*>(iter->second->obj().get());
        return true;
    }
    else
    {
        assert(0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool Ldb::UnaryGetInt(const String& key, int64_t* val)
{
    auto iter = dict_.find(key);
    if(dict_.end() == iter)
        return false;

    if(TYPE_INT == iter->second->type())
    {
        *val = *reinterpret_cast<int64_t*>(iter->second->obj().get());
        return true;
    }
    else
    {
        assert(0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool Ldb::UnaryGetUInt(const String& key, uint64_t* val)
{
    auto iter = dict_.find(key);
    if(dict_.end() == iter)
        return false;

    if(TYPE_UINT == iter->second->type())
    {
        *val = *reinterpret_cast<uint64_t*>(iter->second->obj().get());
        return true;
    }
    else
    {
        assert(0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool Ldb::UnaryGetFloat(const String& key, double* val)
{
    auto iter = dict_.find(key);
    if(dict_.end() == iter)
        return false;

    if(TYPE_FLOAT == iter->second->type())
    {
        *val = *reinterpret_cast<double*>(iter->second->obj().get());
        return true;
    }
    else
    {
        assert(0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool Ldb::UnaryGetBinary(const String& key, Binary* val)
{
    auto iter = dict_.find(key);
    if(dict_.end() == iter)
        return false;

    if(TYPE_BINARY == iter->second->type())
    {
        *val = *reinterpret_cast<Binary*>(iter->second->obj().get());
        return true;
    }
    else
    {
        assert(0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool Ldb::UnaryGetString(const String& key, String* val)
{
    auto iter = dict_.find(key);
    if(dict_.end() == iter)
        return false;

    if(TYPE_STRING == iter->second->type())
    {
        *val = *reinterpret_cast<String*>(iter->second->obj().get());
        return true;
    }
    else
    {
        assert(0);
        return false;
    }
}
//---------------------------------------------------------------------------
inline bool Ldb::UnarySet(const String& key, const ObjectPtr& obj_val)
{
    auto pair = dict_.emplace(key, obj_val);
    if(true == pair.second)
        return true;
    else
    {
        (*pair.first).second = obj_val;
        return false;
    }

    return true;
}

}// namespace db
//---------------------------------------------------------------------------
