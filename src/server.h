//---------------------------------------------------------------------------
#ifndef DB_SERVER_H_
#define DB_SERVER_H_
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
namespace db
{

class HashValue;

class Server
{
public:
    Server(size_t db_nums);
    Server(const Server&) =delete;
    Server& operator=(const Server&) =delete;

public:
    std::vector<HashValue>& dbs() { return dbs_; };

    void set_cur_db_idx(size_t idx) { cur_db_idx_ = idx; };
    size_t cru_db_idx() const { return cur_db_idx_; };

    HashValue& cur_db() { return dbs_[cur_db_idx_]; }

private:
    std::vector<HashValue> dbs_;
    size_t cur_db_idx_;
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_SERVER_H_
