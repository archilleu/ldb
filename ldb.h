//---------------------------------------------------------------------------
#ifndef DB_LDB_H_
#define DB_LDB_H_
//---------------------------------------------------------------------------
#include "type.h"
//---------------------------------------------------------------------------
namespace db 
{

class Ldb 
{
public:
    Ldb(int n)
    :   no_(n)
    {}

    //unary set method, not exist return true, otherwish return false 
    bool UnarySetBoolean(const String& key, bool val);
    bool UnarySetInt    (const String& key, int64_t val);
    bool UnarySetUInt   (const String& key, uint64_t val);
    bool UnarySetFloat  (const String& key, double val);
    bool UnarySetBinary (const String& key, const Binary& val);
    bool UnarySetBinary (const String& key, Binary&& val);
    bool UnarySetString (const String& key, const String& val);
    bool UnarySetString (const String& key, String&& val);

    //unary get method
    bool UnaryGetBoolean(const String& key, bool* val);
    bool UnaryGetInt    (const String& key, int64_t* val);
    bool UnaryGetUInt   (const String& key, uint64_t* val);
    bool UnaryGetFloat  (const String& key, double* val);
    bool UnaryGetBinary (const String& key, Binary* val);
    bool UnaryGetString (const String& key, String* val);

    //list method
    const List<Object>& ListGet(const String& key) const;
    List<Object>& ListGet(const String& key);

    //void ListPush(const List<Object>& list, 

    ///normal method
    //get
    const ObjectPtr& ObjectGet(const String& key) const
    {
        const auto iter = dict_.find(key);
        if(dict_.end() == iter)
            return kNullObject;

        return iter->second;
    }

    ObjectPtr& ObjectGet(const String& key)
    {
        auto iter = dict_.find(key);
        if(dict_.end() == iter)
            return kNullObject;

        return iter->second;
    }

    //exist
    bool KeyExist(const String& key)
    {
        return dict_.end() != dict_.find(key);
    }

    //data db number
    int no() { return no_; }

private:
    inline bool UnarySet(const String& key, const ObjectPtr& obj_val);

private:
    Hash<String, ObjectPtr> dict_;
    int no_;

public:
    static ObjectPtr kNullObject;
};

}// namespace db
//---------------------------------------------------------------------------
#endif //DB_LDB_H_
