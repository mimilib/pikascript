#include "gtest/gtest.h"
#include "test_common.h"
extern "C" {
#include "PikaMain.h"
#include "PikaParser.h"
#include "PikaStdLib_MemChecker.h"
#include "PikaVM.h"
#include "dataArgs.h"
#include "dataMemory.h"
#include "dataStrs.h"
#include "pikaScript.h"
#include "pika_config_gtest.h"
}

extern PikaMemInfo pikaMemInfo;
TEST(pikaMain, init) {
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = pikaScriptInit();
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, new_mem) {
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    VMParameters* globals = obj_runDirect(pikaMain,
                                          "mem = PikaStdLib.MemChecker()\n"
                                          "mem.max()\n");
    PikaObj* mem = (PikaObj*)args_getPtr(globals->list, "mem");
    PikaObj* memClassPtr = (PikaObj*)obj_getPtr(mem, "_clsptr");
    EXPECT_EQ((void*)memClassPtr, (void*)New_PikaStdLib_MemChecker);
    obj_deinit(pikaMain);
    // obj_deinit(globals);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, list_new) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    VMParameters* globals = obj_runDirect(pikaMain,
                                          "list = PikaStdData.List()\n"
                                          "list.append(7)\n"
                                          "list.append('eee')\n"
                                          "len = list.len()\n"
                                          "a1 = list.get(0)\n"
                                          "a2 = list.get(1)\n");
    /* collect */
    int len = obj_getInt(globals, "len");
    int a1 = obj_getInt(globals, "a1");
    char* a2 = obj_getStr(globals, "a2");

    /* assert */
    EXPECT_EQ(len, 2);
    EXPECT_EQ(a1, 7);
    EXPECT_STREQ(a2, "eee");

    /* deinit */
    // obj_deinit(globals);
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, int_float_convert) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    VMParameters* globals = obj_runDirect(pikaMain,
                                          "a = 1\n"
                                          "a_f = float(a)\n"
                                          "b = 1.3\n"
                                          "b_i = int(b)\n");
    /* collect */
    int a = obj_getInt(globals, "a");
    float a_f = obj_getFloat(globals, "a_f");
    float b = obj_getFloat(globals, "b");
    int b_i = obj_getInt(globals, "b_i");

    /* assert */
    EXPECT_EQ(a, 1);
    EXPECT_FLOAT_EQ(a_f, 1);
    EXPECT_FLOAT_EQ(b, 1.3);
    EXPECT_FLOAT_EQ(b_i, 1);

    /* deinit */
    // obj_deinit(globals);
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, type_) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "type(1)\n"
                  "b = 1.4\n"
                  "type(b)\n");
    /* collect */

    /* assert */

    /* deinit */
    // obj_deinit(globals);
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, a_signed) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain, "a = -1\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");

    /* assert */
    EXPECT_EQ(-1, a);

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, a_mm) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain, "a = -1.1 ** 3\n");
    /* collect */
    float a = obj_getFloat(pikaMain, "a");

    /* assert */
    EXPECT_FLOAT_EQ(-1.331, a);

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, a_n1) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain, "a = -2\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");

    /* assert */
    EXPECT_EQ(-2, a);

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, a_l4) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain, "a = 1<<4\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");

    /* assert */
    EXPECT_EQ(16, a);

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, less_equ) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "a = 0\n"
                  "while a <= 10:\n"
                  "    a += 1\n"
                  "\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");

    /* assert */
    EXPECT_EQ(11, a);

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, and_or_not) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "a = 0\n"
                  "b = 0\n"
                  "c = 0\n"
                  "d = 0\n"
                  "if (1>2) or (2>1):\n"
                  "    a = 1\n"
                  "\n"
                  "if (1>2) and (2>1):\n"
                  "    b = 1\n"
                  "\n"
                  "if not (1>2):\n"
                  "    c = 1\n"
                  "\n"
                  "if not (2>1):\n"
                  "    d = 1\n"
                  "\n"
                  "e = ~1\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    int b = obj_getInt(pikaMain, "b");
    int c = obj_getInt(pikaMain, "c");
    int d = obj_getInt(pikaMain, "d");
    int e = obj_getInt(pikaMain, "e");

    /* assert */
    EXPECT_EQ(1, a);
    EXPECT_EQ(0, b);
    EXPECT_EQ(1, c);
    EXPECT_EQ(0, d);
    EXPECT_EQ(e, -2);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, err_scop) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain, "print('test'");
    /* collect */

    /* assert */

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, PikaStdData) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "dict = PikaStdData.Dict()\n"
            "dict.set('a', 1)\n"
            "dict.set('b', 2)\n"
            "dict.remove('b')\n"
            "a = dict.get('a')\n"
            "b = dict.get('b')\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    int b = obj_getInt(pikaMain, "b");
    /* assert */
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, -999999999);

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, list_method) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "list = PikaStdData.List()\n"
                  "list.append(7)\n"
                  "list.append('eee')\n"
                  "len = list.len()\n"
                  "a1 = list.get(0)\n"
                  "a2 = list.get(1)\n"
                  "\n");
    /* collect */
    /* assert */
    /* deinit */
    // obj_deinit(globals);
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, list_iter) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "list = PikaStdData.List()\n"
                  "res = iter(list)\n"
                  "\n");
    /* collect */
    PikaObj* res = (PikaObj*)obj_getPtr(pikaMain, "res");
    PikaObj* list = (PikaObj*)obj_getPtr(pikaMain, "list");
    int ref_cnt = obj_refcntNow(list);
    EXPECT_EQ(ref_cnt, 2);
    /* assert */
    EXPECT_EQ(res, list);
    /* deinit */
    // obj_deinit(globals);
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, list_for_loop) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "list = PikaStdData.List()\n"
                  "list.append(7)\n"
                  "list.append('eee')\n"
                  "len = list.len()\n"
                  "for item in list:\n"
                  "    print(item)\n"
                  "    a = item\n"
                  "\n");
    /* collect */
    char* a = obj_getStr(pikaMain, "a");
    /* assert */
    EXPECT_STREQ(a, "eee");
    /* deinit */
    // obj_deinit(globals);
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, range) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "r = range(10, 0)\n"
                  "r\n"
                  "\n");
    /* collect */
    /* assert */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, for_in_range) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "a = 0\n"
                  "for i in range(0, 10):\n"
                  "    print(i)\n"
                  "    a = a + i\n"
                  "\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    /* assert */
    EXPECT_EQ(a, 45);
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, for_for_in_range) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "a = 0\n"
                  "for i in range(0, 10):\n"
                  "    for k in range(0, 3):\n"
                  "        print(k)\n"
                  "        a = a + k\n"
                  "\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    /* assert */
    EXPECT_EQ(a, 30);
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, for_if_break) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_runDirect(pikaMain,
                  "a = 0\n"
                  "for i in range(0, 10):\n"
                  "    if i == 5:\n"
                  "        break\n"
                  "    a = a + i\n"
                  "\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    /* assert */
    EXPECT_EQ(a, 10);
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, for_if_continue) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "a = 0\n"
            "for i in range(0, 10):\n"
            "    if i == 5:\n"
            "        continue\n"
            "    a = a + i\n"
            "\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    /* assert */
    EXPECT_EQ(a, 40);
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

/* the log_buff of printf */
extern char log_buff[LOG_BUFF_MAX][LOG_SIZE];
TEST(pikaMain, print_in_def) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    /* the test is used to fix too many print in def */
    /* clear the log_buff */
    memset(log_buff, 0, LOG_BUFF_MAX * LOG_SIZE);
    obj_runDirect(pikaMain,
                  "def test_print():\n"
                  "    print('test')\n"
                  "test_print()\n");
    /* collect */
    /* assert */
    /* should only print once, so the second log (log_buff[1]) shuold be '\0' */
    EXPECT_STREQ(log_buff[0], "test\r\n");
    EXPECT_STREQ(log_buff[1], "");
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, prime_100) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "num = 0\n"
            "i = 2\n"
            "for i in range(2 , 100):\n"
            "    j=2\n"
            "    is_prime = 1\n"
            "    for j in range(2 , i):\n"
            "        if i%j==0 :\n"
            "            is_prime = 0\n"
            "            break\n"
            "    if is_prime:\n"
            "        num = num + i\n"
            "\n");
    /* collect */
    int num = obj_getInt(pikaMain, "num");
    /* assert */
    EXPECT_EQ(num, 1060);
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

/* the log_buff of printf */
extern char log_buff[LOG_BUFF_MAX][LOG_SIZE];
TEST(pikaMain, for_in_dict) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "print('__start__')\n"
            "dict = PikaStdData.Dict()\n"
            "dict.set('a', 1)\n"
            "dict.set('b', 2)\n"
            "dict.remove('b')\n"
            "for item in dict:\n"
            "    print(item)\n"
            "\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "1\r\n");
    EXPECT_STREQ(log_buff[1], "__start__\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, str_add) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "a = 'a'\n"
            "b = 'b'\n"
            "c = a + b\n"
            "d = 1\n"
            "e = 1.2\n"
            "g = c + str(d)\n"
            "h = c + str(d) + str(e)\n"
            "\n");
    /* collect */
    char* c = obj_getStr(pikaMain, "c");
    char* g = obj_getStr(pikaMain, "g");
    char* h = obj_getStr(pikaMain, "h");
    /* assert */
    EXPECT_STREQ(c, "ab");
    EXPECT_STREQ(g, "ab1");
    EXPECT_STREQ(h, "ab11.200000");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, str_add_print) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "print('test: ' + str(2233))\n"
            "\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "test: 2233\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, int_float_to_str) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "a = str(1)\n"
            "b = str(1.2)\n"
            "\n");
    /* collect */
    char* a = obj_getStr(pikaMain, "a");
    char* b = obj_getStr(pikaMain, "b");
    /* assert */
    EXPECT_STREQ(a, "1");
    EXPECT_STREQ(b, "1.200000");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, str_eq) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
            "a = '1ee'\n"
            "b = '1ee'\n"
            "c = '1e'\n"
            "if a==b:\n"
            "    res1 = 1\n"
            "else:\n"
            "    res1 = 0\n"
            "if a==c:\n"
            "    res2 = 1\n"
            "else:\n"
            "    res2 = 0\n"
            "\n");
    /* collect */
    int res1 = obj_getInt(pikaMain, "res1");
    int res2 = obj_getInt(pikaMain, "res2");
    /* assert */
    EXPECT_EQ(res1, 1);
    EXPECT_EQ(res2, 0);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, print_with_enter) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain, "print('test\\n')\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "test\n\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, print_with_2enter) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain, "print('test\\r\\n\\n')\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "test\r\n\n\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, print_ddd) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain, "print(\"[Info]: in Python config ...\")\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "[Info]: in Python config ...\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, for_in_string) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "s = PikaStdData.String('test')\n"
            "for c in s:\n"
            "    print(c)\n"
            "\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[4], "BEGIN\n");
    EXPECT_STREQ(log_buff[3], "t\r\n");
    EXPECT_STREQ(log_buff[2], "e\r\n");
    EXPECT_STREQ(log_buff[1], "s\r\n");
    EXPECT_STREQ(log_buff[0], "t\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, string_no_init_arg) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "s = PikaStdData.String()\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[3], "BEGIN\r\n");
    EXPECT_STREQ(log_buff[2],
                 "TypeError: __init__() takes 1 positional argument but 0 were "
                 "given\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, obj_no_free) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "s = PikaStdData.String()\n"
            "s.set('test')\n"
            "s = PikaStdData.String()\n"
            "s.set('test')\n"
            "\n");
    /* collect */
    /* assert */
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, list__set__) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "list = PikaStdData.List()\n"
            "__set__(list, 0, 2, 'list')\n"
            "res = __get__(list, 0)\n"
            "\n");
    /* collect */
    int res = obj_getInt(pikaMain, "res");
    /* assert */
    EXPECT_EQ(res, 2);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, string__get__) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "s = PikaStdData.String('test')\n"
            "res = __get__(s, 2)\n"
            "\n");
    /* collect */
    char* res = obj_getStr(pikaMain, "res");
    /* assert */
    EXPECT_STREQ(res, "s");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, dict__set__get) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "list = PikaStdData.Dict()\n"
            "__set__(list, 'a', 2, 'list')\n"
            "res = __get__(list, 'a')\n"
            "\n");
    /* collect */
    int res = obj_getInt(pikaMain, "res");
    /* assert */
    EXPECT_EQ(res, 2);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, str___get____set__) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "s = 'test'\n"
            "res = __get__(s, 2)\n"
            "__set__(s, 2, 'q', 's')\n"
            "\n");
    /* collect */
    char* res = obj_getStr(pikaMain, "res");
    char* s = obj_getStr(pikaMain, "s");
    /* assert */
    EXPECT_STREQ(res, "s");
    EXPECT_STREQ(s, "teqt");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, str__index__) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "s = 'test'\n"
            "res = s[2]\n"
            "res2 = 'eqrt'[2]\n"
            "s[2] = 'q'\n"
            "\n");
    /* collect */
    char* res = obj_getStr(pikaMain, "res");
    char* res2 = obj_getStr(pikaMain, "res2");
    char* s = obj_getStr(pikaMain, "s");
    /* assert */
    EXPECT_STREQ(res, "s");
    EXPECT_STREQ(res2, "r");
    EXPECT_STREQ(s, "teqt");
    // EXPECT_STREQ(s, "teqt");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, list_index) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "list = PikaStdData.List()\n"
            "list[0] = 2\n"
            "res = list[0]\n"
            "\n");
    /* collect */
    int res = obj_getInt(pikaMain, "res");
    /* assert */
    EXPECT_EQ(res, 2);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, dict_index) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\n");
    obj_run(pikaMain,
            "dict = PikaStdData.Dict()\n"
            "dict['a'] = 2\n"
            "res = dict['a']\n"
            "\n");
    /* collect */
    int res = obj_getInt(pikaMain, "res");
    /* assert */
    EXPECT_EQ(res, 2);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, task_run_once) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    obj_run(pikaMain,
            "def todo1():\n"
            "    print('task 1 running...')\n"
            "def todo2():\n"
            "    print('task 2 running...')\n"
            "task = GTestTask.Task()\n"
            "task.call_always(todo1)\n"
            "task.call_always(todo2)\n"
            "task.run_once()\n"
            "\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "task 2 running...\r\n");
    EXPECT_STREQ(log_buff[1], "task 1 running...\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, task_run_when) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    obj_run(pikaMain,
            "def todo1():\n"
            "    print('task 1 running...')\n"
            "def todo2():\n"
            "    print('task 2 running...')\n"
            "def todo3():\n"
            "    print('task 3 running...')\n"
            "def when3():\n"
            "    return True\n"
            "task = GTestTask.Task()\n"
            "task.call_always(todo1)\n"
            "task.call_always(todo2)\n"
            "task.call_when(todo3, when3)\n"
            "task.run_once()\n"
            "\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "task 3 running...\r\n");
    EXPECT_STREQ(log_buff[1], "task 2 running...\r\n");
    EXPECT_STREQ(log_buff[2], "task 1 running...\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, task_run_period_until) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "def todo1():\n"
            "    print('task 1 running...')\n"
            "def todo2():\n"
            "    print('task 2 running...')\n"
            "def todo3():\n"
            "    print('task 3 running...')\n"
            "def when3():\n"
            "    return True\n"
            "task = GTestTask.Task()\n"
            "task.call_period_ms(todo1, 200)\n"
            "task.call_period_ms(todo2, 500)\n"
            "# task.call_when(todo3, when3)\n"
            "task.run_until_ms(1000)\n"
            "\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "task 1 running...\r\n");
    EXPECT_STREQ(log_buff[1], "task 1 running...\r\n");
    EXPECT_STREQ(log_buff[2], "task 2 running...\r\n");
    EXPECT_STREQ(log_buff[3], "task 1 running...\r\n");
    EXPECT_STREQ(log_buff[4], "task 1 running...\r\n");
    EXPECT_STREQ(log_buff[5], "task 2 running...\r\n");
    EXPECT_STREQ(log_buff[6], "task 1 running...\r\n");
    EXPECT_STREQ(log_buff[7], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, fun_call) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "def fun(a,b,c,d,e):\n"
            "    print(a)\n"
            "    print(b)\n"
            "    print(c)\n"
            "    print(d)\n"
            "    print(e)\n"
            "fun(10,20,30,40, 'xxx')\n"
            "\n");
    /* assert */
    EXPECT_STREQ(log_buff[0], "xxx\r\n");
    EXPECT_STREQ(log_buff[1], "40\r\n");
    EXPECT_STREQ(log_buff[2], "30\r\n");
    EXPECT_STREQ(log_buff[3], "20\r\n");
    EXPECT_STREQ(log_buff[4], "10\r\n");
    EXPECT_STREQ(log_buff[5], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, global) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "x = 0\n"
            "a = 0\n"
            "z = 0\n"
            "def test_global():\n"
            "    global x\n"
            "    global y, z\n"
            "    x = 1\n"
            "    a = 1\n"
            "    z = 1\n"
            "    print('test global')\n"
            "test_global()\n"
            "\n");
    /* assert */
    int x = obj_getInt(pikaMain, "x");
    int a = obj_getInt(pikaMain, "a");
    int z = obj_getInt(pikaMain, "z");
    EXPECT_EQ(x, 1);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(z, 1);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, complex_str) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "print('test,test')\n");
    /* assert */
    EXPECT_STREQ(log_buff[0], "test,test\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, synac_err_1) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "print('testtest)\n");
    /* assert */
    EXPECT_STREQ(log_buff[0], "[error]: Syntax error.\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_arg) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    Args* buffs = New_strBuff();
    char* pikaAsm = Parser_multiLineToAsm(buffs,
                                          "class Test(TinyObj):\n"
                                          "    x = 1\n"
                                          "\n"
                                          "test = Test()\n"
                                          "print(test.x)\n");
    printf("%s", pikaAsm);
    pikaVM_runAsm(pikaMain, pikaAsm);
    /* assert */
    EXPECT_STREQ(log_buff[0], "1\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    args_deinit(buffs);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_def) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(self,
            "class Test():\n"
            "    x = 1\n"
            "    def hello(self, x):\n"
            "        return x + 2\n"
            "test = Test()\n"
            "x = test.hello(test.x)\n"
            "print(x)\n");
    /* collect */
    PikaObj* test = obj_getObj(self, "test");
    EXPECT_EQ(obj_refcntNow(test), 1);
    /* assert */
    EXPECT_STREQ(log_buff[0], "3\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_def_print) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(self,
            "class Test():\n"
            "    x = 1\n"
            "    def hi(self):\n"
            "        print('hi' + str(self.x))\n"
            "test = Test()\n"
            "test.hi()\n");
    /* assert */
    EXPECT_STREQ(log_buff[0], "hi1\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_demo_1) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(self,
            "class MyClass:\n"
            "    i = 12345\n"
            "    def f(self):\n"
            "        return 'hello world'\n"
            "        \n"
            "x = MyClass()\n"
            " \n"
            "print(x.i)\n"
            "print(x.f())\n");
    /* assert */
    EXPECT_STREQ(log_buff[0], "hello world\r\n");
    EXPECT_STREQ(log_buff[1], "12345\r\n");
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    /* deinit */
    obj_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_demo_2) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(self,
            "class Complex:\n"
            "    def __init__(self):\n"
            "        self.r = 3.0\n"
            "        self.i = -4.5\n"
            "x = Complex()\n"
            "print(x.r)\n"
            "print(x.i)\n");
    /* assert */
    EXPECT_STREQ(log_buff[0], "-4.500000\r\n");
    EXPECT_STREQ(log_buff[1], "3.000000\r\n");
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    /* deinit */
    obj_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_demo_3) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(self,
            "class people:\n"
            "    def speak(self):\n"
            "        print('i am a people')\n"
            " \n"
            "class student(people):\n"
            "    def speak(self):\n"
            "        print('i am a student')\n"
            " \n"
            "p = people()\n"
            "s = student()\n"
            "p.speak()\n"
            "s.speak()\n");
    /* assert */
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    EXPECT_STREQ(log_buff[1], "i am a people\r\n");
    EXPECT_STREQ(log_buff[0], "i am a student\r\n");
    /* deinit */
    obj_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_demo_save_asm) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(self,
            "class people:\n"
            "    def speak(self):\n"
            "        print('i am a people')\n"
            " \n"
            "class student(people):\n"
            "    def speak(self):\n"
            "        print('i am a student')\n"
            " \n");
    obj_run(self,
            "p = people()\n"
            "s = student()\n"
            "p.speak()\n"
            "s.speak()\n");
    /* assert */
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    EXPECT_STREQ(log_buff[1], "i am a people\r\n");
    EXPECT_STREQ(log_buff[0], "i am a student\r\n");
    /* deinit */
    obj_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, for_if_continue_byte_code) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    pikaVM_run(pikaMain,
               "a = 0\n"
               "for i in range(0, 10):\n"
               "    if i == 5:\n"
               "        continue\n"
               "    a = a + i\n"
               "\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    /* assert */
    EXPECT_EQ(a, 40);
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, print_in_def_byte_code) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_run(pikaMain,
               "def test_print():\n"
               "    print('test')\n"
               "test_print()\n");
    /* collect */
    /* assert */
    /* should only print once, so the second log (log_buff[1]) shuold be '\0' */
    EXPECT_STREQ(log_buff[0], "test\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_demo_1_file) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    char lines[] =
        "class MyClass:\n"
        "    i = 12345\n"
        "    def f(self):\n"
        "        return 'hello world'\n"
        "        \n"
        "x = MyClass()\n"
        " \n"
        "print(x.i)\n"
        "print(x.f())\n";
    pikaCompile("pika_bytecode.bin", lines);
    char bytecodebuff[4096] = {0};
    FILE* f = __platform_fopen("pika_bytecode.bin", "rb");
    printf("size: %ld\n", fread(bytecodebuff, 1, 4096, f));
    __platform_printf("BEGIN\r\n");
    pikaVM_runByteCode(self, (uint8_t*)bytecodebuff);
    /* assert */
    EXPECT_STREQ(log_buff[0], "hello world\r\n");
    EXPECT_STREQ(log_buff[1], "12345\r\n");
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    /* deinit */
    obj_deinit(self);
    __platform_fclose(f);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, get_native_method) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    /* do some thing */
    Args args = {0};
    args_setStr(&args, "val", "test");
    obj_runNativeMethod(pikaMain, "print", &args);
    args_deinit_stack(&args);
    /* assert */
    EXPECT_STREQ(log_buff[0], "test\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, hex_list) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_run(pikaMain,
               "bytes = PikaStdData.List()\n"
               "bytes.append(0x0F)\n"
               "bytes.append(0xFF)\n"
               "sum = 0\n"
               "for byte in bytes:\n"
               "    sum = sum + byte\n"
               "\n"
               "print(sum)\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "270\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, bytearray) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_run(pikaMain,
               "bytes = PikaStdData.ByteArray()\n"
               "bytes.fromString('test')\n"
               "sum = 0\n"
               "for byte in bytes:\n"
               "    sum = sum + byte\n"
               "\n"
               "print(sum)\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "448\r\n");
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, not_4_space) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_run(pikaMain, "  print('test')\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "[error]: Syntax error.\r\n");
    EXPECT_STREQ(
        log_buff[1],
        "IndentationError: unexpected indent, only support 4 spaces\r\n");
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, self_operator) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_run(pikaMain,
               "a = 1\n"
               "b = 2\n"
               "c = 3\n"
               "d = 4\n"
               "a += 2\n"
               "b -= 1+1-3\n"
               "c *= 4\n"
               "d /= 2\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    int b = obj_getInt(pikaMain, "b");
    int c = obj_getInt(pikaMain, "c");
    int d = obj_getInt(pikaMain, "d");
    /* assert */
    EXPECT_EQ(a, 3);
    EXPECT_EQ(b, 3);
    EXPECT_EQ(c, 12);
    EXPECT_EQ(d, 2);
    /* deinit */
    obj_deinit(pikaMain);
    /* mem check */
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_demo_2_initwitharg) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* self = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(self,
            "class Complex:\n"
            "    def __init__(self, r, i):\n"
            "        self.r = r\n"
            "        self.i = i\n"
            "x = Complex(3.0, -4.5)\n"
            "print(x.r)\n"
            "print(x.i)\n");
    /* assert */
    EXPECT_STREQ(log_buff[0], "-4.500000\r\n");
    EXPECT_STREQ(log_buff[1], "3.000000\r\n");
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    /* deinit */
    obj_deinit(self);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, def_args_err) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain, "print()\n");
    /* collect */

    /* assert */

    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_args_err) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain, "mem = PikaStdLib.MemChecker(0)\n");
    /* collect */

    /* assert */
    EXPECT_STREQ(log_buff[4],
                 "TypeError: PikaStdLib.MemChecker() takes no arguments\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, int_) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain, "a = int('3')\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    /* assert */
    EXPECT_EQ(a, 3);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, len_) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain, "a = len('331dd')\n");
    /* collect */
    int a = obj_getInt(pikaMain, "a");
    /* assert */
    EXPECT_EQ(a, 5);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, def_in_shell) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);

    /* skip the first obj_run */
    obj_run(pikaMain, "'BEGIN'");
    /* as run in shell */
    obj_run(pikaMain,
            "def test():\n"
            "    print('test')\n"
            "\n");
    obj_run(pikaMain,
            "def test2():\n"
            "    print('test2')\n"
            "\n");
    obj_run(pikaMain, "test()\n");
    obj_run(pikaMain, "test2()\n");
    /* collect */
    /* assert */
    EXPECT_STREQ("test2\r\n", log_buff[0]);
    EXPECT_STREQ("test\r\n", log_buff[1]);
    EXPECT_STREQ("BEGIN\r\n", log_buff[2]);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, def_in_shell_override) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);

    /* skip the first obj_run */
    obj_run(pikaMain, "'BEGIN'");
    /* as run in shell */
    obj_run(pikaMain,
            "def test():\n"
            "    print('test')\n"
            "\n");
    obj_run(pikaMain, "test()\n");
    obj_run(pikaMain,
            "def test():\n"
            "    print('test2')\n"
            "\n");
    obj_run(pikaMain, "test()\n");
    /* collect */
    /* assert */
    EXPECT_STREQ("test2\r\n", log_buff[0]);
    EXPECT_STREQ("test\r\n", log_buff[1]);
    EXPECT_STREQ("BEGIN\r\n", log_buff[2]);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_in_shell) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);

    /* skip the first obj_run */
    obj_run(pikaMain, "'BEGIN'");
    /* as run in shell */
    obj_run(pikaMain,
            "class Test():\n"
            "    def hi(self):\n"
            "        print('hi')\n"
            "\n");
    obj_run(pikaMain,
            "t = Test()\n"
            "t.hi()\n");
    /* collect */
    /* assert */
    EXPECT_STREQ("hi\r\n", log_buff[0]);
    EXPECT_STREQ("BEGIN\r\n", log_buff[1]);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, class_TinyObj) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);

    /* skip the first obj_run */
    obj_run(pikaMain, "'BEGIN'");
    /* as run in shell */
    obj_run(pikaMain,
            "class MyClass( TinyObj ):\n"
            "    def __init__(self):\n"
            "        self.val = 123\n"
            "\n");
    obj_run(pikaMain,
            "x = MyClass()\n"
            "x.val\n");
    /* collect */
    /* assert */
    EXPECT_STREQ("123\r\n", log_buff[0]);
    EXPECT_STREQ("BEGIN\r\n", log_buff[1]);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, list_sysobj) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);

    /* skip the first obj_run */
    obj_run(pikaMain,
            "a = list()\n"
            "a.len()\n");
    /* as run in shell */
    /* collect */
    /* assert */
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

#if PIKA_BUILTIN_LIST_ENABLE
TEST(pikaMain, list_init) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "a = [1, 2, 3]\n"
            "a.len()\n");
    /* as run in shell */
    /* collect */
    /* assert */
    EXPECT_STREQ("3\r\n", log_buff[0]);
    EXPECT_STREQ("BEGIN\r\n", log_buff[1]);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}
#endif

TEST(pikaMain, ctypes) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    char* lines =
        "t = ctypes.Test()\n"
        "sendbuf = b'\\x03\\x04\\x33\\x00\\x05'\n"
        "rlen = ctypes.c_uint(0)\n"
        "rcvbuf = ctypes.c_char_p('')\n"
        "res = t.dc_cpuapdu_hex(5, sendbuf, rlen, rcvbuf)\n"
        "t.print_rcv(rcvbuf)\n";
    __platform_printf("%s\n", lines);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, lines);
    /* as run in shell */
    /* collect */
    Arg* sendbuf = obj_getArg(pikaMain, "sendbuf");
    Arg* rcvbuf = obj_getArg(pikaMain, "rcvbuf.value");
    /* assert */
    EXPECT_EQ(arg_getBytesSize(sendbuf), 5);
    EXPECT_EQ(arg_getBytesSize(rcvbuf), 6);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, import_err) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    char* lines = "import qqpe\n";
    __platform_printf("%s\n", lines);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, lines);
    /* as run in shell */
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[2],
                 "ModuleNotFoundError: No module named 'qqpe'\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(pikaMain, cmodule_in_py) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    /* run */
    PikaObj* pikaMain = pikaScriptInit();
    char* lines =
        "import test_cmodule\n"
        "test_cmodule.test_mem()\n";
    __platform_printf("%s\n", lines);
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, lines);
    /* as run in shell */
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    EXPECT_STREQ(log_buff[1], "mem used max:\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}
