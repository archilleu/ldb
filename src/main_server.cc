//---------------------------------------------------------------------------
#include "main_server.h"
#include "../depend/net/include/event_loop.h"
#include "../depend/net/include/tcp_server.h"
#include "../depend/net/include/inet_address.h"
#include "../depend/net/include/tcp_connection.h"
#include "config.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
MainServer::MainServer()
:   running_(false)
{
}
//---------------------------------------------------------------------------
MainServer::~MainServer()
{
}
//---------------------------------------------------------------------------
void MainServer::Start()
{
    if(true == running_)
        return;
    running_ = true;

    //config
    MyConfig.set_path(cfg_path_);
    MyConfig.LoadCofig();

    //main loop
    main_loop_ = std::make_shared<net::EventLoop>();
    main_loop_->set_sig_quit_callback(std::bind(&MainServer::SignalQuit, this));

    //tcp server
    std::vector<net::InetAddress> listen_addr;
    const auto& addrs = MyConfig.addrs();
    for(auto v: addrs)
        listen_addr.push_back(net::InetAddress(v.first, v.second));
    tcp_server_ = std::make_shared<net::TCPServer>(main_loop_.get(), listen_addr);

    //tcp server callback
    tcp_server_->set_callback_connection(std::bind(&MainServer::OnConnection, this, std::placeholders::_1));
    tcp_server_->set_callback_disconnection(std::bind(&MainServer::OnDisconnection, this, std::placeholders::_1));
    tcp_server_->set_callback_read(std::bind(&MainServer::OnRead, this, std::placeholders::_1, std::placeholders::_2));

    //work thread numbers
    tcp_server_->set_event_loop_nums(MyConfig.thread_nums());

    //start tcp server
    tcp_server_->Start();
    main_loop_->Loop();

    return;
}
//---------------------------------------------------------------------------
void MainServer::Stop()
{
    main_loop_->Quit();
    tcp_server_->Stop();

    MyConfig.SaveCofig();

    return;
}
//---------------------------------------------------------------------------
void MainServer::OnConnection(const net::TCPConnPtr& conn_ptr)
{
    (void)conn_ptr;
}
//---------------------------------------------------------------------------
void MainServer::OnDisconnection(const net::TCPConnPtr& conn_ptr)
{
    (void)conn_ptr;
}
//---------------------------------------------------------------------------
void MainServer::OnRead(const net::TCPConnPtr& conn_ptr, net::Buffer& buffer)
{
    (void)conn_ptr;
    (void)buffer;
}
//---------------------------------------------------------------------------
void MainServer::SignalQuit()
{
    Stop();
}
//---------------------------------------------------------------------------

}//namespace db
