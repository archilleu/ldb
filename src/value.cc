//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
size_t Value::HashFunc::operator()(const ObjectPtr& value) const
{
    switch(value.object()->type())
    {
        case STRING:
        {
            switch(value.object()->encoding())
            {
                case RAW:
                {
                    std::hash<String> hash_fn;
                    return hash_fn(*value.object()->val_.string);
                }

                case INT:
                {
                    std::hash<long> hash_fn;
                    return hash_fn(reinterpret_cast<size_t>(value.object()->val_.string));
                }
            
                default:
                    throw type_error();
            }
            break;
        }

        case BINARY:
        case HASH:
        case LIST:
        case SET:
        case ZSET:
        {
            std::hash<void*> hash_fn;
            return hash_fn(value.object()->val_.string);
            break;
        }

        default:
            throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
Value::Value(Type type)
{
    type_ = type;
    lru_ = base::Timestamp::Now();

    return;
}
//---------------------------------------------------------------------------
Value::Value(Type type, Encoding encoding, size_t reserve_size)
{
    type_ = type;
    encoding_ = encoding;
    lru_ = base::Timestamp::Now();

    InitPayload(reserve_size);
    return;
}
//---------------------------------------------------------------------------
Value::Value(const Value& other)
{
    DupPayload(other);
    return;
}
//---------------------------------------------------------------------------
Value::Value(Value&& other)
{
    type_ = other.type_;
    encoding_ = other.encoding_;
    lru_ = other.lru_;
    val_ = other.val_;

    other.type_ = STRING;
    other.encoding_ = INT;
    other.lru_ = base::Timestamp::Invalid();
    other.val_.string = 0;
    return;
}
//---------------------------------------------------------------------------
Value& Value::operator=(const Value& other)
{
    if(this == &other)
        return *this;

    Value(other).Swap(*this);
    return *this;
}
//---------------------------------------------------------------------------
Value& Value::operator=(Value&& other)
{
    if(this == &other)
        return *this;

    //释放旧空间
    ReleasePayload();

    type_ = other.type_;
    encoding_ = other.encoding_;
    lru_ = other.lru_;
    val_ = other.val_;

    other.type_ = STRING;
    other.encoding_ = INT;
    other.lru_ = base::Timestamp::Invalid();
    other.val_.string = 0;
    return *this;
}
//---------------------------------------------------------------------------
Value::~Value()
{
    ReleasePayload();

    val_.string = 0;
    return;
}
//---------------------------------------------------------------------------
bool Value::operator==(const Value& other) const
{
    if(this == &other)
        return true;

    if(type_ != other.type_ )
        return false;

    if(encoding_ != other.encoding_)
        return false;

    if(0==val_.string && 0==other.val_.string)
        return true;
    
    switch(type_)
    {
        case STRING:
        {
            switch(encoding_)
            {
                case RAW:
                    return *val_.string == *other.val_.string;

                case INT:
                    return val_.string == other.val_.string;
            
                default:
                    throw type_error();
            }
            break;
        }

        case BINARY:
        {
            return *val_.binary == *other.val_.binary;
        }

        case HASH:
        {
            switch(encoding_)
            {
                case UNORDERED_MAP:
                    return *val_.hash == *other.val_.hash;

                case ZIPLIST:
                    return *val_.zip_list == *other.val_.zip_list;

                default:
                    throw type_error();
            }
            break;
        }

        case LIST:
        {
            switch(encoding_)
            {
                case LINKED_LIST:
                    return *val_.linked_list == *other.val_.linked_list;

                case ZIPLIST:
                    return *val_.zip_list == *other.val_.zip_list;

                default:
                    throw type_error();
            }
            break;
        }

        case SET:
        {
            switch(encoding_)
            {
                case UNORDERED_SET:
                    return *val_.set == *other.val_.set;

                case INT_SET:
                    return *val_.intset == *other.val_.intset;

                default:
                    break;
            }
            break;
        }

        case ZSET:
        {
            return (val_.sorted_set->list == other.val_.sorted_set->list
                    &&
                    val_.sorted_set->map == other.val_.sorted_set->map
                   );
        }

        default:
            throw type_error();
    }

    return true;
}
//---------------------------------------------------------------------------
void Value::Swap(Value& other)
{
    std::swap(this->encoding_, other.encoding_);
    std::swap(this->val_, other.val_);
    std::swap(this->lru_, other.lru_);
}
//---------------------------------------------------------------------------
void Value::InitPayload(size_t reserve_size)
{
    switch(type_)
    {
        case STRING:
        {
            switch(encoding_)
            {
                case RAW:
                    val_.string = new String();
                    break;

                case INT:
                    val_.string = 0;
                    break;
            
                default:
                    throw type_error();
            }
            break;
        }

        case BINARY:
        {
            val_.binary = new Binary();
            break;
        }

        case HASH:
        {
            switch(encoding_)
            {
                case UNORDERED_MAP:
                    if(0 == reserve_size)
                        val_.hash = new Hash();
                    else
                        val_.hash = new Hash(reserve_size);
                    break;

                case ZIPLIST:
                    val_.zip_list = new ZipList();
                    break;

                default:
                    throw type_error();
            }
            break;
        }

        case LIST:
        {
            switch(encoding_)
            {
                case LINKED_LIST:
                    if(0 == reserve_size)
                        val_.linked_list = new LinkedList();
                    else
                        val_.linked_list = new LinkedList(reserve_size);
                    break;

                case ZIPLIST:
                    val_.zip_list = new ZipList();
                    break;

                default:
                    throw type_error();
            }
            break;
        }

        case SET:
        {
            switch(encoding_)
            {
                case UNORDERED_SET:
                    if(0 == reserve_size)
                        val_.set = new Set();
                    else
                        val_.set = new Set(reserve_size);
                    break;

                case INT_SET:
                    val_.intset = new IntSet();
                    break;

                default:
                    break;
            }
            break;
        }

        case ZSET:
        {
            val_.sorted_set = new SortedSet();
            break;
        }

        default:
            throw type_error();
    }
    
    return;
}
//---------------------------------------------------------------------------
void Value::DupPayload(const Value& other)
{
    type_ = other.type_;
    encoding_ = other.encoding_;
    lru_ = other.lru_;

    switch(type_)
    {
        case STRING:
        {
            switch(encoding_)
            {
                case RAW:
                    val_.string = new String(*other.val_.string);
                    break;

                case INT:
                    val_.string = other.val_.string;
                    break;
            
                default:
                    throw type_error();
            }
            break;
        }

        case BINARY:
        {
            val_.binary = new Binary(*other.val_.binary);
            break;
        }

        case HASH:
        {
            switch(encoding_)
            {
                case UNORDERED_MAP:
                    val_.hash = new Hash(*other.val_.hash);
                    break;

                case ZIPLIST:
                    val_.zip_list = new ZipList(*other.val_.zip_list);
                    break;

                default:
                    throw type_error();
            }
            break;
        }

        case LIST:
        {
            switch(encoding_)
            {
                case LINKED_LIST:
                    val_.linked_list = new LinkedList(*other.val_.linked_list);
                    break;

                case ZIPLIST:
                    val_.zip_list = new ZipList(*other.val_.zip_list);
                    break;

                default:
                    throw type_error();
            }
            break;
        }

        case SET:
        {
            switch(encoding_)
            {
                case UNORDERED_SET:
                    val_.set = new Set(*other.val_.set);
                    break;

                case INT_SET:
                    val_.intset = new IntSet(*other.val_.intset);
                    break;

                default:
                    break;
            }
            break;
        }

        case ZSET:
        {
            val_.sorted_set = new SortedSet(*other.val_.sorted_set);
            break;
        }

        default:
            throw type_error();
    }
    
    return;
}
//---------------------------------------------------------------------------
void Value::ReleasePayload()
{
    switch(type_)
    {
        case STRING:
        {
            switch(encoding_)
            {
                case RAW:
                    delete val_.string;
                    break;

                case INT:
                    break;
            
                default:
                    throw type_error();
            }
            break;
        }

        case BINARY:
        {
            delete val_.binary;
            break;
        }

        case HASH:
        {
            switch(encoding_)
            {
                case UNORDERED_MAP:
                    delete val_.hash;
                    break;

                case ZIPLIST:
                    delete val_.zip_list;
                    break;

                default:
                    throw type_error();
            }
            break;
        }

        case LIST:
        {
            switch(encoding_)
            {
                case LINKED_LIST:
                    delete val_.linked_list;
                    break;

                case ZIPLIST:
                    delete val_.zip_list;
                    break;

                default:
                    throw type_error();
            }
            break;
        }

        case SET:
        {
            switch(encoding_)
            {
                case UNORDERED_SET:
                    delete val_.set;
                    break;

                case INT_SET:
                    delete val_.intset;
                    break;

                default:
                    break;
            }
            break;
        }

        case ZSET:
        {
            delete val_.sorted_set;
            break;
        }

        default:
            throw type_error();
    }

    return;
}
//---------------------------------------------------------------------------
bool operator==(const ObjectPtr& left, const ObjectPtr& right)
{
    return *left.object() == *right.object();
}
//---------------------------------------------------------------------------
bool operator!=(const ObjectPtr& left, const ObjectPtr& right)
{
    return !(*left.object() == *right.object());
}
//---------------------------------------------------------------------------
}//namespace db
