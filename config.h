//---------------------------------------------------------------------------
#ifndef DB_CONFIG_H_
#define DB_CONFIG_H_
//---------------------------------------------------------------------------
#include <string>
#include <map>
#include "json/value.h"
//---------------------------------------------------------------------------
namespace db 
{

class Config 
{
public:
    Config();

    bool LoadCofig();
    bool SaveCofig();

    const std::map<std::string, short>& addrs() const { return addrs_; }
    const std::map<std::string, uint64_t>& save_conds() const { return save_conds_; }
    int thread_nums() const { return thread_nums_; }

    void set_path(const std::string& p) { path_ = p; }
    const std::string& path() const { return path_; }

private:
    void DefaultConfig();

    void LoadAddrs();
    void LoadSaveCondition();
    void LoadThreadNums();

private:
    std::map<std::string, short> addrs_;
    std::map<std::string, uint64_t> save_conds_;
    int thread_nums_; 

    std::string path_;
    json::Value config_;

private:
    const static int kSecond = 1;
    const static int kMinute = kSecond * 60;
    const static int kHour = kMinute * 60;
};
//---------------------------------------------------------------------------
extern Config MyConfig;
//---------------------------------------------------------------------------
}//namespace db
//---------------------------------------------------------------------------
#endif //DB_CONFIG_H_

