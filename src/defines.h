//---------------------------------------------------------------------------
#ifndef DB_DEFINES_H_
#define DB_DEFINES_H_
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
/**
 * dump & undump
 */
//数据库名字
const static char kLDB_NAME[3] = {'L','D','B'};
//数据库文件版本
const static char kLDB_VERSION[4] = {'0','0','0','1'};
//ldb文件结束
const static uint8_t kLDB_EOF = 0xFF;

//对象类型再ldb文件中的类型
const static uint8_t kLDB_TYPE_STRING = 0;
const static uint8_t kLDB_TYPE_LIST = 1;
const static uint8_t kLDB_TYPE_SET = 2;
const static uint8_t kLDB_TYPE_ZSET = 3;
const static uint8_t kLDB_TYPE_HASH = 4;

const static uint8_t kLDB_TYPE_LIST_ZIPLIST = 10;
const static uint8_t kLDB_TYPE_SET_INTSET = 11;
const static uint8_t kLDB_TYPE_SET_ZIPLIST = 12;
const static uint8_t kLDB_TYPE_HASH_ZIPLIST = 13;

/**
 * 数据库特殊操作标识符
 */
//MS过期时间
const static uint8_t kLDB_OPCODE_EXPIRETIME_MS = 252;
//过期时间
const static uint8_t kLDB_OPCODE_EXPIRETIME = 253;
//数据库编号
const static uint8_t kLDB_OPCODE_SELECTDB = 254;
//数据库结尾
const static uint8_t kLDB_OPCODE_EOF = 255;

//---------------------------------------------------------------------------
#endif //DB_DEFINES_H_
