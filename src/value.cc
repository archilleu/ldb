//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
const ValuePtr Value::NullPtr;
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
}//namespace db
