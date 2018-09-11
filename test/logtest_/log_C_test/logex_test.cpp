#include "gtest/gtest.h"
#include "logex/logex.h"
#include "../src/logex/LogStates.h"

// 创建日志实例，每个实例代表一个日志文件
TEST(logex_cwLogCreateInstance, cwLogCreateInstance)
{
    void* hLogInst = cwLogCreateInstance();
    cwLogDestroyInstance(hLogInst);
}

// 写日志前，应该先调用此函数，打开某个日志文件。
// lpszFileName: 日志文件的完整路径。
// 如果日志文件名指定的文件夹不存在，则会自动创建文件夹。
TEST(logex_cwLogOpenFileA, cwLogOpenFileA)
{
    void* hLogInst = cwLogCreateInstance();
    EXPECT_NE(0, cwLogOpenFileA(hLogInst, "./test/log.txt"));
    cwLogCloseFile(hLogInst);
    cwLogDestroyInstance(hLogInst);
}

// 向 LOG 文件中追加一行（会自动插入时间和换行符号）
TEST(logex_cwLogWriteA, cwLogWriteA)
{
    void* hLogInst = cwLogCreateInstance();
    const char* lpszFileName = "./test/log.txt";
    cwLogOpenFileA(hLogInst, lpszFileName);
    EXPECT_NE(0, cwLogWriteA(hLogInst, LOGLEVEL_INFO, " test one : add log level info : 0x20 "));
    cwLogCloseFile(hLogInst);
    cwLogDestroyInstance(hLogInst);
}

// 删除指定文件夹下面的过期文件。（不会递归删除子目录）
// Dir:  文件夹路径。结尾是否带斜杠都无所谓。路径中的分割字符正反斜杠均可。
// LifetimeInDays: 日志文件保留天数。（修改日期距现在的时间如果超过此天数，则将其删除）。
TEST(logex_cwDeleteOverdueFilesA, cwDeleteOverdueFilesA)
{
    void* hLogInst = cwLogCreateInstance();
    cwLogOpenFileA(hLogInst, "./test/log.txt");
    EXPECT_NE(0, cwLogWriteA(hLogInst, LOGLEVEL_INFO, " add log level info : 0x20 "));
    cwLogCloseFile(hLogInst);
    cwLogDestroyInstance(hLogInst);
    cwDeleteOverdueFilesA("./test", 1, "");
}

// 【对数据准确性要求不高，不考虑多线程安全性】
// 设置输出日志的 LEVEL 范围;
// [in] int nLeastSignificantLevel: 严重程度大于等于该值的 LOG 会被输出
TEST(logex_cwLogSetLevelFilter, cwLogSetLevelFilter)
{
    void* hLogInst = cwLogCreateInstance();
    cwLogOpenFileA(hLogInst, "./test/log.txt");

    cwLogSetLevelFilter(hLogInst, LOGLEVEL_ALL);
    EXPECT_EQ(LOGLEVEL_ALL, cwLogGetLevelFilter(hLogInst));

    cwLogWriteA(hLogInst, LOGLEVEL_DEBUG, " add log level debug : 0x10 ");
    cwLogWriteA(hLogInst, LOGLEVEL_INFO, " add log level info : 0x20 ");
    cwLogWriteA(hLogInst, LOGLEVEL_WARN, " add log level warn : 0x30 ");
    cwLogWriteA(hLogInst, LOGLEVEL_ERROR, " add log level error : 0x40 ");
    cwLogWriteA(hLogInst, LOGLEVEL_FATAL, " add log level fatal : 0x50 ");
    cwLogCloseFile(hLogInst);
    cwLogDestroyInstance(hLogInst);
}
TEST(logex_cwLogSetLevelFilter_LOGLEVEL_INFO, cwLogSetLevelFilter)
{
    void* hLogInst = cwLogCreateInstance();
    cwLogOpenFileA(hLogInst, "./test/log.txt");

    cwLogSetLevelFilter(hLogInst, LOGLEVEL_WARN);
    EXPECT_EQ(LOGLEVEL_WARN, cwLogGetLevelFilter(hLogInst));

    cwLogWriteA(hLogInst, LOGLEVEL_DEBUG, " add log level debug : 0x10 ");
    cwLogWriteA(hLogInst, LOGLEVEL_INFO, " add log level info : 0x20 ");
    cwLogWriteA(hLogInst, LOGLEVEL_WARN, " add log level warn : 0x30 ");
    cwLogWriteA(hLogInst, LOGLEVEL_ERROR, " add log level error : 0x40 ");
    cwLogWriteA(hLogInst, LOGLEVEL_FATAL, " add log level fatal : 0x50 ");
    cwLogCloseFile(hLogInst);
    cwLogDestroyInstance(hLogInst);
}

// 【对数据准确性要求不高，不考虑多线程安全性】
// 设置每个日志文件的最大尺寸 （in bytes），当超过这个尺寸时，文件会切换到 $(LOGDIR)\\FileName_2.txt，以此类推。
// nMaxFileSize: 每个日志文件的最大尺寸 (Bytes)。如果为 0，表示文件尺寸不限。
TEST(logex_cwLogSetFileSizeLimit, cwLogSetFileSizeLimit)
{
    void* hLogInst = cwLogCreateInstance();
    cwLogOpenFileA(hLogInst, "./test/log.txt");
    int nMaxFileSize = 1024 * 1024 * 8;
    cwLogSetFileSizeLimit(hLogInst, nMaxFileSize);
    EXPECT_EQ(nMaxFileSize, cwLogGetFileSizeLimit(hLogInst));
    cwLogCloseFile(hLogInst);
    cwLogDestroyInstance(hLogInst);
}
