/*******************************************************************************
 *
 *
 ******************************************************************************/

#include <iostream>
#include "Program1.h"

int main()
{
    Program1 test = Program1();

    Mat testImage = imread("../data/Matthew.png", IMREAD_COLOR);

    test.processImage(testImage);

}
