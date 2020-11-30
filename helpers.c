#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR = 0;
    int tempG = 0;
    int tempB = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            tempR = image[y][x].rgbtRed;
            tempG = image[y][x].rgbtGreen;
            tempB = image[y][x].rgbtBlue;
            float almost = tempR + tempG + tempB;
            int done = round(almost / 3);
            image[y][x].rgbtRed = done;
            image[y][x].rgbtGreen = done;
            image[y][x].rgbtBlue = done;
            
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR = 0;
    int tempG = 0;
    int tempB = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            tempR = image[y][x].rgbtRed;
            tempG = image[y][x].rgbtGreen;
            tempB = image[y][x].rgbtBlue;
            if (round(0.393 * tempR + 0.769 * tempG + 0.189 * tempB) > 255)
            {
                image[y][x].rgbtRed = 255;
            }
            else
            {
                image[y][x].rgbtRed = round(0.393 * tempR + 0.769 * tempG + 0.189 * tempB);
            }
            if (round(0.349 * tempR + 0.686 * tempG + 0.168 * tempB) > 255)
            {
                image[y][x].rgbtGreen = 255;
            }
            else
            {
                image[y][x].rgbtGreen = round(0.349 * tempR + 0.686 * tempG + 0.168 * tempB);
            }
            if (round(0.272 * tempR + 0.534 * tempG + 0.131 * tempB) > 255)
            {
                image[y][x].rgbtBlue = 255;
            }
            {
                image[y][x].rgbtBlue = round(0.272 * tempR + 0.534 * tempG + 0.131 * tempB);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int pmax;
    if (width % 2 == 0)
    {
        pmax = (width / 2);
    }
    else
    {
        pmax = round((width / 2) - 0.5);
    }
    typedef struct
    {
        int R;
        int G;
        int B;
    }
    tempe;
    tempe temp[1];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {  
            if (x == pmax)
            {
                break;
            }
            temp[0].R = image[y][x].rgbtRed;
            temp[0].G = image[y][x].rgbtGreen;
            temp[0].B = image[y][x].rgbtBlue;
            image[y][x].rgbtRed = image[y][width - 1 - x].rgbtRed;
            image[y][x].rgbtGreen = image[y][width - 1 - x].rgbtGreen;
            image[y][x].rgbtBlue = image[y][width - 1 - x].rgbtBlue;
            image[y][width - 1 - x].rgbtRed = temp[0].R;
            image[y][width - 1 - x].rgbtGreen = temp[0].G;
            image[y][width - 1 - x].rgbtBlue = temp[0].B;
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //this one is complicated so i added notes for it
    //i know i did this very badly and coulve used functions but im tierd and i just ate cheteos so i have brain fog.
    //copies data to temporary 2d array
    RGBTRIPLE temp[height][width];
    double tempR = 0;
    double tempG = 0;
    double tempB = 0;
    int tempx = 0;
    int tempy = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++) 
        {
            tempR = 0;
            tempG = 0;
            tempB = 0;
            tempx = 0;
            tempy = 0;
            //if pixel is on top left
            if (x == 0 && y == 0)
            {
                tempx = x;
                tempy = y;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //right
                tempR += image[y][x + 1].rgbtRed;
                tempG += image[y][x + 1].rgbtGreen;
                tempB += image[y][x + 1].rgbtBlue;
                //bottom
                tempR += image[1][x].rgbtRed;
                tempG += image[1][x].rgbtGreen;
                tempB += image[1][x].rgbtBlue;
                //bottom right
                tempR += image[1][1].rgbtRed;
                tempG += image[1][1].rgbtGreen;
                tempB += image[1][1].rgbtBlue;

                tempR = round(tempR / 4);
                tempG = round(tempG / 4);
                tempB = round(tempB / 4);

                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            //if pixel is on top right
            else if (x == width - 1 && y == 0)
            {
                tempx = x;
                tempy = y;
                //left
                tempR += image[y][x - 1].rgbtRed;
                tempG += image[y][x - 1].rgbtGreen;
                tempB += image[y][x - 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //bottom left
                tempR += image[y + 1][x - 1].rgbtRed;
                tempG += image[y + 1][x - 1].rgbtGreen;
                tempB += image[y + 1][x - 1].rgbtBlue;
                //bottom
                tempR += image[y + 1][x].rgbtRed;
                tempG += image[y + 1][x].rgbtGreen;
                tempB += image[y + 1][x].rgbtBlue;
                
                tempR = round(tempR / 4);
                tempG = round(tempG / 4);
                tempB = round(tempB / 4);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
                
            }
            //if pixel is on bottom left
            else if (x == 0 && y == height - 1)
            {
                tempx = x;
                tempy = y;
                //top
                tempR += image[y - 1][x].rgbtRed;
                tempG += image[y - 1][x].rgbtGreen;
                tempB += image[y - 1][x].rgbtBlue;
                //top right
                tempR += image[y - 1][x + 1].rgbtRed;
                tempG += image[y - 1][x + 1].rgbtGreen;
                tempB += image[y - 1][x + 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //right
                tempR += image[y][x + 1].rgbtRed;
                tempG += image[y][x + 1].rgbtGreen;
                tempB += image[y][x + 1].rgbtBlue;
                tempR = round(tempR / 4);
                tempG = round(tempG / 4);
                tempB = round(tempB / 4);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            //if pixel in on bottom right
            else if (x == width - 1 && y == height - 1)
            {
                tempx = x;
                tempy = y;
                //top left
                tempR += image[y -1 ][x - 1].rgbtRed;
                tempG += image[y - 1][x - 1].rgbtGreen;
                tempB += image[y - 1][x - 1].rgbtBlue;
                //top
                tempR += image[y - 1][x].rgbtRed;
                tempG += image[y - 1][x].rgbtGreen;
                tempB += image[y - 1][x].rgbtBlue;
                //left
                tempR += image[y][x - 1].rgbtRed;
                tempG += image[y][x - 1].rgbtGreen;
                tempB += image[y][x - 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                tempR = round(tempR / 4);
                tempG = round(tempG / 4);
                tempB = round(tempB / 4);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            //if pixel is on top
            else if (y == 0)
            {
                tempx = x;
                tempy = y;
                //left
                tempR += image[y][x - 1].rgbtRed;
                tempG += image[y][x - 1].rgbtGreen;
                tempB += image[y][x - 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //right
                tempR += image[y][x + 1].rgbtRed;
                tempG += image[y][x + 1].rgbtGreen;
                tempB += image[y][x + 1].rgbtBlue;
                
                //bottom left
                tempR += image[y + 1][x - 1].rgbtRed;
                tempG += image[y + 1][x - 1].rgbtGreen;
                tempB += image[y + 1][x - 1].rgbtBlue;
                //bottom
                tempR += image[y + 1][x].rgbtRed;
                tempG += image[y + 1][x].rgbtGreen;
                tempB += image[y + 1][x].rgbtBlue;
                //bottom right
                tempR += image[y + 1][x + 1].rgbtRed;
                tempG += image[y + 1][x + 1].rgbtGreen;
                tempB += image[y + 1][x + 1].rgbtBlue;
                
                tempR = round(tempR / 6);
                tempG = round(tempG / 6);
                tempB = round(tempB / 6);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            //if pixel is on bottom
            else if (y == height - 1)
            {
                tempx = x;
                tempy = y;
                //top left
                tempR += image[y - 1][x - 1].rgbtRed;
                tempG += image[y - 1][x - 1].rgbtGreen;
                tempB += image[y - 1][x - 1].rgbtBlue;
                //top
                tempR += image[y - 1][x].rgbtRed;
                tempG += image[y - 1][x].rgbtGreen;
                tempB += image[y - 1][x].rgbtBlue;
                //top right
                tempR += image[y - 1][x + 1].rgbtRed;
                tempG += image[y - 1][x + 1].rgbtGreen;
                tempB += image[y - 1][x + 1].rgbtBlue;
                //left
                tempR += image[y][x - 1].rgbtRed;
                tempG += image[y][x - 1].rgbtGreen;
                tempB += image[y][x - 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //right
                tempR += image[y][x + 1].rgbtRed;
                tempG += image[y][x + 1].rgbtGreen;
                tempB += image[y][x + 1].rgbtBlue;
                tempR = round(tempR / 6);
                tempG = round(tempG / 6);
                tempB = round(tempB / 6);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            //if pixel is on left
            else if (x == 0)
            {
                tempx = x;
                tempy = y;
                //top
                tempR += image[y - 1][x].rgbtRed;
                tempG += image[y - 1][x].rgbtGreen;
                tempB += image[y - 1][x].rgbtBlue;
                //top right
                tempR += image[y - 1][x + 1].rgbtRed;
                tempG += image[y - 1][x + 1].rgbtGreen;
                tempB += image[y - 1][x + 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //right
                tempR += image[y][x + 1].rgbtRed;
                tempG += image[y][x + 1].rgbtGreen;
                tempB += image[y][x + 1].rgbtBlue;
                //bottom
                tempR += image[y + 1][x].rgbtRed;
                tempG += image[y + 1][x].rgbtGreen;
                tempB += image[y + 1][x].rgbtBlue;
                //bottom right
                tempR += image[y + 1][x + 1].rgbtRed;
                tempG += image[y + 1][x + 1].rgbtGreen;
                tempB += image[y + 1][x + 1].rgbtBlue;
                tempR = round(tempR / 6);
                tempG = round(tempG / 6);
                tempB = round(tempB / 6);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            //if pixel is on right
            else if (x == width - 1)
            {
                tempx = x;
                tempy = y;
                //top left
                tempR += image[y - 1][x - 1].rgbtRed;
                tempG += image[y - 1][x - 1].rgbtGreen;
                tempB += image[y - 1][x - 1].rgbtBlue;
                //top
                tempR += image[y - 1][x].rgbtRed;
                tempG += image[y - 1][x].rgbtGreen;
                tempB += image[y - 1][x].rgbtBlue;
                //left
                tempR += image[y][x - 1].rgbtRed;
                tempG += image[y][x - 1].rgbtGreen;
                tempB += image[y][x - 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //bottom left
                tempR += image[y + 1][x - 1].rgbtRed;
                tempG += image[y + 1][x - 1].rgbtGreen;
                tempB += image[y + 1][x - 1].rgbtBlue;
                //bottom
                tempR += image[y + 1][x].rgbtRed;
                tempG += image[y + 1][x].rgbtGreen;
                tempB += image[y + 1][x].rgbtBlue;
                tempR = round(tempR / 6);
                tempG = round(tempG / 6);
                tempB = round(tempB / 6);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            else
            {
                tempx = x;
                tempy = y;
                //top left
                tempR += image[y - 1][x - 1].rgbtRed;
                tempG += image[y - 1][x - 1].rgbtGreen;
                tempB += image[y - 1][x - 1].rgbtBlue;
                //top
                tempR += image[y - 1][x].rgbtRed;
                tempG += image[y - 1][x].rgbtGreen;
                tempB += image[y - 1][x].rgbtBlue;
                //top right
                tempR += image[y - 1][x + 1].rgbtRed;
                tempG += image[y - 1][x + 1].rgbtGreen;
                tempB += image[y - 1][x + 1].rgbtBlue;
                //left
                tempR += image[y][x - 1].rgbtRed;
                tempG += image[y][x - 1].rgbtGreen;
                tempB += image[y][x - 1].rgbtBlue;
                //mid
                tempR += image[y][x].rgbtRed;
                tempG += image[y][x].rgbtGreen;
                tempB += image[y][x].rgbtBlue;
                //right
                tempR += image[y][x + 1].rgbtRed;
                tempG += image[y][x + 1].rgbtGreen;
                tempB += image[y][x + 1].rgbtBlue;
                //bottom left
                tempR += image[y + 1][x - 1].rgbtRed;
                tempG += image[y + 1][x - 1].rgbtGreen;
                tempB += image[y + 1][x - 1].rgbtBlue;
                //bottom
                tempR += image[y + 1][x].rgbtRed;
                tempG += image[y + 1][x].rgbtGreen;
                tempB += image[y + 1][x].rgbtBlue;
                //bottom right
                tempR += image[y + 1][x + 1].rgbtRed;
                tempG += image[y + 1][x + 1].rgbtGreen;
                tempB += image[y + 1][x + 1].rgbtBlue;
                
                tempR = round(tempR / 9);
                tempG = round(tempG / 9);
                tempB = round(tempB / 9);
                temp[y][x].rgbtRed = tempR;
                temp[y][x].rgbtGreen = tempG;
                temp[y][x].rgbtBlue = tempB;
                x = tempx;
                y = tempy;
            }
            
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
