//---------------------------------------------------------------------------
#ifndef DB_TEST_MAIN_H_
#define DB_TEST_MAIN_H_
//---------------------------------------------------------------------------
#include <unordered_map>
#include <memory>
//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

class TestBase;

class TestMain
{
public:
    TestMain();
    ~TestMain();

    void StartTest();

private:
    typedef std::unordered_map<std::string, std::shared_ptr<TestBase>> TestObj;
    TestObj test_obj_list_;
};

}//namespace test 

}//namespace db 
//---------------------------------------------------------------------------
#endif// DB_TEST_MAIN_H_
