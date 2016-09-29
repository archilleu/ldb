//---------------------------------------------------------------------------
#include "test_ldb.h"
#include "../ldb.h"
//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

bool TestLdb::DoTest()
{
    if(false == TestNormal())   return false;

    return true;
}
//---------------------------------------------------------------------------
bool TestLdb::TestNormal()
{
    Ldb ldb(1);
    std::cout << "no=" << ldb.no() << std::endl;
    MY_ASSERT(1 == ldb.no());

    //boolean
    {
    std::string key_bt = "bt";
    std::string key_bf = "bf";
    bool val_bt = true;
    bool val_bf = false;
    MY_ASSERT(true == ldb.UnarySetBoolean(key_bt, val_bt));
    MY_ASSERT(false == ldb.UnarySetBoolean(key_bt, val_bt));
    MY_ASSERT(true == ldb.UnarySetBoolean(key_bf, val_bf));
    MY_ASSERT(false == ldb.UnarySetBoolean(key_bf, val_bf));
    bool rval_bt;
    bool rval_bf;
    MY_ASSERT(true == ldb.UnaryGetBoolean(key_bt, &rval_bt));
    MY_ASSERT(true == ldb.UnaryGetBoolean(key_bf, &rval_bf));
    MY_ASSERT(true == rval_bt);
    MY_ASSERT(false == rval_bf);
    MY_ASSERT(false == ldb.UnaryGetBoolean("invaild", &rval_bt));

    ObjectPtr& oval_bt  = ldb.ObjectGet(key_bt);
    ObjectPtr& oval_bf  = ldb.ObjectGet(key_bf);
    const ObjectPtr& coval_bt  = ldb.ObjectGet(key_bt);
    const ObjectPtr& coval_bf  = ldb.ObjectGet(key_bf);
    MY_ASSERT(TYPE_BOOLEAN == oval_bt->type());
    MY_ASSERT(TYPE_BOOLEAN == oval_bf->type());
    MY_ASSERT(TYPE_BOOLEAN == coval_bt->type());
    MY_ASSERT(TYPE_BOOLEAN == coval_bf->type());

    const ObjectPtr& coval_null = ldb.ObjectGet("invalid");
    ObjectPtr& oval_null = ldb.ObjectGet("invalid");
    MY_ASSERT(coval_null == Ldb::kNullObject);
    MY_ASSERT(oval_null == Ldb::kNullObject);
    ObjectPtr null;
    MY_ASSERT(null != Ldb::kNullObject);
    MY_ASSERT(null != Ldb::kNullObject);
    }

    return true;
}

}// namespace test

}//namespace db
