#ifndef TOOL_H
#define TOOL_H

#include <QObject>
#include <sstream>
#include "Poco/JSON/Parser.h"
#include "Poco/SharedPtr.h"
#include "Serialization.pb.h"

using std::string;
using std::stringstream;
using Poco::JSON::Object;
using Poco::SharedPtr;
using tutorial::CmdData;


class ToolSignal:public QObject{
    Q_OBJECT
public:
    explicit ToolSignal(QObject *parent = 0);
    void toolSignalSend(string a){emit toolSignalOpen(a);}
signals:
    void toolSignalOpen(string);

public slots:
};


class Tool{
public :
    static const char *db_pipe_name;
    static const char *sd_pipe_name;
    static SharedPtr<ToolSignal> tool_signal;
    static void showMsgOnMainWindow(string str){emit tool_signal.get()->toolSignalSend(str);}
    static string intToString(int a){stringstream ss;ss<<a;string result = ss.str();return result;}
    static string jsonToStr(Object);
    static Object strToJson(string);
    static string fifoRead(const char*);
    static bool fifoWrite(const char*,string);
    static bool createFifo();
};

#endif // TOOL_H
