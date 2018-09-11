#ifndef PRODUCTOBJ_H
#define PRODUCTOBJ_H

#include <string>

#include <Poco/Data/Session.h>

#include "BaseObj.h"

using std::string;

using Poco::Data::Session;

using table::BaseObj;

namespace table {
    class ProductObj : public BaseObj{
    private:
        string table_name;
        int id;
        string name;
        int value;
//        virtual string intToString(int);

    public:
        ProductObj();
        ProductObj(int,string,int);
        void setId(int);
        void setName(string);
        void setValue(int);
        int getId();
        string getName();
        int getValue();
        string getTableName();
        virtual string selectCmd(Session);
        virtual string updateCmd(Session);
        virtual string deleteCmd(Session);
        virtual string insertCmd(Session);
        virtual string createTableCmd(Session);
        virtual string dropTableCmd(Session);
        virtual string printType();
    };

}

#endif // PRODUCTOBJ_H
