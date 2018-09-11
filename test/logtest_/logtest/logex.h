#ifdef _WIN32
#pragma once
#define MAX_PATH_LENGTH MAX_PATH
#else
#define MAX_PATH_LENGTH 512
#endif

//
// 日志操作 C 语言接口 V1.4
// -- jinfude@cloudwalk.cn, 2018-09-04

// dllexport of a C++ function will expose the function with C++ name mangling. 
// If C++ name mangling is not desired, either use a .def file (EXPORTS keyword) 
// or declare the function as extern "C".
//
// referred to ms-help : //MS.VSCC.v80/MS.MSDN.v80/MS.VisualStudio.v80.chs/
// dv_vclang/html/ff95b645-ef55-4e72-b848-df44657b3208.htm
//

#define LOGAPI

#define LOGERR_OK                       0
#define LOGERR_INVALID_PATH             1
#define LOGERR_FILE_NOT_OPEN            2
#define LOGERR_MEM_FULL                 3
#define LOGERR_INSUFFICENT_DISKSPACE    4
#define LOGERR_WIN32_ERROR              5
#define LOGERR_INVALID_PARAM            6
#define LOGERR_CANNOT_CREATE_DIR        7
#define LOGERR_CANNOT_OPEN_FILE         8

//
// 日志的重要程度等级
// 数字越大，表示错误级别越严重。

#define LOGLEVEL_ALL                    0
#define LOGLEVEL_DEBUG                  0x10
#define LOGLEVEL_INFO                   0x20
#define LOGLEVEL_WARN                   0x30
#define LOGLEVEL_ERROR                  0x40
#define LOGLEVEL_FATAL                  0x50
#define LOGLEVEL_OFF                    0x7FFFFFFF

// （应该在单个线程中调用）
// 创建日志实例，每个实例代表一个日志文件
//
void* LOGAPI cwLogCreateInstance();
void LOGAPI cwLogDestroyInstance(void* hLogInst);

// 【多线程安全】
// 写日志前，应该先调用此函数，打开某个日志文件。
// lpszFileName: 日志文件的完整路径。
// 如果日志文件名指定的文件夹不存在，则会自动创建文件夹。

int LOGAPI cwLogOpenFileA(void* hLogInst, const char* lpszFileName);
int LOGAPI cwLogOpenFileW(void* hLogInst, const wchar_t* lpszFileName);

// 【多线程安全】
// 向 LOG 文件中追加一行（会自动插入时间和换行符号）
//
int LOGAPI cwLogWriteA(void* hLogInst, int nLogLevel, const char* szText);
int LOGAPI cwLogWriteW(void* hLogInst, int nLogLevel, const wchar_t* szText);

//【多线程安全】
// 关闭当前打开的日志文件
//
void LOGAPI cwLogCloseFile(void* hLogInst);

// 删除指定文件夹下面的过期文件。（不会递归删除子目录）
// Dir:  文件夹路径。结尾是否带斜杠都无所谓。路径中的分割字符正反斜杠均可。
// LifetimeInDays: 日志文件保留天数。（修改日期距现在的时间如果超过此天数，则将其删除）。
// FileNameFilter: 要删除的文件的通配符。(在 linux 平台: 该参数无效）
//         例如: "*.txt";
//         如果传入 NULL 或者 "*" 表示任何文件类型都匹配。
void LOGAPI cwDeleteOverdueFilesA(const char* Dir, int nLifetimeInDays, const char* FileNameFilter);
void LOGAPI cwDeleteOverdueFilesW(const wchar_t* Dir, int nLifetimeInDays, const wchar_t* FileNameFilter);

// 删除指定文件夹下面的过期文件。（不会递归删除子目录）
// Dir:  文件夹路径。结尾是否带斜杠都无所谓。路径中的分割字符正反斜杠均可。
// LifetimeInDays: 日志文件保留天数。（修改日期距现在的时间如果超过此天数，则将其删除）。
// FileNameFilter: 要删除的文件的通配符。(在 linux 平台: 该参数无效）
//         如果传入 NULL 或者 "*" 表示任何文件类型都匹配。
//         例如: "*.txt";
//         
// Exts:   要删除文件的后缀集合。多个后缀用分号分割，每个后缀前面不要有小数点。
//         如果传入 NULL 或者 "*" 表示任何文件后缀都匹配。
//         例如："TXT;LOG;JPG;BMP";

void LOGAPI cwDeleteOverdueFilesExA(const char* Dir, int nLifetimeInDays, 
	const char* FileNameFilter, const char* Exts);

void LOGAPI cwDeleteOverdueFilesExW(const wchar_t* Dir, int nLifetimeInDays, 
	const wchar_t* FileNameFilter, const wchar_t* Exts);

// 【对数据准确性要求不高，不考虑多线程安全性】
// 设置输出日志的 LEVEL 范围;
// [in] int nLeastSignificantLevel: 严重程度大于等于该值的 LOG 会被输出
//
void LOGAPI cwLogSetLevelFilter(void* hILogInst, int nLeastSignificantLevel);

// 【对数据准确性要求不高，不考虑多线程安全性】
// 获取输出日志的 LEVEL 范围。
//
int LOGAPI cwLogGetLevelFilter(void* hLogInst);

// 【对数据准确性要求不高，不考虑多线程安全性】
// 设置每个日志文件的最大尺寸 （in bytes），当超过这个尺寸时，文件会切换到
// $(LOGDIR)\\FileName_2.txt，以此类推。
//
// nMaxFileSize: 每个日志文件的最大尺寸 (Bytes)。如果为 0，表示文件尺寸不限。

void LOGAPI cwLogSetFileSizeLimit(void* hLogInst, int nMaxFileSize);
int LOGAPI cwLogGetFileSizeLimit(void* hLogInst);

#ifdef _UNICODE
	#define cwLogOpenFile cwLogOpenFileW
	#define cwLogWrite cwLogWriteW
	#define cwDeleteOverdueFiles cwDeleteOverdueFilesW
	#define cwDeleteOverdueFilesEx cwDeleteOverdueFilesExW
#else
	#define cwLogOpenFile cwLogOpenFileA
	#define cwLogWrite cwLogWriteA
	#define cwDeleteOverdueFiles cwDeleteOverdueFilesA
	#define cwDeleteOverdueFilesEx cwDeleteOverdueFilesExA
#endif
