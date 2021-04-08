//
// Created by Matthew Munson on 3/31/21.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>

//Basic pixel manipulation

using namespace cv;
using namespace std;

int main()
{
    Mat test = imread("../data/sadge_bronze.png", IMREAD_UNCHANGED);

    int whiteCount = 0;

    for(int i = 0; i < test.rows; i++)
    {
        for(int j = 0; j < test.cols; j++)
        {
            Vec3b pixel = test.at<Vec3b>(i, j);

            int blue = pixel[0];
            int green = pixel[1];
            int red = pixel[2];

            if(blue < 30 && green < 30 && red < 30)
            {
                blue = 255;
                green = 255;
                red = 255;
                whiteCount++;
            }

            pixel[0] = blue;
            pixel[1] = green;
            pixel[2] = red;

            test.at<Vec3b>(i, j) = pixel;
        }
    }

    imwrite("../data/output.png", test);

    cout << "White Pixel Count: " << whiteCount << endl;
    cout << "Finished!" << endl;
}

