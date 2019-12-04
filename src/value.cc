//---------------------------------------------------------------------------
#include <cassert>
#include "value.h"
//---------------------------------------------------------------------------
namespace
{


}
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
Value::Value(Type type)
{
    type_ = type;
    val_.string = 0;
    lru_ = base::Timestamp::Now();
}
//---------------------------------------------------------------------------
Value::~Value()
{
    return;
}
//---------------------------------------------------------------------------
/*
void Value::InitPayload(Encoding encoding)
{

        case BINARY:
        {
            val_.binary = new Binary();
            break;
        }

        case HASH:
        {
            val_.hash = new Hash();
            break;
        }

        case LIST:
        {
            switch(encoding)
            {
                case LINKED_LIST:
                    val_.linked_list = new LinkedList();
                    break;

                case ZIPLIST:
                    val_.zip_list = new ZipList();
                    break;

                default:
                    assert(0);
                    break;
            }
            break;
        }

        case SET:
        {
            switch(encoding)
            {
                case UNORDERED_SET:
                    val_.set = new Set();
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
            assert(0);
            break;
    }
    
    return;
}
*/
//---------------------------------------------------------------------------
}//namespace db
