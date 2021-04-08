#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>

//My own kernel implementation

using namespace cv;
using namespace std;

Vec3b* getSurrounding(Mat input, int i, int j)
{
    Vec3b* retVal = new Vec3b[9];

    int row = 0;
    int column = 0;

    for(int k = 0; k < 9; k++)
    {
        retVal[k] = input.at<Vec3b>(i + row, j + column);

        column++;

        if(column > 2)
        {
            column = 0;
            row++;
        }
    }

    return retVal;
}

Mat setSurrounding(Mat &input, int i, int j, Vec3b* values)
{
    int row = 0;
    int column = 0;

    for(int k = 0; k < 9; k++)
    {
        input.at<Vec3b>(i + row, j + column) = values[k];

        column++;

        if(column > 2)
        {
            column = 0;
            row++;
        }
    }

    return input;
}

int main()
{
    Mat test = imread("../data/Matthew.png", IMREAD_COLOR);

    for(int i = 0; i < test.rows; i += 1)
    {
        if(i + 2 >= test.rows)
            continue;

        for(int j = 0; j < test.cols; j += 1)
        {
            if(j + 2 >= test.cols)
                continue;

            Vec3b* surrounding = getSurrounding(test, i, j);

            int avg_red = 0;
            int avg_green = 0;
            int avg_blue = 0;

            for(int k = 0; k < 9; k++)
            {
                Vec3b intensity = surrounding[k];

                avg_blue += intensity.val[0];
                avg_green += intensity.val[1];
                avg_red += intensity.val[2];

                surrounding[k] = intensity;
            }

            avg_blue /= 9;
            avg_green /= 9;
            avg_red /= 9;

            for(int k = 0; k < 9; k++)
            {
                Vec3b intensity = surrounding[k];

                intensity.val[0] = (intensity.val[0] + avg_blue) / 2;
                intensity.val[1] = (intensity.val[1] + avg_green) / 2;
                intensity.val[2] = (intensity.val[2] + avg_red) / 2;

                surrounding[k] = intensity;
            }

            test = setSurrounding(test, i, j, surrounding);

            Vec3b intensity = test.at<Vec3b>(i,j);
        }
    }

    imwrite("../data/output.png", test);
    cout << "Finished!" << endl;

    return 0;

}
