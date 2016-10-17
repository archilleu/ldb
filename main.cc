//---------------------------------------------------------------------------
#include <iostream>
#include "main_server.h"
//---------------------------------------------------------------------------
int main(int , char** )
{
    db::MainServer main_server;
    main_server.set_cfg_path("~/workspace/ldb/ldb.cfg");
    main_server.Start();

    return 0;
}
//---------------------------------------------------------------------------
