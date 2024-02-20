#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Finds the average of RGB values to set them equal to one another
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Changes RGB values based on equation for sepia filter
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            // Sets RGB values to 255 incase of overflow
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Sets new RGB values for each pixel in the image to create sepia filter
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = 1; j < (width / 2); j++, n++)
        {
            // Temporarily stores RGB values on the left side
            int tmpRed = image[i][j].rgbtRed;
            int tmpGreen = image[i][j].rgbtGreen;
            int tmpBlue = image[i][j].rgbtBlue;

            // Sets new RGB values to the left side
            image[i][j].rgbtRed = image[i][width - n].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - n].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - n].rgbtBlue;


            // Sets new RGB values to the right side
            image[i][width - n].rgbtRed = tmpRed;
            image[i][width - n].rgbtGreen = tmpGreen;
            image[i][width - n].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create new array for a copy of the image
    RGBTRIPLE copy[height][width];

    // Copies image into a new array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = copy[i][j].rgbtRed;
            float totalGreen = copy[i][j].rgbtGreen;
            float totalBlue = copy[i][j].rgbtBlue;
            int divider = 1;

            // Check top left
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                totalRed += copy[i - 1][j - 1].rgbtRed;
                totalGreen += copy[i - 1][j - 1].rgbtGreen;
                totalBlue += copy[i - 1][j - 1].rgbtBlue;
                divider++;
            }

            // Check top middle
            if (i - 1 >= 0)
            {
                totalRed += copy[i - 1][j].rgbtRed;
                totalGreen += copy[i - 1][j].rgbtGreen;
                totalBlue += copy[i - 1][j].rgbtBlue;
                divider++;
            }

            // Check top right
            if (i - 1 >= 0 && j + 1 < width)
            {
                totalRed += copy[i - 1][j + 1].rgbtRed;
                totalGreen += copy[i - 1][j + 1].rgbtGreen;
                totalBlue += copy[i - 1][j + 1].rgbtBlue;
                divider++;
            }

            // Check left
            if (j - 1 >= 0)
            {
                totalRed += copy[i][j - 1].rgbtRed;
                totalGreen += copy[i][j - 1].rgbtGreen;
                totalBlue += copy[i][j - 1].rgbtBlue;
                divider++;
            }

            // Check right
            if (j + 1 < width)
            {
                totalRed += copy[i][j + 1].rgbtRed;
                totalGreen += copy[i][j + 1].rgbtGreen;
                totalBlue += copy[i][j + 1].rgbtBlue;
                divider++;
            }

            // Check bottom left
            if (i + 1 < height && j - 1 >= 0)
            {
                totalRed += copy[i + 1][j - 1].rgbtRed;
                totalGreen += copy[i + 1][j - 1].rgbtGreen;
                totalBlue += copy[i + 1][j - 1].rgbtBlue;
                divider++;
            }

            // Check bottom middle
            if (i + 1 < height)
            {
                totalRed += copy[i + 1][j].rgbtRed;
                totalGreen += copy[i + 1][j].rgbtGreen;
                totalBlue += copy[i + 1][j].rgbtBlue;
                divider++;
            }

            // Check bottom right
            if (i + 1 < height && j + 1 < width)
            {
                totalRed += copy[i + 1][j + 1].rgbtRed;
                totalGreen += copy[i + 1][j + 1].rgbtGreen;
                totalBlue += copy[i + 1][j + 1].rgbtBlue;
                divider++;
            }

            // Get average and blur image
            image[i][j].rgbtRed = round(totalRed / divider);
            image[i][j].rgbtGreen = round(totalGreen / divider);
            image[i][j].rgbtBlue = round(totalBlue / divider);
        }
    }
    return;
}
