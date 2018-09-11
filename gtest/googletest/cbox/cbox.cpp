#include "cbox.h"

CBox::CBox(double lv, double wv, double hv)
{
    std::cout << "Constructor called." << std::endl;
    m_Length = lv;                          // Set values of
    m_Width = wv;                           // data members
    m_Height = hv;
}


// Default constructor definition
CBox::CBox()
{
    std::cout << "Default constructor called." << std::endl;
}


// Function to calculate the volume of a box
double CBox::volume()
{
	std::cout << " v = "<< m_Length* m_Width* m_Height << std::endl;
    	return m_Length* m_Width* m_Height;
}
