#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int color =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Update pixel values
            image[i][j].rgbtRed = color;
            image[i][j].rgbtGreen = color;
            image[i][j].rgbtBlue = color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            // Update pixel with sepia values
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
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            int tempr = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = tempr;

            int tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = tempg;

            int tempb = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = tempb;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 && i == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          4.0);
            }
            else if (j == 0 && i == height - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j + 1].rgbtBlue) /
                          4.0);
            }
            else if (j == width - 1 && i == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue) /
                          4.0);
            }
            else if (j == width - 1 && i == height - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                          4.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue) /
                          4.0);
            }
            else if (j == 0 && i != 0 && i != height - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i - 1][j].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i - 1][j].rgbtBlue) /
                          6.0);
            }
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                             copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                           copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                           copy[i - 1][j].rgbtBlue) /
                          6.0);
            }
            else if (j != 0 && j != width - 1 && i == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                             copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                           copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                           copy[i][j + 1].rgbtBlue) /
                          6.0);
            }
            else if (j != 0 && j != width - 1 && i == height - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i][j + 1].rgbtBlue) /
                          6.0);
            }
            else
            {
                image[i][j].rgbtRed =
                    round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                           copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                           copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed +
                           copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                          9.0);
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                     copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                     copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                     copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                    9.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                          9.0);
            }
        }
    }
    return;
}
