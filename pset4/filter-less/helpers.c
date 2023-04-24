#include "helpers.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

// Convert image to grayscale
void swap(BYTE *a, BYTE *b);
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get rgb from pixel
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            // do avg
            int gs = round((r + g + b) / 3.0);
            // replace rgb to avg
            image[i][j].rgbtRed = gs;
            image[i][j].rgbtGreen = gs;
            image[i][j].rgbtBlue = gs;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get rgb from pixel
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            // apply sepia formula
            float sepiaR = 0.393 * r + 0.769 * g + 0.189 * b;
            float sepiaG = 0.349 * r + 0.686 * g + 0.168 * b;
            float sepiaB = 0.272 * r + 0.534 * g + 0.131 * b;
            // if sepia range is over 255 limit to 255 or round the range
            if (round(sepiaR) > 255)
            {
                r = 255;
            }
            else
            {
                r = round(sepiaR);
            }
            // if sepia range is over 255 limit to 255
            if (round(sepiaG) > 255)
            {
                g = 255;
            }
            else
            {
                g = round(sepiaG);
            }
            // if sepia range is over 255 limit to 255
            if (round(sepiaB) > 255)
            {
                b = 255;
            }
            else
            {
                b = round(sepiaB);
            }
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap first pixel with last, second with last - 1
            swap(&image[i][j].rgbtRed, &image[i][width - 1 - j].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - 1 - j].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - 1 - j].rgbtBlue);
        }
    }
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //int avgRed, avgGreen, avgBlue, count;
    // copy images
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // row 0
            if (x == 0)
            {
                count++;
                // corner left
                if (y == 0)
                {
                    image[x][y].rgbtRed = round((copy[x][y].rgbtRed + copy[x + 1][y].rgbtRed + copy[x][y + 1].rgbtRed + copy[x + 1][y + 1].rgbtRed) / 4.0);
                    image[x][y].rgbtGreen = round((copy[x][y].rgbtGreen + copy[x + 1][y].rgbtGreen + copy[x][y + 1].rgbtGreen + copy[x + 1][y + 1].rgbtGreen) / 4.0);
                    image[x][y].rgbtBlue = round((copy[x][y].rgbtBlue + copy[x + 1][y].rgbtBlue + copy[x][y + 1].rgbtBlue + copy[x + 1][y + 1].rgbtBlue) / 4.0);
                }
                // corner right
                else if (y == width - 1)

                {
                    image[x][y].rgbtRed = round((copy[x][y - 1].rgbtRed + copy[x][y].rgbtRed + copy[x + 1][y - 1].rgbtRed + copy[x + 1][y].rgbtRed) / 4.0);
                    image[x][y].rgbtGreen = round((copy[x][y - 1].rgbtGreen + copy[x][y].rgbtGreen + copy[x + 1][y - 1].rgbtGreen + copy[x + 1][y].rgbtGreen) / 4.0);
                    image[x][y].rgbtBlue = round((copy[x][y - 1].rgbtBlue + copy[x][y].rgbtBlue + copy[x + 1][y - 1].rgbtBlue + copy[x + 1][y].rgbtBlue) / 4.0);
                }
                // edge 0
                else
                {
                    image[x][y].rgbtRed = round((copy[x][y - 1].rgbtRed + copy[x][y].rgbtRed + copy[x][y + 1].rgbtRed + copy[x + 1][y - 1].rgbtRed + copy[x + 1][y].rgbtRed + copy[x + 1][y + 1].rgbtRed) / 6.0);
                    image[x][y].rgbtGreen = round((copy[x][y - 1].rgbtGreen + copy[x][y].rgbtGreen + copy[x][y + 1].rgbtGreen + copy[x + 1][y - 1].rgbtGreen + copy[x + 1][y].rgbtGreen + copy[x + 1][y + 1].rgbtGreen) / 6.0);
                    image[x][y].rgbtBlue = round((copy[x][y - 1].rgbtBlue + copy[x][y].rgbtBlue + copy[x][y + 1].rgbtBlue + copy[x + 1][y - 1].rgbtBlue + copy[x + 1][y].rgbtBlue + copy[x + 1][y + 1].rgbtBlue) / 6.0);
                }
            }
            // final row
            else if (x == height - 1)
            {
                // corner left
                if (y == 0)
                {
                    image[x][y].rgbtRed = round((copy[x - 1][y].rgbtRed + copy[x - 1][y + 1].rgbtRed + copy[x][y].rgbtRed + copy[x][y + 1].rgbtRed) / 4.0);
                    image[x][y].rgbtGreen = round((copy[x - 1][y].rgbtGreen + copy[x - 1][y + 1].rgbtGreen + copy[x][y].rgbtGreen + copy[x][y + 1].rgbtGreen) / 4.0);
                    image[x][y].rgbtBlue = round((copy[x - 1][y].rgbtBlue + copy[x - 1][y + 1].rgbtBlue + copy[x][y].rgbtBlue + copy[x][y + 1].rgbtBlue) / 4.0);
                }
                // corner right
                else if (y == width - 1)
                {
                    image[x][y].rgbtRed = round((copy[x - 1][y - 1].rgbtRed + copy[x][y - 1].rgbtRed + copy[x - 1][y].rgbtRed + copy[x][y].rgbtRed) / 4.0);
                    image[x][y].rgbtGreen = round((copy[x - 1][y - 1].rgbtGreen + copy[x][y - 1].rgbtGreen + copy[x - 1][y].rgbtGreen + copy[x][y].rgbtGreen) / 4.0);
                    image[x][y].rgbtBlue = round((copy[x - 1][y - 1].rgbtBlue + copy[x][y - 1].rgbtBlue + copy[x - 1][y].rgbtBlue + copy[x][y].rgbtBlue) / 4.0);
                }
                // edge final
                else
                {
                    image[x][y].rgbtRed = round((copy[x - 1][y - 1].rgbtRed + copy[x - 1][y].rgbtRed + copy[x - 1][y + 1].rgbtRed + copy[x][y - 1].rgbtRed + copy[x][y].rgbtRed + copy[x][y + 1].rgbtRed) / 6.0);
                    image[x][y].rgbtGreen = round((copy[x - 1][y - 1].rgbtGreen + copy[x - 1][y].rgbtGreen + copy[x - 1][y + 1].rgbtGreen + copy[x][y - 1].rgbtGreen + copy[x][y].rgbtGreen + copy[x][y + 1].rgbtGreen) / 6.0);
                    image[x][y].rgbtBlue = round((copy[x - 1][y - 1].rgbtBlue + copy[x - 1][y].rgbtBlue + copy[x - 1][y + 1].rgbtBlue + copy[x][y - 1].rgbtBlue + copy[x][y].rgbtBlue + copy[x][y + 1].rgbtBlue) / 6.0);
                }
            }
            // others row
            else
            {
                // first column
                if (y == 0)
                {
                    image[x][y].rgbtRed = round((copy[x - 1][y].rgbtRed + copy[x - 1][y + 1].rgbtRed + copy[x][y].rgbtRed + copy[x][y + 1].rgbtRed + copy[x + 1][y].rgbtRed + copy[x + 1][y + 1].rgbtRed) / 6.0);
                    image[x][y].rgbtGreen = round((copy[x - 1][y].rgbtGreen + copy[x - 1][y + 1].rgbtGreen + copy[x][y].rgbtGreen + copy[x][y + 1].rgbtGreen + copy[x + 1][y].rgbtGreen + copy[x + 1][y + 1].rgbtGreen) / 6.0);
                    image[x][y].rgbtBlue = round((copy[x - 1][y].rgbtBlue + copy[x - 1][y + 1].rgbtBlue + copy[x][y].rgbtBlue + copy[x][y + 1].rgbtBlue + copy[x + 1][y].rgbtBlue + copy[x + 1][y + 1].rgbtBlue) / 6.0);
                }
                // last column
                else if (y == width - 1)
                {
                    image[x][y].rgbtRed = round((copy[x - 1][y - 1].rgbtRed + copy[x-1][y].rgbtRed + copy[x][y-1].rgbtRed + copy[x][y].rgbtRed + copy[x + 1][y - 1].rgbtRed + copy[x+1][y].rgbtRed) / 6.0);
                    image[x][y].rgbtGreen = round((copy[x - 1][y - 1].rgbtGreen + copy[x-1][y].rgbtGreen + copy[x][y-1].rgbtGreen + copy[x][y].rgbtGreen + copy[x + 1][y - 1].rgbtGreen + copy[x+1][y].rgbtGreen) / 6.0);
                    image[x][y].rgbtBlue = round((copy[x - 1][y - 1].rgbtBlue + copy[x-1][y].rgbtBlue + copy[x][y-1].rgbtBlue + copy[x][y].rgbtBlue + copy[x + 1][y - 1].rgbtBlue + copy[x+1][y].rgbtBlue) / 6.0);
                }
                // middle pix
                else
                {
                    image[x][y].rgbtRed = round((copy[x - 1][y - 1].rgbtRed + copy[x][y - 1].rgbtRed + copy[x + 1][y - 1].rgbtRed + copy[x - 1][y].rgbtRed + copy[x][y].rgbtRed + copy[x + 1][y].rgbtRed + copy[x - 1][y + 1].rgbtRed + copy[x][y + 1].rgbtRed + copy[x + 1][y + 1].rgbtRed) / 9.0);
                    image[x][y].rgbtGreen = round((copy[x - 1][y - 1].rgbtGreen + copy[x][y - 1].rgbtGreen + copy[x + 1][y - 1].rgbtGreen + copy[x - 1][y].rgbtGreen + copy[x][y].rgbtGreen + copy[x + 1][y].rgbtGreen + copy[x - 1][y + 1].rgbtGreen + copy[x][y + 1].rgbtGreen + copy[x + 1][y + 1].rgbtGreen) / 9.0);
                    image[x][y].rgbtBlue = round((copy[x - 1][y - 1].rgbtBlue + copy[x][y - 1].rgbtBlue + copy[x + 1][y - 1].rgbtBlue + copy[x - 1][y].rgbtBlue + copy[x][y].rgbtBlue + copy[x + 1][y].rgbtBlue + copy[x - 1][y + 1].rgbtBlue + copy[x][y + 1].rgbtBlue + copy[x + 1][y + 1].rgbtBlue) / 9.0);
                }
            }
        }
    }
}

// swap method get 2 Bytes and swapea
void swap(BYTE *a, BYTE *b)
{
    BYTE temp = *a;
    *a = *b;
    *b = temp;
}