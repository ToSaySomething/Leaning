#ifndef BASEOBJ_H
#define BASEOBJ_H

#include <string>

#include <Poco/Data/Session.h>

using std::string;

using Poco::Data::Session;

namespace table {
    class BaseObj{
    protected:
         string intToString(int);
    public:
        BaseObj(){}
        ~BaseObj(){}
        virtual string selectCmd(Session) = 0;
        virtual string updateCmd(Session) = 0;
        virtual string deleteCmd(Session) = 0;
        virtual string insertCmd(Session) = 0;
        virtual string createTableCmd(Session) = 0;
        virtual string dropTableCmd(Session) = 0;
        virtual string printType() = 0;
    };
}


#endif // BASEOBJ_H
