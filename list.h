//---------------------------------------------------------------------------
#ifndef DB_LIST_H_
#define DB_LIST_H_
//---------------------------------------------------------------------------
#include <list>

#include "type.h"
#include "set.h"
#include "zset.h"
#include "hash.h"
//---------------------------------------------------------------------------
namespace db 
{

class List 
{
public:
    void PushBoolean(bool val, bool head);
    void PushInt(int64_t val, bool head);
    void PushUInt(uint64_t val, bool head);
    void PushFloat(float val, bool head);

    void PushBinary(const Binary& val, bool head);
    void PushBinary(Binary&& val, bool head);

    void PushString(const String& val, bool head);
    void PushString(String&& val, bool head);

    void PushList(const List& val, bool head);
    void PushList(List&& val, bool head);

    void PushSet(const Set& val, bool head);
    void PushSet(Set&& val, bool head);

    void PushZSet(const ZSet& val, bool head);
    void PushZSet(ZSet&& val, bool head);

    void PushHash(const Hash& val, bool head);
    void PushHash(Hash&& val, bool head);

private:
    std::list<Object> list_;
};

}// namespace db
//---------------------------------------------------------------------------
#endif //DB_LIST_H_
