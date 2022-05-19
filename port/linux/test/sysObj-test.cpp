#include "gtest/gtest.h"
#include "test_common.h"
extern "C" {
#include "BaseObj.h"
#include "PikaStdLib_SysObj.h"
#include "TinyObj.h"
#include "pika_config_gtest.h"
}

/* the log_buff of printf */
extern char log_buff[LOG_BUFF_MAX][LOG_SIZE];
TEST(sysObj, print) {
    PikaObj* obj = newRootObj("test", New_PikaStdLib_SysObj);
    VMParameters* globals = obj_runDirect(obj, "print('hello world')");
    // char* sysOut = args_getSysOut(globals->list);
    int errCode = args_getErrorCode(globals->list);
    // printf("sysout = %s\r\n", sysOut);
    EXPECT_STREQ(log_buff[0], "hello world\r\n");
    // ASSERT_STREQ("hello world", sysOut);
    ASSERT_EQ(0, errCode);
    // obj_deinit(globals);
    obj_deinit(obj);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(sysObj, noMethod) {
    PikaObj* obj = newRootObj("test", New_PikaStdLib_SysObj);
    __platform_printf("BEGIN\r\n");
    obj_runDirect(obj, "printttt('hello world')");
    // char* sysOut = args_getSysOut(globals->list);
    // int errCode = args_getErrorCode(globals->list);
    // printf("sysout = %s\r\n", sysOut);
    // ASSERT_EQ(1, strEqu("[error] runner: method no found.", sysOut));
    EXPECT_STREQ(log_buff[4],
                 "NameError: name 'printttt' is not defined\r\n");
    // ASSERT_EQ(2, errCode);
    // obj_deinit(globals);
    obj_deinit(obj);
    EXPECT_EQ(pikaMemNow(), 0);
}
