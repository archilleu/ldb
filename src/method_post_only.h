//---------------------------------------------------------------------------
#ifndef DB_METHOD_POST_ONLY_H_
#define DB_METHOD_POST_ONLY_H_
//---------------------------------------------------------------------------
#include "method.h"
//---------------------------------------------------------------------------
namespace db 
{

class MethodPostOnly: public tinyhttp::Method
{
public:
    virtual void GET        (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);
    virtual void POST       (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);
    virtual void HEAD       (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);
    virtual void OPTIONS    (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);
    virtual void PUT        (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);
    virtual void TRANCE     (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);
    virtual void DELETE     (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);
    virtual void CONNECT    (const net::TCPConnPtr& tcp_conn, uint64_t rcv_time);

private:
    void ResponeseHeader(const net::TCPConnPtr& tcp_conn, const char* status_code, int body_len);
    void ResponeseForbidden(const net::TCPConnPtr& tcp_conn);
};

}//namespace db 
//---------------------------------------------------------------------------
#endif //DB_METHOD_POST_ONLY_H_
