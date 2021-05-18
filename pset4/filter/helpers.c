#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Average the current color values.
            int current_red = image[i][j].rgbtRed;
            int current_green = image[i][j].rgbtGreen;
            int current_blue = image[i][j].rgbtBlue;
            // Be careful to divide by a float and round the result!
            int average_color = round((current_blue + current_green + current_red) / 3.0);

            // Set each color to the average value for gray.
            image[i][j].rgbtRed = average_color;
            image[i][j].rgbtGreen = average_color;
            image[i][j].rgbtBlue = average_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        // For the first half of the image ...
        for (int j = 0, midway = width / 2.0; j < midway; ++j)
        {
            // Swap the RBG values with the other end.
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
