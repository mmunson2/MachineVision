/***************************************************************************************************
 * Program II Implementation
 *
 * @author Matthew Munson
 * @date 4/17/21
 *
 * Implementation file for CSS 587A program II. This program takes a foreground and background image
 * and uses a color histogram to determine the most common pixel color in the foreground. Pixels
 * within a certain threshold of this color will be replaced with the corresponding pixels in the
 * background image. This creates a sort of "green screen" effect. It is most effective on images
 * with a distinct and consistent background color, such as a blue sky or grey wall.
 *
 * _________________________________________________________________________________________________
 * Assumptions:
 *
 * In the same directory as the this file, this program expects:
 * - foreground.jpg : The foreground image on which the effect will be applied
 * - background.jpg : The image that will be overlayed on the foreground.
 *
 * Upon completion, this program will create:
 * - overlay.jpg : The overlay of background.jpg onto parts of foreground.jpg
 *
 *__________________________________________________________________________________________________
 * Implementation Details:
 *
 * int main()
 * - Program entry point. Loads images, calls getMostCommonColor, then overlayBackground. Displays
 * the overlay image and saves it to file.
 *
 * Vec3b getMostCommonColor(const Mat&image, int buckets)
 * - Returns the most common color in an image.
 *
 *
 * Mat overlayBackground(const Mat& foreground, const Mat& background, const Vec3b& mostCommonColor,
 *                    int threshold)
 * - Overlays a background image onto the foreground image where the pixels are within a certain
 * threshold of the provided most common color
 *
 * Vec3i findMaxBucket(const Mat& hist, int buckets)
 * - Finds the maximum bucket in a 3D histogram and returns it as a Vec3i representing a color
 *
 * void displayImage(const Mat& image, const string windowName)
 * - Displays an image, waits for user input, and destroys the window
 *
 **************************************************************************************************/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static const int HISTOGRAM_BUCKETS = 4;
static const int REPLACEMENT_THRESHOLD = 60;

/***************************************************************************************************
 * Get Most Common Color
 *
 * Finds the most common color in an image.
 *
 * See function implementation for detailed documentation, including purpose, preconditions, and
 * postconditions.
 **************************************************************************************************/
Vec3i getMostCommonColor(const Mat& image, int buckets);

/***************************************************************************************************
 * Overlay Background
 *
 * Overlays a background image onto a foreground, replacing colors within a certain threshold of
 * a provided most common color.
 *
 * See function implementation for detailed documentation, including purpose, preconditions, and
 * postconditions.
 **************************************************************************************************/
Mat overlayBackground(const Mat& foreground,
                      const Mat& background,
                      const Vec3i& mostCommonColor,
                      int threshold);

/***************************************************************************************************
 * Find Max Bucket
 *
 * Helper function for getMostCommonColor. From a 3D histogram, determines which bucket has the
 * greatest count (in other words, the most common color in the image) and returns it as a Vec3i
 * representing a pixel.
 *
 * See function implementation for detailed documentation, including purpose, preconditions, and
 * postconditions.
 **************************************************************************************************/
Vec3i findMaxBucket(const Mat& hist, int buckets);

/***************************************************************************************************
 * Display Image
 *
 * Helper function for displaying an image to a named window, allowing the user to view it until
 * they press a key, and then destroying the window.
 *
 * See function implementation for detailed documentation, including purpose, preconditions, and
 * postconditions.
 **************************************************************************************************/
void displayImage(const Mat& image, const string& windowName);

/***************************************************************************************************
 * Main Function
 *
 * Purpose:
 * Program entry point. Loads the foreground and background image from disk. Determines the most
 * common color in the foreground image. Overlays the background image onto the foreground based
 * on the most common color. Displays the image to the user and saves it to disk.
 *
 * @pre: foreground.jpg and background.jpg are in the working directory.
 * @post: overlay image displayed to screen and saved to disk.
 *
 * @return exit code indicating program status. Zero indicates success.
 **************************************************************************************************/
int main()
{
    string foreground_filename = "foreground.jpg";
    string background_filename = "background.jpg";

    Mat foreground = imread(foreground_filename, IMREAD_COLOR);
    Mat background = imread(background_filename, IMREAD_COLOR);

    Vec3i mostCommonColor = getMostCommonColor(foreground, HISTOGRAM_BUCKETS);

    Mat overlay = overlayBackground(foreground, background, mostCommonColor, REPLACEMENT_THRESHOLD);

    displayImage(overlay, "Overlay Image");

    imwrite("overlay.jpg", overlay);

    return 0;
}

/***************************************************************************************************
 * Overlay Background - Implementation
 *
 * @param foreground : The image which the background will be overlaid onto
 * @param background : The image to overlay onto the foreground
 * @param mostCommonColor : The most common color identified in the foreground image
 * @param threshold : How close to the common color must a pixel be in order to be replaced
 *
 * Purpose:
 *
 * Overlays the background image onto the foreground where foreground pixels are close to the
 * most common color. Loops through each pixel in the foreground image and determines if its
 * red AND green AND blue pixels are all within the provided threshold of the most common color.
 * If this is true, the pixel will be replaced with the corresponding pixel of the background image.
 * If the background image is smaller than the foreground, it will be "tiled" onto the background
 * and form a repeating pattern.
 *
 * @pre: foreground, background, and mostCommonColor are all initialized. Threshold is greater
 *       than zero.
 * @post: background is overlaid onto common color foreground pixels, overlaid image is returned.
 *
 * @return A copy of foreground with background pixels overlaid.
 **************************************************************************************************/
Mat overlayBackground(const Mat& foreground,
                      const Mat& background,
                      const Vec3i& mostCommonColor,
                      int threshold)
{
    Mat overlay = Mat();
    foreground.copyTo(overlay);

    for(int i = 0; i < overlay.rows; i++)
    {
        for(int j = 0; j < overlay.cols; j++)
        {
            Vec3b pixel = overlay.at<Vec3b>(i, j);

            if(abs(pixel[0] - mostCommonColor[0]) < threshold &&
               abs(pixel[1] - mostCommonColor[1]) < threshold &&
               abs(pixel[2] - mostCommonColor[2]) < threshold)
            {

                pixel = background.at<Vec3b>(i % background.rows, j % background.cols);

                overlay.at<Vec3b>(i, j) = pixel;
            }
        }
    }

    return overlay;
}

/***************************************************************************************************
 * Get Most Common Color - Implementation
 *
 * @param image : The image from which the most common color will be determined
 * @param buckets : The amount of buckets in the color histogram used to determine most common color
 *
 * Purpose:
 *
 * Finds the most common color in the provided image using a color histogram. Goes through each
 * pixel and determines which bucket it falls into. Uses findMaxBucket() to determine which bucket
 * has the highest count, and returns this as a Vec3i.
 *
 * @pre: image is initialized and buckets is greater than zero.
 * @post: The most common color in the image is determined and returned as a Vector 3.
 *
 * @return a Vec3b representing the most common color in the provided image
 **************************************************************************************************/
Vec3i getMostCommonColor(const Mat& image, int buckets)
{
    int dims[] = {buckets, buckets, buckets};
    Mat hist(3, dims, CV_32S, Scalar::all(0));

    //Initialize all loop variables
    int blue, green, red, x, y, z, bucketSize;
    Vec3b pixel;

    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            pixel = image.at<Vec3b>(i, j);

            blue = pixel[0];
            green = pixel[1];
            red = pixel[2];

            bucketSize = 256 / buckets;
            x = red / bucketSize;
            y = green / bucketSize;
            z = blue / bucketSize;

            hist.at<int>(z, y, x)++;
        }
    }

    return findMaxBucket(hist, buckets);
}

/***************************************************************************************************
 * Find Max Bucket - Implementation
 *
 * @param hist : The 3D histogram from which the maximum bucket will be determined
 * @param buckets : The amount of buckets in the color histogram used to determine most common color
 *
 * Purpose:
 *
 * From the populated 3D array of buckets, this function finds the max. Based on the number of
 * buckets, it determines what the actual color was (bucket index to pixel conversion) and returns
 * this as the most common color.
 *
 * @pre: hist is initialized and filled with bucket counts. Buckets is greater than 1. Max count is
 *       greater than 0.
 * @post: The bucket with the highest count is determined and returned as a Vector 3.
 *
 * @return a Vec3b representing the most common color in the provided image
 **************************************************************************************************/
Vec3i findMaxBucket(const Mat& hist, int buckets)
{
    Vec3i mostCommonColor = Vec3i(0,0,0);

    int max = 0;

    for(int i = 0; i < buckets; i++)
    {
        for(int j = 0; j < buckets; j++)
        {
            for(int k = 0; k < buckets; k++)
            {
                int count = hist.at<int>(i, j, k);

                if(count > max)
                {
                    max = count;

                    mostCommonColor = Vec3i(i * (256 / buckets),
                                            j * (256 / buckets),
                                            k * (256 / buckets));
                }
            }
        }
    }

    return mostCommonColor;
}

/***************************************************************************************************
 * Display Image - Implementation
 *
 * @param image : The image to be displayed to the user.
 *
 * Purpose:
 *
 * Provides a wrapper around opencv functions for creating a window, showing an image, waiting for
 * the user to press any key, and destroying the window.
 *
 * @pre: Image has been initialized and windowName is not already in use in another window.
 * @post: An image has been displayed to the user.
 *
 * @return None.
 **************************************************************************************************/
void displayImage(const Mat& image, const string& windowName)
{
    namedWindow(windowName);
    imshow(windowName, image);

    waitKey(0);
    destroyWindow(windowName);
}
