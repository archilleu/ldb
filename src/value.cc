//---------------------------------------------------------------------------
#include <cstring>
#include <sstream>
#include "value.h"
//---------------------------------------------------------------------------
namespace
{


}
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
Value::Value(Type type, const ValuePtr& obj)
{
    type_ = type;
    encoding_ = Encoding::RAW;
    lru_ = base::Timestamp::Now();
    obj_ = obj;
}
//---------------------------------------------------------------------------
}//namespace db