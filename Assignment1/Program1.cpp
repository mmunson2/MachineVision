/***************************************************************************************************
 * Program 1 Implementation
 *
 * @author Matthew Munson
 * @date 4/12/2021
 *
 * Implementation file for methods in the Program1 Class. Functions include:
 *
 * Example 1: Basic image processing
 *     - Mat imgProcessingExample(const Mat& image)
 *
 * Example 2: Smoothing Slider Example
 *     - void on_smoothing_trackbar(int alphaSlider, void* testImage)
 *     - void smoothingSliderExample(Mat image)
 *
 * Example 3: Edge Detection Slider Example
 *     - void blur_and_canny(Program1 *program, const Mat& image, const string& windowName)
 *     - void print_settings(Program1 *program)
 *     - void trackbar_callback(int sliderValue, void*combinedData)
 *     - void edgeDetectionSliderExample(const Mat& image)
 *
 * Example 4: Additional Image Effects
 *     - Mat additionalImageEffectsExample(const Mat& image)
 *
 * Getters and Setters for all instance variables
 *     - Size X
 *     - Size Y
 *     - Sigma X
 *     - Sigma Y
 *     - Threshold 1
 *     - Threshold 2
 *
 **************************************************************************************************/

#include "Program1.h"

using namespace std;
using namespace cv;

/***************************************************************************************************
 * PART I
 **************************************************************************************************/

//Purpose: Demonstrate basic image processing
//Preconditions: None
//Postconditions: Image is rotated 180 degrees, grey-scaled, and edges detected.
Mat Program1::imgProcessingExample(const Mat& image)
{
    Mat copy = Mat();

    //Flip the image vertically and horizontally
    flip(image, copy, 0);

    //Reduce the color to greyscale
    cvtColor(copy, copy, COLOR_BGR2GRAY);

    //Blur the image
    GaussianBlur(copy,
                 copy,
                 Size(0,0),
                 2.0,
                 2.0);

    Canny(copy, copy, 20, 60);

    //Display Processed Image:

    string windowName = "Basic Processing";
    namedWindow(windowName);

    imshow(windowName, copy);

    waitKey(0);
    destroyWindow(windowName);


    return copy;
}

/***************************************************************************************************
 * PART II
 **************************************************************************************************/

// Callback function for when the blur trackbar is changed
// Purpose: Handle changes to the blur trackbar
// Preconditions: Trackbar initialized, testImage struct created and passed in
// Postconditions: Image blurred and displayed
void Program1::on_smoothing_trackbar(int alphaSlider, void* testImage)
{
    Mat im = *((Mat*) testImage);

    Mat copy = Mat();

    GaussianBlur(im,
                 copy,
                 Size(0,0),
                 alphaSlider + 1,
                 alphaSlider + 1);

    imshow("Smoothing Adjustment", copy);
};

// Example II code - Creates a trackbar that blurs an image
// Purpose: Demonstrate trackbar usage and blur of an image
// Preconditions: None
// Postconditions: None
void Program1::smoothingSliderExample(Mat image)
{
    string windowName = "Smoothing Adjustment";

    namedWindow(windowName);

    imshow(windowName, image);

    int smoothing_slider = 0;
    int smoothing_max = 10;
    createTrackbar("Smoothing",
                   windowName,
                   &smoothing_slider,
                   smoothing_max,
                   on_smoothing_trackbar,
                   &image);

    waitKey(0);
    destroyWindow(windowName);
}

/***************************************************************************************************
 * PART III
 **************************************************************************************************/

// Applies a gaussian blur and canny edge detection algorithm
// Purpose: Provide a modular interface and wrap openCV functionality
// Preconditions: Program 1 initialized. Window created
// Postconditions: Image display updated
void Program1::blur_and_canny(Program1 *program, const Mat& image, const string& windowName)
{
    Mat copy1 = Mat();
    Mat copy2 = Mat();

    GaussianBlur(image,
                 copy1,
                 Size(program->getSizeX(), program->getSizeY()),
                 program->getSigmaX(),
                 program->getSigmaY());


    imshow("Blur Result", copy1);

    Canny(copy1, copy2, program->getThreshold1(), program->getThreshold2());

    imshow(windowName, copy2);
}

// Prints instance variables to console
// Purpose: Allow the user to see their exact trackbar settings
// Preconditions: None
// Postconditions: None
void Program1::print_settings(Program1 *program)
{
    cout << "__________________________" << endl;
    cout << "Size X: " << program->getSizeX() << endl;
    cout << "Size Y: " << program->getSizeY() << endl;
    cout << "Sigma X: " << program->getSigmaX() << endl;
    cout << "Sigma Y: " << program->getSigmaY() << endl;
    cout << "Threshold 1: " << program->getThreshold1() << endl;
    cout << "Threshold 2: " << program->getThreshold2() << endl;
    cout << "__________________________" << endl << endl;
}

// Generalized Trackbar callback
// Purpose: Handle all changes to any of the six trackbars
// Preconditions: Slider initialized. CombinedData struct initialized.
// Postconditions: Program1 instance variables updated.
void Program1::trackbar_callback(int sliderValue, void*combinedData)
{
    callbackData* data = (callbackData*) combinedData;

    Program1* program = data->programPtr;

    switch(data->type)
    {
        case SIZE_X:
            sliderValue *= 2;
            sliderValue -= 1;

            program->setSizeX(sliderValue);
            break;

        case SIZE_Y:
            sliderValue *= 2;
            sliderValue -= 1;

            program->setSizeY(sliderValue);
            break;

        case SIGMA_X:
            sliderValue += 1;

            program->setSigmaX(sliderValue);
            break;

        case SIGMA_Y:
            sliderValue += 1;

            program->setSigmaY(sliderValue);
            break;

        case THRESHOLD1:
            sliderValue *= 10;

            program->setThreshold1(sliderValue);

            break;

        case THRESHOLD2:
            sliderValue *= 10;

            program->setThreshold2(sliderValue);
            break;
    }

    blur_and_canny(program, data->image, data->windowName);

    print_settings(program);
}


/***************************************************************************************************
 * Edge Detection Slider
 **************************************************************************************************/
// Purpose: Allow the user to adjust six parameters of an edge detection algorithm
// Preconditions: None
// Postconditions: None
void Program1::edgeDetectionSliderExample(const Mat& image)
{
    string windowName = "Edge Detection";
    int defaultSliderSize = 20;
    Mat output = Mat();

    namedWindow(windowName, WINDOW_GUI_NORMAL);
    namedWindow("Blur Result", WINDOW_GUI_NORMAL);

    callbackData size_x_data = {SIZE_X, this, image, windowName};
    callbackData size_y_data = {SIZE_Y, this, image, windowName};
    callbackData sigma_x_data = {SIGMA_X, this, image, windowName};
    callbackData sigma_y_data = {SIGMA_Y, this, image, windowName};
    callbackData threshold1_data = {THRESHOLD1, this, image, windowName};
    callbackData threshold2_data = {THRESHOLD2, this, image, windowName};

    int sizeX_slider = 0;
    int sizeX_max = 10;
    createTrackbar("Blur: Size X",
                   windowName,
                   &sizeX_slider,
                   sizeX_max,
                   trackbar_callback,
                   &size_x_data);

    int sizeY_slider = 0;
    int sizeY_max = 10;
    createTrackbar("Blur: Size Y",
                   windowName,
                   &sizeY_slider,
                   sizeY_max,
                   trackbar_callback,
                   &size_y_data);

    int sigmaX_slider = 0;
    int sigmaX_max = 10;
    createTrackbar("Blur: Sigma X",
                   windowName,
                   &sigmaX_slider,
                   sigmaX_max,
                   trackbar_callback,
                   &sigma_x_data);

    int sigmaY_slider = 0;
    int sigmaY_max = 10;
    createTrackbar("Blur: Sigma Y",
                   windowName,
                   &sigmaY_slider,
                   sigmaY_max,
                   trackbar_callback,
                   &sigma_y_data);

    int thresh1_slider = 0;
    int thresh1_max = 10;
    createTrackbar("Canny: Threshold 1",
                   windowName,
                   &thresh1_slider,
                   thresh1_max,
                   trackbar_callback,
                   &threshold1_data);

    int thresh2_slider = 0;
    int thresh2_max = 10;
    createTrackbar("Canny: Threshold 2",
                   windowName,
                   &thresh2_slider,
                   thresh2_max,
                   trackbar_callback,
                   &threshold2_data);

    imshow(windowName, image);

    waitKey(0);
    destroyWindow(windowName);
    destroyWindow("Blur Result");
}

/***************************************************************************************************
 * PART IV
 **************************************************************************************************/

// Purpose: Show two additional image effects
// Preconditions: None
// Postconditions: Returns the modified image
Mat Program1::additionalImageEffectsExample(const Mat& image)
{
    string windowName = "Additional-Effects";
    Mat inverted;

    //Bitwise not inverts the image
    bitwise_not(image, inverted);

    //Convert Scale with an alpha > 1.0 brightens the image
    convertScaleAbs(inverted, inverted, 2.0);

    imshow(windowName, inverted);

    waitKey(0);
    destroyWindow(windowName);

    return inverted;
}

/***************************************************************************************************
 * GETTERS AND SETTERS
 *
 * Purpose: To provide access to instance variables within the Program1 Object
 * Precondition: Object initialized
 * Postcondition: None for get. Instance variables updated for set.
 **************************************************************************************************/

int Program1::getSizeX() const { return this->sizeX; }
int Program1::getSizeY() const { return this->sizeY; }
double Program1::getSigmaX() const { return this->sigmaX; }
double Program1::getSigmaY() const { return this->sigmaY; }
double Program1::getThreshold1() const { return this->threshold1; }
double Program1::getThreshold2() const { return this->threshold2; }

void Program1::setSizeX(int sizeX) { this->sizeX = sizeX; }
void Program1::setSizeY(int sizeY) { this->sizeY = sizeY; }
void Program1::setSigmaX(double sigmaX) { this->sigmaX = sigmaX; }
void Program1::setSigmaY(double sigmaY) { this->sigmaY = sigmaY; }
void Program1::setThreshold1(double thresh1) { this->threshold1 = thresh1; }
void Program1::setThreshold2(double thresh2) { this->threshold2 = thresh2; }
