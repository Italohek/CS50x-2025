#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of the original file
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    // loop through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redAverage = 0, greenAverage = 0, blueAverage = 0;
            float count = 0.0;

            // loop to iterate the 3x3 matrix (starts -1 cuz one row above current pixel)
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // takes the position of the neighboor pixel
                    int newHeight = i + k, newWidth = j + l;

                    // prevents the use of a pixel that isn't in the image
                    if (newHeight >= 0 && newHeight < height && newWidth >= 0 && newWidth < width)
                    {
                        // sum the average color of each pixel
                        redAverage += imageCopy[newHeight][newWidth].rgbtRed;
                        greenAverage += imageCopy[newHeight][newWidth].rgbtGreen;
                        blueAverage += imageCopy[newHeight][newWidth].rgbtBlue;
                        count++;
                    }
                }
            }

            // set the average value of each pixel by dividing the average sum by the count value
            image[i][j].rgbtRed = round(redAverage / count);
            image[i][j].rgbtGreen = round(greenAverage / count);
            image[i][j].rgbtBlue = round(blueAverage / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of the original file
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // now we do every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redGx = 0, greenGx = 0, blueGx = 0;
            int redGy = 0, greenGy = 0, blueGy = 0;

            // applying the 3x3 matrix
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int neighboorI = i + k, neighboorJ = j + l;

                    // check if everything is inside the image
                    if (neighboorI >= 0 && neighboorI < height && neighboorJ >= 0 &&
                        neighboorJ < width)
                    {
                        int auxX = Gx[k + 1][l + 1];
                        int auxY = Gy[k + 1][l + 1];

                        redGx += imageCopy[neighboorI][neighboorJ].rgbtRed * auxX;
                        greenGx += imageCopy[neighboorI][neighboorJ].rgbtGreen * auxX;
                        blueGx += imageCopy[neighboorI][neighboorJ].rgbtBlue * auxX;

                        redGy += imageCopy[neighboorI][neighboorJ].rgbtRed * auxY;
                        greenGy += imageCopy[neighboorI][neighboorJ].rgbtGreen * auxY;
                        blueGy += imageCopy[neighboorI][neighboorJ].rgbtBlue * auxY;
                    }
                }
            }
            // calculates the final value by doing pythagoras
            int red = round(sqrt(redGx * redGx + redGy * redGy));
            int green = round(sqrt(greenGx * greenGx + greenGy * greenGy));
            int blue = round(sqrt(blueGx * blueGx + blueGy * blueGy));

            // see if the value exceds 255 (8 bit color)
            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            // updates the right pixel in image
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
