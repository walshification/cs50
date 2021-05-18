#include <math.h>

#include "helpers.h"

int calculate_average_color(RGBTRIPLE pixel);
int calc_avg_red(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_avg_green(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_avg_blue(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_edge_red(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_edge_blue(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_edge_green(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_sobel_red_x(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_sobel_red_y(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_sobel_green_x(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_sobel_green_y(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_sobel_blue_x(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);
int calc_sobel_blue_y(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Average the current color values.
            int average_color = calculate_average_color(image[i][j]);

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
    // Copy the original image.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            copy[i][j] = image[i][j];
        }
    }

    // For each pixel, check the copy pixel values to blur.
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j].rgbtRed = calc_avg_red(i, j, height, width, copy);
            image[i][j].rgbtGreen = calc_avg_green(i, j, height, width, copy);
            image[i][j].rgbtBlue = calc_avg_blue(i, j, height, width, copy);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the original image.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            copy[i][j] = image[i][j];
        }
    }

    // For each pixel, check the copy pixel values to blur.
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Apply Sobel operator to each pixel color value.
            image[i][j].rgbtRed = calc_edge_red(i, j, height, width, copy);
            image[i][j].rgbtGreen = calc_edge_green(i, j, height, width, copy);
            image[i][j].rgbtBlue = calc_edge_blue(i, j, height, width, copy);
        }
    }
    return;
}

/**
 * Function: calculate_average_color
 * ---------------------------------
 * Returns the average color value of a given pixel.
 *
 * pixel (RGBTRIPLE): the pixel whose values will be averaged.
 *
 * returns: (int)
 */
int calculate_average_color(RGBTRIPLE pixel)
{
    // Be careful to divide by a float and round the result!
    return round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);
}

/**
 * Function: calculate_average_red
 * -------------------------------
 * Return the average value of a hue and its surrounding pixels.
 *
 * v_idx (int): the current vertical index.
 * h_idx (int): the current horizontal index.
 * hgt (int): max height of the image.
 * wdt (int): max width of the image.
 * img (RGBTRIPLE): the image to blur.
 *
 * returns: (int)
 */
int calc_avg_red(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int total = 1;
    int average_numerator = img[v_idx][h_idx].rgbtRed;
    if (v_idx > 0)
    {
        average_numerator += img[v_idx - 1][h_idx].rgbtRed;
        total += 1;

        if (h_idx < wdt - 1)
        {
            average_numerator += img[v_idx - 1][h_idx + 1].rgbtRed;
            total += 1;
        }

        if (h_idx > 0)
        {
            average_numerator += img[v_idx - 1][h_idx - 1].rgbtRed;
            total += 1;
        }
    }

    if (h_idx > 0)
    {
        average_numerator += img[v_idx][h_idx - 1].rgbtRed;
        total += 1;
    }

    if (h_idx < wdt - 1)
    {
        average_numerator += img[v_idx][h_idx + 1].rgbtRed;
        total += 1;
    }

    if (v_idx < hgt - 1)
    {
        average_numerator += img[v_idx + 1][h_idx].rgbtRed;
        total += 1;

        if (h_idx < wdt - 1)
        {
            average_numerator += img[v_idx + 1][h_idx + 1].rgbtRed;
            total += 1;
        }

        if (h_idx > 0)
        {
            average_numerator += img[v_idx + 1][h_idx - 1].rgbtRed;
            total += 1;
        }
    }

    return round(average_numerator / (float)total);
}

/**
 * Function: calculate_average_blue
 * --------------------------------
 * Return the average value of a hue and its surrounding pixels.
 *
 * v_idx (int): the current vertical index.
 * h_idx (int): the current horizontal index.
 * hgt (int): max height of the image.
 * wdt (int): max width of the image.
 * img (RGBTRIPLE): the image to blur.
 *
 * returns: (int)
 */
int calc_avg_blue(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int total = 1;
    int average_numerator = img[v_idx][h_idx].rgbtBlue;
    if (v_idx > 0)
    {
        average_numerator += img[v_idx - 1][h_idx].rgbtBlue;
        total += 1;

        if (h_idx < wdt - 1)
        {
            average_numerator += img[v_idx - 1][h_idx + 1].rgbtBlue;
            total += 1;
        }

        if (h_idx > 0)
        {
            average_numerator += img[v_idx - 1][h_idx - 1].rgbtBlue;
            total += 1;
        }
    }

    if (h_idx > 0)
    {
        average_numerator += img[v_idx][h_idx - 1].rgbtBlue;
        total += 1;
    }

    if (h_idx < wdt - 1)
    {
        average_numerator += img[v_idx][h_idx + 1].rgbtBlue;
        total += 1;
    }

    if (v_idx < hgt - 1)
    {
        average_numerator += img[v_idx + 1][h_idx].rgbtBlue;
        total += 1;

        if (h_idx < wdt - 1)
        {
            average_numerator += img[v_idx + 1][h_idx + 1].rgbtBlue;
            total += 1;
        }

        if (h_idx > 0)
        {
            average_numerator += img[v_idx + 1][h_idx - 1].rgbtBlue;
            total += 1;
        }
    }

    return round(average_numerator / (float)total);
}

/**
 * Function: calculate_average_green
 * ---------------------------------
 * Return the average value of a hue and its surrounding pixels.
 *
 * v_idx (int): the current vertical index.
 * h_idx (int): the current horizontal index.
 * hgt (int): max height of the image.
 * wdt (int): max width of the image.
 * img (RGBTRIPLE): the image to blur.
 *
 * returns: (int)
 */
int calc_avg_green(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int total = 1;
    int average_numerator = img[v_idx][h_idx].rgbtGreen;
    if (v_idx > 0)
    {
        average_numerator += img[v_idx - 1][h_idx].rgbtGreen;
        total += 1;

        if (h_idx < wdt - 1)
        {
            average_numerator += img[v_idx - 1][h_idx + 1].rgbtGreen;
            total += 1;
        }

        if (h_idx > 0)
        {
            average_numerator += img[v_idx - 1][h_idx - 1].rgbtGreen;
            total += 1;
        }
    }

    if (h_idx > 0)
    {
        average_numerator += img[v_idx][h_idx - 1].rgbtGreen;
        total += 1;
    }

    if (h_idx < wdt - 1)
    {
        average_numerator += img[v_idx][h_idx + 1].rgbtGreen;
        total += 1;
    }

    if (v_idx < hgt - 1)
    {
        average_numerator += img[v_idx + 1][h_idx].rgbtGreen;
        total += 1;

        if (h_idx < wdt - 1)
        {
            average_numerator += img[v_idx + 1][h_idx + 1].rgbtGreen;
            total += 1;
        }

        if (h_idx > 0)
        {
            average_numerator += img[v_idx + 1][h_idx - 1].rgbtGreen;
            total += 1;
        }
    }

    return round(average_numerator / (float)total);
}

/**
 * Function: calc_edge_red
 * -----------------------
 * Return the value of a hue after applying the Sobel operator.
 *
 * v_idx (int): the current vertical index.
 * h_idx (int): the current horizontal index.
 * hgt (int): max height of the image.
 * wdt (int): max width of the image.
 * img (RGBTRIPLE): the image to blur.
 *
 * returns: (int)
 */
int calc_edge_red(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gx = calc_sobel_red_x(v_idx, h_idx, hgt, wdt, img);
    int gy = calc_sobel_red_y(v_idx, h_idx, hgt, wdt, img);
    int sq_sum = round(sqrt((gx * gx * 1.0) + (gy * gy)));
    if (sq_sum > 255)
    {
        return 255;
    }
    return sq_sum;
}

int calc_sobel_red_x(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gx = 0;
    if (v_idx > 0)
    {
        // north
        gx += img[v_idx - 1][h_idx].rgbtRed * 0;

        if (h_idx < wdt - 1)
        {
            // northeast
            gx += img[v_idx - 1][h_idx + 1].rgbtRed * 1;
        }

        if (h_idx > 0)
        {
            // northwest
            gx += img[v_idx - 1][h_idx - 1].rgbtRed * -1;
        }
    }

    if (h_idx > 0)
    {
        // west
        gx += img[v_idx][h_idx - 1].rgbtRed * -2;
    }

    if (h_idx < wdt - 1)
    {
        // east
        gx += img[v_idx][h_idx + 1].rgbtRed * 2;
    }

    if (v_idx < hgt - 1)
    {
        // south
        gx += img[v_idx + 1][h_idx].rgbtRed * 0;

        if (h_idx < wdt - 1)
        {
            // southeast
            gx += img[v_idx + 1][h_idx + 1].rgbtRed * 1;
        }

        if (h_idx > 0)
        {
            // southwest
            gx += img[v_idx + 1][h_idx - 1].rgbtRed * -1;
        }
    }

    return gx;
}

int calc_sobel_red_y(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gy = 0;
    if (v_idx > 0)
    {
        // north
        gy += img[v_idx - 1][h_idx].rgbtRed * -2;

        if (h_idx < wdt - 1)
        {
            // northeast
            gy += img[v_idx - 1][h_idx + 1].rgbtRed * -1;
        }

        if (h_idx > 0)
        {
            // northwest
            gy += img[v_idx - 1][h_idx - 1].rgbtRed * -1;
        }
    }

    if (h_idx > 0)
    {
        // west
        gy += img[v_idx][h_idx - 1].rgbtRed * 0;
    }

    if (h_idx < wdt - 1)
    {
        // east
        gy += img[v_idx][h_idx + 1].rgbtRed * 0;
    }

    if (v_idx < hgt - 1)
    {
        // south
        gy += img[v_idx + 1][h_idx].rgbtRed * 2;

        if (h_idx < wdt - 1)
        {
            // southeast
            gy += img[v_idx + 1][h_idx + 1].rgbtRed * 1;
        }

        if (h_idx > 0)
        {
            // southwest
            gy += img[v_idx + 1][h_idx - 1].rgbtRed * 1;
        }
    }

    return gy;
}

/**
 * Function: calc_edge_blue
 * ------------------------
 * Return the value of a hue after applying the Sobel operator.
 *
 * v_idx (int): the current vertical index.
 * h_idx (int): the current horizontal index.
 * hgt (int): max height of the image.
 * wdt (int): max width of the image.
 * img (RGBTRIPLE): the image to blur.
 *
 * returns: (int)
 */
int calc_edge_blue(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gx = calc_sobel_blue_x(v_idx, h_idx, hgt, wdt, img);
    int gy = calc_sobel_blue_y(v_idx, h_idx, hgt, wdt, img);
    int sq_sum = round(sqrt((gx * gx * 1.0) + (gy * gy)));
    if (sq_sum > 255)
    {
        return 255;
    }
    return sq_sum;
}

int calc_sobel_blue_x(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gx = 0;
    if (v_idx > 0)
    {
        // north
        gx += img[v_idx - 1][h_idx].rgbtBlue * 0;

        if (h_idx < wdt - 1)
        {
            // northeast
            gx += img[v_idx - 1][h_idx + 1].rgbtBlue * 1;
        }

        if (h_idx > 0)
        {
            // northwest
            gx += img[v_idx - 1][h_idx - 1].rgbtBlue * -1;
        }
    }

    if (h_idx > 0)
    {
        // west
        gx += img[v_idx][h_idx - 1].rgbtBlue * -2;
    }

    if (h_idx < wdt - 1)
    {
        // east
        gx += img[v_idx][h_idx + 1].rgbtBlue * 2;
    }

    if (v_idx < hgt - 1)
    {
        // south
        gx += img[v_idx + 1][h_idx].rgbtBlue * 0;

        if (h_idx < wdt - 1)
        {
            // southeast
            gx += img[v_idx + 1][h_idx + 1].rgbtBlue * 1;
        }

        if (h_idx > 0)
        {
            // southwest
            gx += img[v_idx + 1][h_idx - 1].rgbtBlue * -1;
        }
    }

    return gx;
}

int calc_sobel_blue_y(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gy = 0;
    if (v_idx > 0)
    {
        // north
        gy += img[v_idx - 1][h_idx].rgbtBlue * -2;

        if (h_idx < wdt - 1)
        {
            // northeast
            gy += img[v_idx - 1][h_idx + 1].rgbtBlue * -1;
        }

        if (h_idx > 0)
        {
            // northwest
            gy += img[v_idx - 1][h_idx - 1].rgbtBlue * -1;
        }
    }

    if (h_idx > 0)
    {
        // west
        gy += img[v_idx][h_idx - 1].rgbtBlue * 0;
    }

    if (h_idx < wdt - 1)
    {
        // east
        gy += img[v_idx][h_idx + 1].rgbtBlue * 0;
    }

    if (v_idx < hgt - 1)
    {
        // south
        gy += img[v_idx + 1][h_idx].rgbtBlue * 2;

        if (h_idx < wdt - 1)
        {
            // southeast
            gy += img[v_idx + 1][h_idx + 1].rgbtBlue * 1;
        }

        if (h_idx > 0)
        {
            // southwest
            gy += img[v_idx + 1][h_idx - 1].rgbtBlue * 1;
        }
    }

    return gy;
}

/**
 * Function: calc_edge_green
 * ------------------------
 * Return the value of a hue after applying the Sobel operator.
 *
 * v_idx (int): the current vertical index.
 * h_idx (int): the current horizontal index.
 * hgt (int): max height of the image.
 * wdt (int): max width of the image.
 * img (RGBTRIPLE): the image to blur.
 *
 * returns: (int)
 */
int calc_edge_green(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gx = calc_sobel_green_x(v_idx, h_idx, hgt, wdt, img);
    int gy = calc_sobel_green_y(v_idx, h_idx, hgt, wdt, img);
    int sq_sum = round(sqrt((gx * gx * 1.0) + (gy * gy)));
    if (sq_sum > 255)
    {
        return 255;
    }
    return sq_sum;
}

int calc_sobel_green_x(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gx = 0;
    if (v_idx > 0)
    {
        // north
        gx += img[v_idx - 1][h_idx].rgbtGreen * 0;

        if (h_idx < wdt - 1)
        {
            // northeast
            gx += img[v_idx - 1][h_idx + 1].rgbtGreen * 1;
        }

        if (h_idx > 0)
        {
            // northwest
            gx += img[v_idx - 1][h_idx - 1].rgbtGreen * -1;
        }
    }

    if (h_idx > 0)
    {
        // west
        gx += img[v_idx][h_idx - 1].rgbtGreen * -2;
    }

    if (h_idx < wdt - 1)
    {
        // east
        gx += img[v_idx][h_idx + 1].rgbtGreen * 2;
    }

    if (v_idx < hgt - 1)
    {
        // south
        gx += img[v_idx + 1][h_idx].rgbtGreen * 0;

        if (h_idx < wdt - 1)
        {
            // southeast
            gx += img[v_idx + 1][h_idx + 1].rgbtGreen * 1;
        }

        if (h_idx > 0)
        {
            // southwest
            gx += img[v_idx + 1][h_idx - 1].rgbtGreen * -1;
        }
    }

    return gx;
}

int calc_sobel_green_y(int v_idx, int h_idx, int hgt, int wdt, RGBTRIPLE img[hgt][wdt])
{
    int gy = 0;
    if (v_idx > 0)
    {
        // north
        gy += img[v_idx - 1][h_idx].rgbtGreen * -2;

        if (h_idx < wdt - 1)
        {
            // northeast
            gy += img[v_idx - 1][h_idx + 1].rgbtGreen * -1;
        }

        if (h_idx > 0)
        {
            // northwest
            gy += img[v_idx - 1][h_idx - 1].rgbtGreen * -1;
        }
    }

    if (h_idx > 0)
    {
        // west
        gy += img[v_idx][h_idx - 1].rgbtGreen * 0;
    }

    if (h_idx < wdt - 1)
    {
        // east
        gy += img[v_idx][h_idx + 1].rgbtGreen * 0;
    }

    if (v_idx < hgt - 1)
    {
        // south
        gy += img[v_idx + 1][h_idx].rgbtGreen * 2;

        if (h_idx < wdt - 1)
        {
            // southeast
            gy += img[v_idx + 1][h_idx + 1].rgbtGreen * 1;
        }

        if (h_idx > 0)
        {
            // southwest
            gy += img[v_idx + 1][h_idx - 1].rgbtGreen * 1;
        }
    }

    return gy;
}
