#ifndef SQLOPER_H
#define SQLOPER_H

#include "Poco/Data/Session.h"
#include "Poco/Data/SessionPool.h"
#include "Poco/SharedPtr.h"
#include "BaseObj.h"

using std::string;

using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::SharedPtr;

namespace Db {
    class SqlOper{
    private:
        static void init();
        static void shutDown();
        static Session getSession();
        static string intToString(int);

    public:
        SqlOper();
        ~SqlOper();

        static string createTable(table::BaseObj*);
        static string selectData(table::BaseObj*);
        static string insertData(table::BaseObj*);
        static string deleteData(table::BaseObj*);
        static string updateData(table::BaseObj*);
    };

}

#endif // SQLOPER_H


