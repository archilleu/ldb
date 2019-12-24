//---------------------------------------------------------------------------
#include <climits>
#include "test_inc.h"
#include "../src/string_value.h"
//---------------------------------------------------------------------------
using namespace db;
using namespace db::test;
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    //默认构造
    {
    StringValue str;
    TEST_ASSERT(str.type() == Value::STRING);
    TEST_ASSERT(str.encoding() == Value::INT);
    TEST_ASSERT(0 == strcmp(str.val(), "0"));
    TEST_ASSERT(str.AsInt() == 0);
    TEST_ASSERT(str.AsDouble() == 0);
    }

    //const char* 构造
    {
    const char* s = "const char* 构造";
    StringValue str(s);
    TEST_ASSERT(str.type() == Value::STRING);
    TEST_ASSERT(str.encoding() == Value::RAW);
    TEST_ASSERT(str.val() == std::string(s));
    TEST_ASSERT(str.AsInt() == 0);
    TEST_ASSERT(str.AsDouble() == 0);
    }

    //const char*, len 构造
    {
    const char* s = "const char, len* 构造";
    StringValue str(s, strlen(s));
    TEST_ASSERT(str.type() == Value::STRING);
    TEST_ASSERT(str.encoding() == Value::RAW);
    TEST_ASSERT(str.val() == std::string(s));
    TEST_ASSERT(str.AsInt() == 0);
    TEST_ASSERT(str.AsDouble() == 0);
    }

    //const string& 构造
    {
    const std::string s = "const string& 构造";
    StringValue str(s);
    TEST_ASSERT(str.type() == Value::STRING);
    TEST_ASSERT(str.encoding() == Value::RAW);
    TEST_ASSERT(str.val() == s);
    TEST_ASSERT(str.AsInt() == 0);
    TEST_ASSERT(str.AsDouble() == 0);
    }

    //long long 构造
    {
    int64_t l1 = LLONG_MIN;
    int64_t l2 = LLONG_MAX;
    StringValue sl1(l1);
    StringValue sl2(l2);

    TEST_ASSERT(sl1.type() == Value::STRING);
    TEST_ASSERT(sl1.encoding() == Value::INT);
    TEST_ASSERT(sl1.val() == std::to_string(l1));
    TEST_ASSERT(sl1.AsInt() == l1);
    TEST_ASSERT(sl1.AsDouble() == static_cast<double>(l1));

    TEST_ASSERT(sl2.type() == Value::STRING);
    TEST_ASSERT(sl2.encoding() == Value::INT);
    TEST_ASSERT(sl2.val() == std::to_string(l2));
    TEST_ASSERT(sl2.AsInt() == l2);
    TEST_ASSERT(sl2.AsDouble() == static_cast<double>(l2));

    std::cout << "int min:" << sl1.AsInt() << std::endl;
    std::cout << "int max:" << sl2.AsInt() << std::endl;
    }

    //double构造
    {
    double d = 1.0000000000000000001;
    StringValue val(d);

    TEST_ASSERT(val.type() == Value::STRING);
    TEST_ASSERT(val.encoding() == Value::RAW);
    TEST_ASSERT(val.val() == std::to_string(d));
    TEST_ASSERT(val.AsInt() == static_cast<int64_t>(d));
    TEST_ASSERT(val.AsDouble() == d);
    }

    //拷贝构造
    {
    const std::string s = "const StringValue& 构造";
    StringValue val(s);
    StringValue copy(val);
    StringValue copy1 = copy;

    TEST_ASSERT(copy.type() == val.type());
    TEST_ASSERT(copy.encoding() == val.encoding());
    TEST_ASSERT(0 == std::strcmp(copy.val(), val.val()));
    TEST_ASSERT(copy.AsInt() == val.AsInt());
    TEST_ASSERT(copy.AsDouble() == val.AsDouble());
    TEST_ASSERT(copy1.type() == val.type());
    TEST_ASSERT(copy1.encoding() == val.encoding());
    TEST_ASSERT(std::string(copy1.val()) == val.val());
    TEST_ASSERT(copy1.AsInt() == val.AsInt());
    TEST_ASSERT(copy1.AsDouble() == val.AsDouble());
    }

    //移动构造
    {
    const std::string s = "const StringValue& 构造";
    StringValue val(s);
    StringValue copy(std::move(val));
    StringValue copy1 = std::move(copy);

    TEST_ASSERT(val.type() == Value::STRING);
    TEST_ASSERT(val.encoding() == Value::INT);
    TEST_ASSERT(val.AsInt() == 0);
    TEST_ASSERT(val.lru() == base::Timestamp::Invalid());
    TEST_ASSERT(val.AsDouble() == static_cast<double>(0));

    TEST_ASSERT(copy1.type() == Value::STRING);
    TEST_ASSERT(copy1.encoding() == Value::RAW);
    TEST_ASSERT(copy1.val() == s);
    TEST_ASSERT(copy1.AsInt() == 0);
    TEST_ASSERT(copy1.AsDouble() == 0);
    }

    //赋值
    {
    const std::string s1 = "const StringValue& 构造1";
    const std::string s2 = "const StringValue& 构造2";
    StringValue val(s1);
    StringValue copy(s2);
    copy = val;

    TEST_ASSERT(copy.type() == Value::STRING);
    TEST_ASSERT(copy.encoding() == Value::RAW);
    TEST_ASSERT(copy.val() == s1);
    TEST_ASSERT(copy.AsInt() == 0);
    TEST_ASSERT(copy.AsDouble() == 0);

    StringValue v1;
    StringValue v2;
    StringValue v3;
    StringValue v4;
    StringValue v5;

    v1 = s1;
    v2 = "char*";
    v3 = INT_MAX;
    v4 = LONG_MAX;
    v5 = 1.0;
    
    v1 = 1;
    v2 = 2;
    v3 = "3";
    v4 = "4";
    v5 = 5;

    TEST_ASSERT(v1.AsInt() == 1);
    TEST_ASSERT(v2.AsInt() == 2);
    TEST_ASSERT(0 == strcmp(v3.val(),"3"));
    TEST_ASSERT(0 == strcmp(v4.val(), "4"));
    TEST_ASSERT(v5.AsInt() == 5);
    }
    //赋值
    {
    int i1 = 10;
    int i2 = 20;
    StringValue val1(i1);
    StringValue val2(i2);
    val2 = val1;

    TEST_ASSERT(val2.type() == Value::STRING);
    TEST_ASSERT(val2.encoding() == Value::INT);
    TEST_ASSERT(val2.val() == std::to_string(i1));
    TEST_ASSERT(val2.AsInt() == i1);
    TEST_ASSERT(val2.AsDouble() == static_cast<double>(i1));
    }
    //赋值
    {
    const char* i1 = "10";
    int i2 = 20;
    StringValue val1(i1);
    StringValue val2(i2);
    val2 = val1;

    TEST_ASSERT(val2.type() == Value::STRING);
    TEST_ASSERT(val2.encoding() == Value::INT);
    TEST_ASSERT(0==std::strcmp(val2.val(), i1));
    TEST_ASSERT(val2.AsInt() == std::atoi(i1));
    TEST_ASSERT(val2.AsDouble() == std::atof(i1));
    }
    //移动赋值
    {
    const char* i1 = "10";
    int i2 = 20;
    StringValue val1(i1);
    StringValue val2(i2);
    val2 = std::move(val1);

    TEST_ASSERT(val2.type() == Value::STRING);
    TEST_ASSERT(val2.encoding() == Value::INT);
    TEST_ASSERT(0==std::strcmp(val2.val(), i1));
    TEST_ASSERT(val2.AsInt() == std::atoi(i1));
    TEST_ASSERT(val2.AsDouble() == std::atof(i1));

    TEST_ASSERT(val1.type() == Value::STRING);
    TEST_ASSERT(val1.encoding() == Value::INT);
    TEST_ASSERT(val1.AsInt() == 0);
    TEST_ASSERT(val1.lru() == base::Timestamp::Invalid());
    TEST_ASSERT(val1.AsDouble() == static_cast<double>(0));
    }

    //直接赋值
    {
    const char* s1 = "我是好人";
    const std::string s2 = s1;
    int32_t i1 = INT_MAX;
    int64_t i2 = LLONG_MAX;
    double d = 10.0;

    StringValue v1 = s1;
    StringValue v2 = s2;
    StringValue v3 = i1;
    StringValue v4 = i2;
    StringValue vd = d;

    TEST_ASSERT(v1.type() == Value::STRING);
    TEST_ASSERT(v1.encoding() == Value::RAW);
    TEST_ASSERT(0==std::strcmp(v1.val(), s1));
    TEST_ASSERT(v1.AsInt() == 0);
    TEST_ASSERT(v1.AsDouble() == 0);

    TEST_ASSERT(v2.type() == Value::STRING);
    TEST_ASSERT(v2.encoding() == Value::RAW);
    TEST_ASSERT(v2.val() == s2);
    TEST_ASSERT(v2.AsInt() == 0);
    TEST_ASSERT(v2.AsDouble() == 0);

    TEST_ASSERT(v3.type() == Value::STRING);
    TEST_ASSERT(v3.encoding() == Value::INT);
    TEST_ASSERT(v3.val() == std::to_string(i1));
    TEST_ASSERT(v3.AsInt() == i1);
    TEST_ASSERT(v3.AsDouble() == static_cast<double>(i1));

    TEST_ASSERT(v4.type() == Value::STRING);
    TEST_ASSERT(v4.encoding() == Value::INT);
    TEST_ASSERT(v4.val() == std::to_string(i2));
    TEST_ASSERT(v4.AsInt() == i2);
    TEST_ASSERT(v4.AsDouble() == static_cast<double>(i2));

    TEST_ASSERT(vd.type() == Value::STRING);
    TEST_ASSERT(vd.encoding() == Value::RAW);
    TEST_ASSERT(vd.val() == std::to_string(d));
    TEST_ASSERT(vd.AsInt() == static_cast<int64_t>(d));
    TEST_ASSERT(vd.AsDouble() == d);
    }

    //交换
    {
    const char* s1 = "const char1";
    const char* s2 = "const char2";
    StringValue str1 = s1;
    StringValue str2 = s2;
    str1.Swap(str2);

    TEST_ASSERT(str1.type() == Value::STRING);
    TEST_ASSERT(str1.encoding() == Value::RAW);
    TEST_ASSERT(0==std::strcmp(str1.val(), s2));
    TEST_ASSERT(str2.type() == Value::STRING);
    TEST_ASSERT(str2.encoding() == Value::RAW);
    TEST_ASSERT(0==std::strcmp(str2.val(), s1));
    }

    return 0;
}
//---------------------------------------------------------------------------
