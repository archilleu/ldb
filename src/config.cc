//---------------------------------------------------------------------------
#include "config.h"
#include "../depend/json/include/json_reader.h"
#include "../depend/base/include/function.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
Config MyConfig;
//---------------------------------------------------------------------------
Config::Config()
{
    DefaultConfig();
}
//---------------------------------------------------------------------------
bool Config::LoadCofig()
{
    //load config file
    config_ = json::Value(json::Value::TYPE::OBJECT);
    json::JsonReader reader;
    reader.ParseFile(path_, &config_);

    //load addrs
    LoadAddrs();

    //load save conditons
    LoadSaveCondition();

    return true;
}
//---------------------------------------------------------------------------
bool Config::SaveCofig()
{
    std::string cfg = config_.ToString(true);
    std::string temp_name = path_ + "-temp";

    if(false == base::SaveFile(temp_name, cfg.data(), cfg.length()))
        return false;

    //rename
    if(-1 == rename(temp_name.c_str(), path_.c_str()))
        return false;

    return true;
}
//---------------------------------------------------------------------------
void Config::DefaultConfig()
{
    //addrs
    addrs_["127.0.0.1"] = 9981;

    //save conditions
    save_conds_[base::CombineString("%d", kMinute*1)]  = 1000; //1 min 1000 modify,save
    save_conds_[base::CombineString("%d", kMinute*5)]  = 10; //5 min 10 modify,save
    save_conds_[base::CombineString("%d", kMinute*15)] = 1; //15 min 1 modify,save

    //thread numbers
    thread_nums_ = 0;

    return;
}
//---------------------------------------------------------------------------
void Config::LoadAddrs()
{
    static const char* key = "server addrs";

    json::Value jaddrs;
    if(false == config_.PairGet(key, &jaddrs))
    {
        jaddrs = json::Value(json::Value::TYPE::OBJECT);
        for(auto iter : addrs_)
            jaddrs[iter.first] = iter.second;

        config_.PairAdd(key, std::move(jaddrs));
    }
    else
    {
        addrs_.clear();
        for(auto iter=jaddrs.PairIterBegin(); jaddrs.PairIterEnd()!=iter; ++iter)
            addrs_[iter->first] = static_cast<short>(iter->second.get_int());
    }

    return;
}
//---------------------------------------------------------------------------
void Config::LoadSaveCondition()
{
    static const char* key = "save condition";

    json::Value jsave_conds;
    if(false == config_.PairGet(key, &jsave_conds))
    {
        int index = 0;
        jsave_conds = json::Value(json::Value::TYPE::OBJECT);
        for(auto iter : save_conds_)
        {
            json::Value arr(json::Value::TYPE::ARRAY);
            arr.ArrayResize(2);
            arr[0] = iter.first;
            arr[1] = iter.first;

            jsave_conds.PairAdd(base::CombineString("%d", index++), std::move(arr));
        }

        config_.PairAdd(key, std::move(jsave_conds));
    }
    else
    {
        save_conds_.clear();
        for(auto iter=jsave_conds.PairIterBegin(); jsave_conds.PairIterEnd()!=iter; ++iter)
            save_conds_[iter->first] = iter->second.get_uint();
    }

    return;
}
//---------------------------------------------------------------------------
void Config::LoadThreadNums()
{
    static const char* key = "thread numbers";

    json::Value tnum;
    if(false == config_.PairGet(key, &tnum))
        config_.PairAdd(key, thread_nums_);
    else
        thread_nums_ = static_cast<int>(tnum.get_int());

    return;
}
//---------------------------------------------------------------------------

}//namespace db
