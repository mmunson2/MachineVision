/*******************************************************************************
 * Program 1 Signatures
 *
 * @author Matthew Munson
 * @date 4/12/2021
 *
 * Header file for methods in the Program1 Class. Contains public methods for
 * examples 1-4. This includes:
 *
 * - Basic image processing
 *
 * - A smoothing slider example
 *
 * - Edge detection slider example
 *
 * - Additional effects example
 *
 *
 * Header file documentation is user-focused. For implementation-level comments
 * including preconditions and postconditions, see Program1.cpp
 *
 ******************************************************************************/

#ifndef OPENCV_TEST_PROGRAM1_H
#define OPENCV_TEST_PROGRAM1_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Program1 {

public:

    /***********************************************************************************************
     * Image Processing Example.
     *
     * Part 1 of the assignment. Rotates the image 180 degrees, converts it to greyscale, blurs it,
     * and detects edges.
     *
     * Transformations are applied to a copy of the input. The input is unchanged.
     *
     * @param An image to be processed
     * @return The image with transformations applied
     **********************************************************************************************/
    static Mat imgProcessingExample(const Mat& image);

    /***********************************************************************************************
     * Smoothing Slider Example
     *
     * Part 2 of the assignment. Allows the user to blur the input image to varying degree using
     * a trackbar. Sigma X and Sigma Y are varied between 1 and 11. Changes are temporary and are
     * not saved.
     *
     * @param An image to be processed
     **********************************************************************************************/
    static void smoothingSliderExample(Mat image);

    /***********************************************************************************************
     * Edge Detection Slider Example:
     *
     * _________________________________
     * NOTES ON EDGE DETECTION SETTINGS:
     * ---------------------------------
     * • Threshold 1 and 2 have the greatest impact on whether the edge detection yields good
     *   results. Low threshold values (below 50) leave artifacts all over the image. Very high
     *   threshold values (above 150) begin to eliminate some of the thinner details in the image.
     *
     * • Sigma X and Y blur the image before Canny() is called on it. I found that these functioned
     *   as "fine grain" controls for the amount of blur applied to the image. Higher sigmas were
     *   required to eliminate noise from pippy.jpg.
     *
     * • Size X and Y affect how many pixels are being averaged in the blurring process. This has
     *   a greater impact on the amount of blur compared to sigma x and y. These values were also
     *   relatively high to eliminate noise in the image.
     *
     *   The ideal settings for my test image were:
     *   __________________________
     *   Size X: 7
     *   Size Y: 7
     *   Sigma X: 7
     *   Sigma Y: 6
     *   Threshold 1: 20
     *   Threshold 2: 60
     *   __________________________
     *
     *   I prioritized creating a clear outline of the cat (so that you could use a "fill" tool
     *   to color in the cat). This may not be the ideal settings for teaching a machine learning
     *   algorithm to recognize cats, as the face is not easy to make out and there is some noise
     *   remaining in the background.
     *
     * @param image
     **********************************************************************************************/
    void edgeDetectionSliderExample(const Mat& image);

    /***********************************************************************************************
     * Additional Image Effects Examples
     *
     * Part 1 of the assignment. Rotates the image 180 degrees, converts it to greyscale, blurs it,
     * and detects edges.
     *
     * Transformations are applied to a copy of the input. The input is unchanged.
     *
     * @param An image to be processed
     **********************************************************************************************/
    static Mat additionalImageEffectsExample(const Mat& image);

    // Getters & Setters:

    int getSizeX() const;
    int getSizeY() const;

    double getSigmaX() const;
    double getSigmaY() const;

    double getThreshold1() const;
    double getThreshold2() const;

    void setSizeX(int sizeX);
    void setSizeY(int sizeY);

    void setSigmaX(double sigmaX);
    void setSigmaY(double sigmaY);

    void setThreshold1(double thresh1);
    void setThreshold2(double thresh2);

private:

    //I use this to allow the trackbar callback to figure out which value it should adjust
    enum TRACKBAR_TYPES
    {
        SIZE_X,
        SIZE_Y,
        SIGMA_X,
        SIGMA_Y,
        THRESHOLD1,
        THRESHOLD2
    };

    //This is the data passed into the callback function, allowing the program to keep its state.
    struct callbackData
    {
        TRACKBAR_TYPES type; // What the trackbar variable should be interpreted as
        Program1* programPtr; // A pointer to 'this', as the function is static
        Mat image; // The image to modify
        string windowName; // The name of the window to display to
    };

    // Instance Variables:

    int sizeX = 1.0;
    int sizeY = 1.0;

    double sigmaX = 1.0;
    double sigmaY = 1.0;

    double threshold1 = 0.0;
    double threshold2 = 0.0;

    // Simple Callback function used in example II
    static void on_smoothing_trackbar(int alphaSlider, void* testImage);

    // The generalized callback function used for all six trackbars
    static void trackbar_callback(int sliderValue, void*combinedData);

    // Applies a blur and canny affect to an image
    static void blur_and_canny(Program1* program,
                               const Mat& image,
                               const string& windowName);

    // Prints all instance variables to console
    static void print_settings(Program1* program);

};


#endif //OPENCV_TEST_PROGRAM1_H
