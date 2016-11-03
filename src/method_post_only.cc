//---------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <unistd.h>
#include <cstring>
#include "config.h"
#include "method_post_only.h"
#include "request_message.h"
#include "codec.h"
#include "../depend/net/include/tcp_connection.h"
//---------------------------------------------------------------------------
namespace db 
{

using namespace tinyhttp;
//---------------------------------------------------------------------------
__thread char responese_header[1024];
__thread char file_buffer[1024*64];
//---------------------------------------------------------------------------
void MethodPostOnly::GET(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)rcv_time;
    ResponeseForbidden(tcp_conn);
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::POST(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)tcp_conn;
    (void)rcv_time;
    const RequestMessage* req_msg = std::static_pointer_cast<RequestMessage>(tcp_conn->any_).get();
    req_msg->Dump();
    ResponeseHeader(tcp_conn, RequestMessage::kOK, 0);
}
//---------------------------------------------------------------------------
void MethodPostOnly::HEAD(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)tcp_conn;
    (void)rcv_time;
    ResponeseForbidden(tcp_conn);
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::OPTIONS(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)tcp_conn;
    (void)rcv_time;
    ResponeseForbidden(tcp_conn);
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::PUT(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)tcp_conn;
    (void)rcv_time;
    ResponeseForbidden(tcp_conn);
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::TRANCE(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)tcp_conn;
    (void)rcv_time;
    ResponeseForbidden(tcp_conn);
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::DELETE(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)tcp_conn;
    (void)rcv_time;
    ResponeseForbidden(tcp_conn);
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::CONNECT(const net::TCPConnPtr& tcp_conn, uint64_t rcv_time)
{
    (void)tcp_conn;
    (void)rcv_time;
    ResponeseHeader(tcp_conn, tinyhttp::RequestMessage::kForbidden, 0);
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::ResponeseHeader(const net::TCPConnPtr& tcp_conn, const char* status_code, int body_len)
{
    snprintf(responese_header, sizeof(responese_header), 
    "HTTP/1.1 %s\r\n"
    "Content-Type: text/html\r\n"
    "Connection: keep-alive\r\n"
    "Content-Length: %d\r\n\r\n",
    status_code, body_len);

    tcp_conn->Send(responese_header, strlen(responese_header));
    return;
}
//---------------------------------------------------------------------------
void MethodPostOnly::ResponeseForbidden(const net::TCPConnPtr& tcp_conn)
{
    static const char reply[] = "<P>Forbidden</P>";
    ResponeseHeader(tcp_conn, RequestMessage::kForbidden, sizeof(reply));
    tcp_conn->Send(reply, sizeof(reply));

    return;
}
//---------------------------------------------------------------------------

}//namepace db 
