#include "foo.h"

Foo::Foo()
{
}

int Foo::GetNum()
{
    return m_num;
}

void Foo::SetNum( int num )
{
    m_num = num;
}
