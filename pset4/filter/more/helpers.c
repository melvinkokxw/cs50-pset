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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declaring gx and gy kernels
    int gxArray[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyArray[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE edgeImage[height][width];

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            float gxRed = 0, gxGreen = 0, gxBlue = 0;
            float gyRed = 0, gyGreen = 0, gyBlue = 0;

            // Look at each cell in 3x3 matrix, around current cell
            for (int row = i - 1 ; row <= i + 1 ; row++)
            {
                for (int col = j - 1 ; col <= j + 1 ; col++)
                {
                    // If cell is out of bounds, skip
                    if (row == -1 || row == height || col == -1 || col == width)
                    {
                        continue;
                    }

                    // Add weighted gx/gy value of each color
                    gxRed += image[row][col].rgbtRed * gxArray[row - (i - 1)][col - (j - 1)];
                    gxGreen += image[row][col].rgbtGreen * gxArray[row - (i - 1)][col - (j - 1)];
                    gxBlue += image[row][col].rgbtBlue * gxArray[row - (i - 1)][col - (j - 1)];

                    gyRed += image[row][col].rgbtRed * gyArray[row - (i - 1)][col - (j - 1)];
                    gyGreen += image[row][col].rgbtGreen * gyArray[row - (i - 1)][col - (j - 1)];
                    gyBlue += image[row][col].rgbtBlue * gyArray[row - (i - 1)][col - (j - 1)];

                }
            }

            // Add up gx and gy value
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // Cap values at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            edgeImage[i][j].rgbtRed = red;
            edgeImage[i][j].rgbtGreen = green;
            edgeImage[i][j].rgbtBlue = blue;
        }
    }

    // Copy edge image array to normal image array
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = edgeImage[i][j];
        }
    }
    return;
}
