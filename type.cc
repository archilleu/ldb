//---------------------------------------------------------------------------
#include "type.h"
//---------------------------------------------------------------------------
namespace db
{
//---------------------------------------------------------------------------
inline void Object::SetBoolean(bool val)
{
    assert(TYPE_BOOLEAN == type_);

    if(obj_.unique())
        *std::static_pointer_cast<bool>(obj_) = val;
    else
        obj_ = std::make_shared<bool>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetInt(int64_t val)
{
    assert(TYPE_INT == type_);

    if(obj_.unique())
        *std::static_pointer_cast<int64_t>(obj_) = val;
    else
        obj_ = std::make_shared<int64_t>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetUInt(uint64_t val)
{
    assert(TYPE_UINT == type_);

    if(obj_.unique())
        *std::static_pointer_cast<uint64_t>(obj_) = val;
    else
        obj_ = std::make_shared<uint64_t>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetFloat(double val)
{
    assert(TYPE_FLOAT == type_);

    if(obj_.unique())
        *std::static_pointer_cast<double>(obj_) = val;
    else
        obj_ = std::make_shared<double>(val);

    return;
}
//---------------------------------------------------------------------------

inline void Object::SetBinary(const Binary& val)
{
    assert(TYPE_BINARY == type_);

    if(obj_.unique())
        *std::static_pointer_cast<Binary>(obj_) = val;
    else
        obj_ = std::make_shared<Binary>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetBinary(Binary&& val)
{
    assert(TYPE_BINARY == type_);

    if(obj_.unique())
        *std::static_pointer_cast<Binary>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<Binary>(std::move(val));

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetString(const String& val)
{
    assert(TYPE_STRING == type_);

    if(obj_.unique())
        *std::static_pointer_cast<String>(obj_) = val;
    else
        obj_ = std::make_shared<String>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetString(String&& val)
{
    assert(TYPE_STRING == type_);

    if(obj_.unique())
        *std::static_pointer_cast<String>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<String>(std::move(val));

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetList(const List& val)
{
    assert(TYPE_LIST == type_);

    if(obj_.unique())
        *std::static_pointer_cast<List>(obj_) = val;
    else
        obj_ = std::make_shared<List>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetList(List&& val)
{
    assert(TYPE_LIST == type_);

    if(obj_.unique())
        *std::static_pointer_cast<List>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<List>(std::move(val));

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetSet(const Set& val)
{
    assert(TYPE_SET == type_);

    if(obj_.unique())
        *std::static_pointer_cast<Set>(obj_) = val;
    else
        obj_ = std::make_shared<Set>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetSet(Set&& val)
{
    assert(TYPE_SET == type_);

    if(obj_.unique())
        *std::static_pointer_cast<Set>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<Set>(std::move(val));

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetZSet(const ZSet& val)
{
    assert(TYPE_ZSET == type_);

    if(obj_.unique())
        *std::static_pointer_cast<ZSet>(obj_) = val;
    else
        obj_ = std::make_shared<ZSet>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetZSet(ZSet&& val)
{
    assert(TYPE_ZSET == type_);

    if(obj_.unique())
        *std::static_pointer_cast<ZSet>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<ZSet>(std::move(val));

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetHash(const Hash& val)
{
    assert(TYPE_HASH == type_);

    if(obj_.unique())
        *std::static_pointer_cast<Hash>(obj_) = val;
    else
        obj_ = std::make_shared<Hash>(val);

    return;
}
//---------------------------------------------------------------------------
inline void Object::SetHash(Hash&& val)
{
    assert(TYPE_HASH == type_);

    if(obj_.unique())
        *std::static_pointer_cast<Hash>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<Hash>(std::move(val));

    return;
}
//---------------------------------------------------------------------------
inline std::size_t HashFunc::operator()(const Object& obj) const
{
    switch(obj.type())
    {
    case TYPE_BOOLEAN:
        {
            std::hash<std::shared_ptr<bool> > hash_fn;
            return hash_fn(std::static_pointer_cast<bool>(obj.obj()));
        }

    case TYPE_INT:
        {
            std::hash<std::shared_ptr<int64_t> > hash_fn;
            return hash_fn(std::static_pointer_cast<int64_t>(obj.obj()));
        }

    case TYPE_UINT:
        {
            std::hash<std::shared_ptr<uint64_t> > hash_fn;
            return hash_fn(std::static_pointer_cast<uint64_t>(obj.obj()));
        }

    case TYPE_FLOAT:
        {
            std::hash<std::shared_ptr<double> > hash_fn;
            return hash_fn(std::static_pointer_cast<double>(obj.obj()));
        }

    case TYPE_BINARY:
        {
            std::hash<std::shared_ptr<Binary> > hash_fn;
            return hash_fn(std::static_pointer_cast<Binary>(obj.obj()));
        }

    case TYPE_STRING:
        {
            std::hash<std::shared_ptr<String> > hash_fn;
            return hash_fn(std::static_pointer_cast<String>(obj.obj()));
        }

    case TYPE_LIST:
        {
            std::hash<std::shared_ptr<List> > hash_fn;
            return hash_fn(std::static_pointer_cast<List>(obj.obj()));
        }

    case TYPE_SET:
        {
            std::hash<std::shared_ptr<Set> > hash_fn;
            return hash_fn(std::static_pointer_cast<Set>(obj.obj()));
        }

    case TYPE_ZSET:
        {
            std::hash<std::shared_ptr<ZSet> > hash_fn;
            return hash_fn(std::static_pointer_cast<ZSet>(obj.obj()));
        }

    case TYPE_HASH:
        {
            std::hash<std::shared_ptr<Hash> > hash_fn;
            return hash_fn(std::static_pointer_cast<Hash>(obj.obj()));
        }

    default:
        assert(0);
        return 0;
    }
}
//---------------------------------------------------------------------------
inline bool EqualFunc::operator()(const Object& left, const Object& right)
{
    if(left.type() == right.type())
    {
        switch(left.type())
        {

        case TYPE_BOOLEAN: return std::static_pointer_cast<bool>(left.obj()) == std::static_pointer_cast<bool>(right.obj());
        case TYPE_INT: return std::static_pointer_cast<int64_t>(left.obj()) == std::static_pointer_cast<int64_t>(right.obj());
        case TYPE_UINT: return std::static_pointer_cast<uint64_t>(left.obj()) == std::static_pointer_cast<uint64_t>(right.obj());
        case TYPE_FLOAT: return std::static_pointer_cast<double>(left.obj()) == std::static_pointer_cast<double>(right.obj());
        case TYPE_BINARY: return std::static_pointer_cast<Binary>(left.obj()) == std::static_pointer_cast<Binary>(right.obj());
        case TYPE_STRING: return std::static_pointer_cast<String>(left.obj()) == std::static_pointer_cast<String>(right.obj());
        case TYPE_LIST: return std::static_pointer_cast<List>(left.obj()) == std::static_pointer_cast<List>(right.obj());
        case TYPE_SET: return std::static_pointer_cast<Set>(left.obj()) == std::static_pointer_cast<Set>(right.obj());
        case TYPE_ZSET: return std::static_pointer_cast<ZSet>(left.obj()) == std::static_pointer_cast<ZSet>(right.obj());
        case TYPE_HASH: return std::static_pointer_cast<Hash>(left.obj()) == std::static_pointer_cast<Hash>(right.obj());
        default:
            assert(0);
            return true;
        }
    }
    else
        return false;
}
//---------------------------------------------------------------------------
}//namespace db
