#ifndef CBOX_H
#define CBOX_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

class CBox                                  // Class definition at global scope
{
    public:
    double m_Length ;                   // Length of a box in inches
    double m_Width;                    // Width of a box in inches
    double m_Height;                   // Height of a box in inches

     // Constructor definition
    CBox(double lv, double wv, double hv);
    CBox();

    // Function to calculate the volume of a box
    double volume();

};
#endif // CBOX_H
