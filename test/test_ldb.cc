////---------------------------------------------------------------------------
//#include "test_ldb.h"
//#include "../ldb.h"
//#include <string.h>
////---------------------------------------------------------------------------
//namespace db 
//{
//
//namespace test
//{
//
//bool TestLdb::DoTest()
//{
//    if(false == TestUnarySet()) return false;
//    if(false == TestListSet())  return false;
//
//    return true;
//}
////---------------------------------------------------------------------------
//bool TestLdb::TestUnarySet()
//{
//    Ldb ldb(1);
//    std::cout << "no=" << ldb.no() << std::endl;
//    MY_ASSERT(1 == ldb.no());
//
//    //boolean
//    {
//    std::string key_bt = "bt";
//    std::string key_bf = "bf";
//    bool val_bt = true;
//    bool val_bf = false;
//    MY_ASSERT(true == ldb.UnarySetBoolean(key_bt, val_bt));
//    MY_ASSERT(false == ldb.UnarySetBoolean(key_bt, val_bt));
//    MY_ASSERT(true == ldb.UnarySetBoolean(key_bf, val_bf));
//    MY_ASSERT(false == ldb.UnarySetBoolean(key_bf, val_bf));
//    bool rval_bt;
//    bool rval_bf;
//    MY_ASSERT(true == ldb.UnaryGetBoolean(key_bt, &rval_bt));
//    MY_ASSERT(true == ldb.UnaryGetBoolean(key_bf, &rval_bf));
//    MY_ASSERT(true == rval_bt);
//    MY_ASSERT(false == rval_bf);
//    MY_ASSERT(false == ldb.UnaryGetBoolean("invaild", &rval_bt));
//
//    ObjectPtr& oval_bt  = ldb.ObjectGet(key_bt);
//    ObjectPtr& oval_bf  = ldb.ObjectGet(key_bf);
//    const ObjectPtr& coval_bt  = ldb.ObjectGet(key_bt);
//    const ObjectPtr& coval_bf  = ldb.ObjectGet(key_bf);
//    MY_ASSERT(BOOLEAN == oval_bt->type());
//    MY_ASSERT(BOOLEAN == oval_bf->type());
//    MY_ASSERT(BOOLEAN == coval_bt->type());
//    MY_ASSERT(BOOLEAN == coval_bf->type());
//
//    const ObjectPtr& coval_null = ldb.ObjectGet("invalid");
//    ObjectPtr& oval_null = ldb.ObjectGet("invalid");
//    *reinterpret_cast<int*>((oval_null->obj().get())) = 2;
//    MY_ASSERT(coval_null == Ldb::kNullObject);
//    MY_ASSERT(oval_null == Ldb::kNullObject);
//    ObjectPtr null;
//    MY_ASSERT(null != Ldb::kNullObject);
//    MY_ASSERT(null != Ldb::kNullObject);
//    }
//
//    //int
//    {
//    int64_t val_int = 1;
//    std::string key_int = "int";
//    MY_ASSERT(true == ldb.UnarySetInt(key_int, val_int));
//    val_int = 2;
//    MY_ASSERT(false == ldb.UnarySetInt(key_int, val_int));
//    int64_t rval_int;
//    MY_ASSERT(true == ldb.UnaryGetInt(key_int, &rval_int));
//    MY_ASSERT(2 == val_int);
//    MY_ASSERT(false == ldb.UnaryGetInt("invalid", &rval_int));
//
//    //MY_ASSERT(false == ldb.UnaryGetInt("bt", &rval_int)); //assert(false)
//    }
//
//    //uint
//    {
//    uint64_t val_int = -1;
//    std::string key_int = "uint";
//    MY_ASSERT(true == ldb.UnarySetUInt(key_int, val_int));
//    val_int = 2;
//    MY_ASSERT(false == ldb.UnarySetUInt(key_int, val_int));
//    uint64_t rval_int;
//    MY_ASSERT(true == ldb.UnaryGetUInt(key_int, &rval_int));
//    MY_ASSERT(2 == val_int);
//    MY_ASSERT(false == ldb.UnaryGetUInt("invalid", &rval_int));
//    }
//
//    //float
//    {
//    double val_double = -1.0f;
//    std::string key_double = "float";
//    MY_ASSERT(true == ldb.UnarySetFloat(key_double, val_double));
//    MY_ASSERT(false == ldb.UnarySetFloat(key_double, val_double));
//    double rval_double;
//    MY_ASSERT(true == ldb.UnaryGetFloat(key_double, &rval_double));
//    MY_ASSERT(false == ldb.UnaryGetFloat("invalid", &rval_double));
//    }
//
//    //Binary
//    {
//    Binary bin1;
//    Binary bin2;
//    Binary bin3;
//    bin1.resize(10);
//    bin2.resize(10);
//    bin3.resize(10);
//    memset(bin1.data(), 'a', bin1.size());
//    memset(bin2.data(), 'b', bin2.size());
//    memset(bin3.data(), 'b', bin3.size());
//    std::string key_bin1 = "bin1";
//    std::string key_bin2 = "bin2";
//    MY_ASSERT(true == ldb.UnarySetBinary(key_bin1, bin1));
//    MY_ASSERT(true == ldb.UnarySetBinary(key_bin2, std::move(bin2)));
//    MY_ASSERT(false == ldb.UnarySetBinary(key_bin1, bin1));
//    MY_ASSERT(false == ldb.UnarySetBinary(key_bin2, bin3));
//
//    Binary rbin1;
//    Binary rbin2;
//    MY_ASSERT(true== ldb.UnaryGetBinary(key_bin1, &rbin1));
//    MY_ASSERT(true== ldb.UnaryGetBinary(key_bin2, &rbin2));
//    MY_ASSERT(bin1 == rbin1);
//    MY_ASSERT(bin3 == rbin2);
//    MY_ASSERT(false == ldb.UnaryGetBinary("invalid", &rbin1));
//    }
//
//    //String
//    {
//    String str1 = "val_str1";
//    String str2 = "val_str2";
//    String str3 = "val_str2";
//    std::string key1 = "key1";
//    std::string key2 = "key2";
//    MY_ASSERT(true == ldb.UnarySetString(key1, str1));
//    MY_ASSERT(true == ldb.UnarySetString(key2, std::move(str2)));
//    MY_ASSERT(false == ldb.UnarySetString(key1, str1));
//    MY_ASSERT(false == ldb.UnarySetString(key2, str3));
//
//    String rstr1;
//    String rstr2;
//    MY_ASSERT(true== ldb.UnaryGetString(key1, &rstr1));
//    MY_ASSERT(true== ldb.UnaryGetString(key2, &rstr2));
//    MY_ASSERT(str1 == rstr1);
//    MY_ASSERT(str3 == rstr2);
//    MY_ASSERT(false == ldb.UnaryGetString("invalid", &rstr1));
//    }
//
//    return true;
//}
////---------------------------------------------------------------------------
//bool TestLdb::TestListSet()
//{
//    return true;
//}
////---------------------------------------------------------------------------
//}// namespace test
//
//}//namespace db
