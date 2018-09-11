#include "BaseObj.h"

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

string table::BaseObj::intToString(int a){
    stringstream ss;
    ss<<a;
    string result = ss.str();
    return result;
}
