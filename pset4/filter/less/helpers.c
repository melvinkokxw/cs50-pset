#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 0xFF)
            {
                sepiaRed = 0xFF;
            }

            if (sepiaGreen > 0xFF)
            {
                sepiaGreen = 0xFF;
            }

            if (sepiaBlue > 0xFF)
            {
                sepiaBlue = 0xFF;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create another image array to store reflected values
    RGBTRIPLE reflectedImage[height][width];

    // Create reflected image array
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            reflectedImage[i][j] = image[i][width - 1 - j];
        }
    }

    // Copy reflected image array to normal image array
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = reflectedImage[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create blurred image array
    RGBTRIPLE blurredImage[height][width];

    // For each cell, get the average of the surrounding cells' color
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int redSum = 0, greenSum = 0, blueSum = 0, squareSum = 0;

            for (int row = (i - 1) ; row <= (i + 1) ; row++)
            {
                for (int col = (j - 1) ; col <= (j + 1) ; col++)
                {
                    // If trying to get value for non-existent pixel, skip
                    if (row == -1 || row == height || col == -1 || col == width)
                    {
                        continue;
                    }
                    redSum += image[row][col].rgbtRed;
                    greenSum += image[row][col].rgbtGreen;
                    blueSum += image[row][col].rgbtBlue;

                    squareSum++;
                }
            }

            blurredImage[i][j].rgbtRed = round(redSum / (float)squareSum);
            blurredImage[i][j].rgbtGreen = round(greenSum / (float)squareSum);
            blurredImage[i][j].rgbtBlue = round(blueSum / (float)squareSum);
        }
    }

    // Copy blurred image array to normal image array
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = blurredImage[i][j];
        }
    }
    return;
}
