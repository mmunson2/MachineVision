/***************************************************************************************************
 * Program 1 Driver
 *
 * @author Matthew Munson
 * @date 4/12/2021
 *
 * Driver file. Creates a Program1 object and runs all example functions.
 *
 * - Assumes you have a file named "pippy.jpg" in the working directory
 * - Assumes you have a file named "Mercy.png" in the working directory
 *
 **************************************************************************************************/

#include <iostream>
#include "Program1.h"

using namespace std;

// Purpose: Entry point, runs all Program1 functionality
// Preconditions: "pippy.jpg" and "Mercy.png" in working directory
// Postconditions: "output.jpg" and "step5_output.png" created
int main()
{
    string image1_input_filename = "../data/pippy.jpg";
    string image1_output_filename = "../data/output.jpg";

    string image2_input_filename = "../data/Mercy.png";
    string image2_output_filename = "../data/step5_output.png";

    Program1 program1 = Program1();

    //Step 1: Load an image, run some processing, and save to output.png
    Mat providedImage = imread(image1_input_filename, IMREAD_COLOR);

    Mat output = Program1::imgProcessingExample(providedImage);

    cv::imwrite(image1_output_filename, output);

    //Step 2:
    Program1::smoothingSliderExample(providedImage);

    //Step 3:
    program1.edgeDetectionSliderExample(providedImage);

    //Step 4:
    Mat customImage = imread(image2_input_filename, IMREAD_GRAYSCALE);

    Mat invertedImage = Program1::additionalImageEffectsExample(customImage);

    cv::imwrite(image2_output_filename, invertedImage);

    return 0;
}
