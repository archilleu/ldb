//---------------------------------------------------------------------------
#ifndef DB_MAIN_SERVER_H_
#define DB_MAIN_SERVER_H_
//---------------------------------------------------------------------------
#include "net/callback.h"
#include <memory>
//---------------------------------------------------------------------------
namespace net
{
    class EventLoop;
    class TCPServer;
    class Buffer;
}
//---------------------------------------------------------------------------
namespace db 
{

class MainServer 
{
public:
    MainServer();
    ~MainServer();

    void Start();
    void Stop();

    void set_cfg_path(const std::string& path) { cfg_path_ = path; }

private:
    //event callback
    void OnConnection(const net::TCPConnPtr& conn_ptr);
    void OnDisconnection(const net::TCPConnPtr& conn_ptr);
    void OnRead(const net::TCPConnPtr& conn_ptr, net::Buffer& buffer);

    //signal
    void SignalQuit();

private:
    std::shared_ptr<net::EventLoop> main_loop_;
    std::shared_ptr<net::TCPServer> tcp_server_;
    bool running_;

    std::string cfg_path_;
};

};//namespace db
//---------------------------------------------------------------------------
#endif //DB_MAIN_SERVER_H_
