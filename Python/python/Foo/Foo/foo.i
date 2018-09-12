%module foo
%{
#include "foo.h"
%}

class Foo
{
public:
    Foo();
    int GetNum();
    void SetNum(int num);

private:
    int m_num;
};
