//---------------------------------------------------------------------------
#ifndef DB_LDB_H_
#define DB_LDB_H_
//---------------------------------------------------------------------------
#include "value.h"
#include <memory>
//---------------------------------------------------------------------------
namespace db 
{

class Ldb 
{
public:
    Ldb(int n)
    :   no_(n),
        dict_(std::make_shared<Value>(Value::TYPE::HASH))
    {
        return;
    }
    ~Ldb()
    {
        return;
    }


    Value& dict() { return *dict_; }
    int no() { return no_; }

    size_t Size();
    void Clear();

public:
    //operator overload
    Value& operator[](const char* key)          { return dict()[key]; }
    Value& operator[](const std::string& key)   { return dict()[key]; }

private:
    int no_;
    std::shared_ptr<Value> dict_;
};

}// namespace db
//---------------------------------------------------------------------------
#endif //DB_LDB_H_
