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
            float avg = ((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            image[i][j].rgbtBlue = (int) round(avg);
            image[i][j].rgbtGreen = (int) round(avg);
            image[i][j].rgbtRed = (int) round(avg);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // Array to store the original image, to be swapped later
    RGBTRIPLE swap[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            swap[i][j] = image[i][j];
        }
    }

    // Reflect pixels from the swap array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = swap[i][width - j - 1];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*for (int i = 0; i < 3; i++)
    {
        for (int j = width - 2; j < width; j++)
        {
            printf("image[%i][%i] is %i, %i, %i\n", i, j, image[i][j].rgbtBlue,image[i][j].rgbtGreen, image[i][j].rgbtRed);
        }
    }*/


    // Array to store the original image, so as to not affect averages by overriding values
    RGBTRIPLE swap[height][width];

    float avgB, avgG, avgR = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            swap[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Variables to be used during the computation of averages, below this, in cases of edge or corner
            int iminus = i - 1;
            int iplus = i + 1;
            int jminus = j - 1;
            int jplus = j + 1;

            int z1 = 1;
            int z2 = 1;
            int z3 = 1;
            int z4 = 1;

            float divider = 9.0;

            // Prepares variables needed in the next computation
            if (iminus < 0)
            {
                iminus += 1;
                z1 = 0;
                divider -= 3;

                // In the cases of not only edge, but corner, divider must be = 4
                if (jminus < 0 || jplus > width - 1)
                {
                    divider++;
                }
            }

            if (iplus > height - 1)
            {
                iplus -= 1;
                z2 = 0;
                divider -= 3;

                if (jminus < 0 || jplus > width - 1)
                {
                    divider++;
                }
            }

            if (jminus < 0)
            {
                jminus += 1;
                z3 = 0;
                divider -= 3;

                if (iminus < 0 || iplus > height - 1)
                {
                    divider++;
                }
            }

            if (jplus > width - 1)
            {
                jplus -= 1;
                z4 = 0;
                divider -= 3;

                if (iminus < 0 || iplus > height - 1)
                {
                    divider++;
                }
            }

            // Computes and assigns the avg of all surrounding pixels for each color channel

            // In cases of edge or corner:
            // The altered "i." and "j." variables avoid touching unwanted memory, but
            // by including some pixels twice in the sum.
            // The z(ero)'s variables avoid adding those pixels twice  
            avgB = (swap[iminus][jminus].rgbtBlue * (z1) * (z3) + (z1) * swap[iminus][j].rgbtBlue + (z1) * (z4) * swap[iminus][jplus].rgbtBlue
                            + (z3) * swap[i][jminus].rgbtBlue + swap[i][j].rgbtBlue + (z4) * swap[i][jplus].rgbtBlue
                            + (z2) * (z3) * swap[iplus][jminus].rgbtBlue + (z2) * swap[iplus][j].rgbtBlue + (z2) * (z4) * swap[iplus][jplus].rgbtBlue)
                            / divider;

            image[i][j].rgbtBlue = round(avgB);

            avgG = (swap[iminus][jminus].rgbtGreen * (z1) * (z3) + (z1) * swap[iminus][j].rgbtGreen +  (z1) * (z4) * swap[iminus][jplus].rgbtGreen
                            + (z3) * swap[i][jminus].rgbtGreen + swap[i][j].rgbtGreen + (z4) * swap[i][jplus].rgbtGreen
                            + (z2) * (z3) * swap[iplus][jminus].rgbtGreen + (z2) * swap[iplus][j].rgbtGreen + (z2) * (z4) * swap[iplus][jplus].rgbtGreen)
                            / divider;

            image[i][j].rgbtGreen = round(avgG);

            avgR = (swap[iminus][jminus].rgbtRed * (z1) * (z3) + (z1) * swap[iminus][j].rgbtRed + (z1) * (z4) * swap[iminus][jplus].rgbtRed
                            + (z3) * swap[i][jminus].rgbtRed + swap[i][j].rgbtRed + (z4) * swap[i][jplus].rgbtRed
                            + (z2) * (z3) * swap[iplus][jminus].rgbtRed + (z2) * swap[iplus][j].rgbtRed + (z2) * (z4) * swap[iplus][jplus].rgbtRed)
                            / divider;

            image[i][j].rgbtRed = round(avgR);

            // Resets all variables
            iminus = i - 1;
            iplus = i + 1;
            jminus = j - 1;
            jplus = j + 1;
            z1 = 1;
            z2 = 1;
            z3 = 1;
            z4 = 1;
            divider = 9.0;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap[height][width];

    float Gx_B, Gx_G, Gx_R, Gy_B, Gy_G, Gy_R, b, g, r;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            swap[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For pixels in edges
            if (i == 0 || i == height - 1 || j == 0 || j == width -1)
            {

            if (i == 0)
            {
                // Treats corner cases
                if (j == 0)
                {
                    // Gx
                    Gx_B = (2) * swap[i][j + 1].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                    Gx_G = (2) * swap[i][j + 1].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                    Gx_R = (2) * swap[i][j + 1].rgbtRed + swap[i + 1][j + 1].rgbtRed;

                    // Gy
                    Gy_B = (2) * swap[i + 1][j].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                    Gy_G = (2) * swap[i + 1][j].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                    Gy_R = (2) * swap[i + 1][j].rgbtRed + swap[i + 1][j + 1].rgbtRed;
                }
                else if (j == width - 1)
                {
                    // Gx
                    Gx_B = (-2) * swap[i][j - 1].rgbtBlue + (-1) * swap[i + 1][j - 1].rgbtBlue;

                    Gx_G = (-2) * swap[i][j - 1].rgbtGreen + (-1) * swap[i + 1][j - 1].rgbtGreen;

                    Gx_R = (-2) * swap[i][j - 1].rgbtRed + (-1) * swap[i + 1][j - 1].rgbtRed;

                    // Gy
                    Gy_B = swap[i + 1][j - 1].rgbtBlue + (2) * swap[i + 1][j].rgbtBlue;

                    Gy_G = swap[i + 1][j - 1].rgbtGreen + (2) * swap[i + 1][j].rgbtGreen;

                    Gy_R = swap[i + 1][j - 1].rgbtRed + (2) * swap[i + 1][j].rgbtRed;
                }
                else
                {
                    // Gx
                    Gx_B = (-2) * swap[i][j - 1].rgbtBlue + (2) * swap[i][j + 1].rgbtBlue
                            + (-1) * swap[i + 1][j - 1].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                    Gx_G = (-2) * swap[i][j - 1].rgbtGreen + (2) * swap[i][j + 1].rgbtGreen
                            + (-1) * swap[i + 1][j - 1].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                    Gx_R = (-2) * swap[i][j - 1].rgbtRed + (2) * swap[i][j + 1].rgbtRed
                            + (-1) * swap[i + 1][j - 1].rgbtRed + swap[i + 1][j + 1].rgbtRed;

                    // Gy
                    Gy_B = swap[i + 1][j - 1].rgbtBlue + (2) * swap[i + 1][j].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                    Gy_G = swap[i + 1][j - 1].rgbtGreen + (2) * swap[i + 1][j].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                    Gy_R = swap[i + 1][j - 1].rgbtRed + (2) * swap[i + 1][j].rgbtRed + swap[i + 1][j + 1].rgbtRed;
                }
            }

            if (i == height - 1)
            {
                // Treats corner cases
                if (j == 0)
                {
                    Gx_B = swap[i - 1][j + 1].rgbtBlue + (2) * swap[i][j + 1].rgbtBlue;

                    Gx_G = swap[i - 1][j + 1].rgbtGreen + (2) * swap[i][j + 1].rgbtGreen;

                    Gx_R = swap[i - 1][j + 1].rgbtRed + (2) * swap[i][j + 1].rgbtRed;

                    // Gy
                    Gy_B = (-2) * swap[i - 1][j].rgbtBlue + (-1) * swap[i - 1][j + 1].rgbtBlue;

                    Gy_G = (-2) * swap[i - 1][j].rgbtGreen + (-1) * swap[i - 1][j + 1].rgbtGreen;

                    Gy_R = (-2) * swap[i - 1][j].rgbtRed + (-1) * swap[i - 1][j + 1].rgbtRed;
                }

                else if (j == width - 1)
                {
                     Gx_B = (-2) * swap[i][j - 1].rgbtBlue + (-1) * swap[i - 1][j - 1].rgbtBlue;

                     Gx_G = (-2) * swap[i][j - 1].rgbtGreen + (-1) * swap[i - 1][j - 1].rgbtGreen;

                     Gx_R = (-2) * swap[i][j - 1].rgbtRed + (-1) * swap[i - 1][j - 1].rgbtRed;

                     // Gy
                     Gy_B = (-1) * swap[i - 1][j - 1].rgbtBlue + (-2) * swap[i - 1][j].rgbtBlue;

                     Gy_G = (-1) * swap[i - 1][j - 1].rgbtGreen + (-2) * swap[i - 1][j].rgbtGreen;

                     Gy_R = (-1) * swap[i - 1][j - 1].rgbtRed + (-2) * swap[i - 1][j].rgbtRed;
                }

                else
                {
                    // Gx
                    Gx_B = (-1) * swap[i - 1][j - 1].rgbtBlue + swap[i - 1][j + 1].rgbtBlue
                            + (-2) * swap[i][j - 1].rgbtBlue + (2) * swap[i][j + 1].rgbtBlue;

                    Gx_G = (-1) * swap[i - 1][j - 1].rgbtGreen + swap[i - 1][j + 1].rgbtGreen
                            + (-2) * swap[i][j - 1].rgbtGreen + (2) * swap[i][j + 1].rgbtGreen;

                    Gx_R = (-1) * swap[i - 1][j - 1].rgbtRed + swap[i - 1][j + 1].rgbtRed
                            + (-2) * swap[i][j - 1].rgbtRed + (2) * swap[i][j + 1].rgbtRed;

                    // Gy
                    Gy_B = (-1) * swap[i - 1][j - 1].rgbtBlue + (-2) * swap[i - 1][j].rgbtBlue + (-1) * swap[i - 1][j + 1].rgbtBlue;

                    Gy_G = (-1) * swap[i - 1][j - 1].rgbtGreen + (-2) * swap[i - 1][j].rgbtGreen + (-1) * swap[i - 1][j + 1].rgbtGreen;

                    Gy_R = (-1) * swap[i - 1][j - 1].rgbtRed + (-2) * swap[i - 1][j].rgbtRed + (-1) * swap[i - 1][j + 1].rgbtRed;
                }
            }

            if (j == 0 && (i != 0 && i != height - 1))
            {
                // Gx
                Gx_B = swap[i - 1][j + 1].rgbtBlue + (2) * swap[i][j + 1].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                Gx_G = swap[i - 1][j + 1].rgbtGreen + (2) * swap[i][j + 1].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                Gx_R = swap[i - 1][j + 1].rgbtRed + (2) * swap[i][j + 1].rgbtRed + swap[i + 1][j + 1].rgbtRed;

                // Gy
                Gy_B = (-2) * swap[i - 1][j].rgbtBlue + (-1) * swap[i - 1][j + 1].rgbtBlue
                       + (2) * swap[i + 1][j].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                Gy_G =(-2) * swap[i - 1][j].rgbtGreen + (-1) * swap[i - 1][j + 1].rgbtGreen
                       + (2) * swap[i + 1][j].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                Gy_R =(-2) * swap[i - 1][j].rgbtRed + (-1) * swap[i - 1][j + 1].rgbtRed
                       + (2) * swap[i + 1][j].rgbtRed + swap[i + 1][j + 1].rgbtRed;
            }

            if (j == width -1 && (i != 0 && i != height - 1))
            {
                // Gx
                Gx_B = (-1) * swap[i - 1][j - 1].rgbtBlue + (-2) * swap[i][j - 1].rgbtBlue + (-1) * swap[i + 1][j - 1].rgbtBlue;

                Gx_G = (-1) * swap[i - 1][j - 1].rgbtGreen + (-2) * swap[i][j - 1].rgbtGreen + (-1) * swap[i + 1][j - 1].rgbtGreen;

                Gx_R = (-1) * swap[i - 1][j - 1].rgbtRed + (-2) * swap[i][j - 1].rgbtRed + (-1) * swap[i + 1][j - 1].rgbtRed;

                // Gy
                Gy_B = (-1) * swap[i - 1][j - 1].rgbtBlue + (-2) * swap[i - 1][j].rgbtBlue
                        + swap[i + 1][j - 1].rgbtBlue + (2) * swap[i + 1][j].rgbtBlue;

                Gy_G = (-1) * swap[i - 1][j - 1].rgbtGreen + (-2) * swap[i - 1][j].rgbtGreen
                        + swap[i + 1][j - 1].rgbtGreen + (2) * swap[i + 1][j].rgbtGreen;

                Gy_R = (-1) * swap[i - 1][j - 1].rgbtRed + (-2) * swap[i - 1][j].rgbtRed
                        + swap[i + 1][j - 1].rgbtRed + (2) * swap[i + 1][j].rgbtRed;
            }
            }

            // For pixels NOT in edges
            else
            {
                // Gx
                Gx_B = (-1) * swap[i - 1][j - 1].rgbtBlue + swap[i - 1][j + 1].rgbtBlue
                       + (-2) * swap[i][j - 1].rgbtBlue + (2) * swap[i][j + 1].rgbtBlue
                       + (-1) * swap[i + 1][j - 1].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                Gx_G = (-1) * swap[i - 1][j - 1].rgbtGreen + swap[i - 1][j + 1].rgbtGreen
                       + (-2) * swap[i][j - 1].rgbtGreen + (2) * swap[i][j + 1].rgbtGreen
                       + (-1) * swap[i + 1][j - 1].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                Gx_R = (-1) * swap[i - 1][j - 1].rgbtRed + swap[i - 1][j + 1].rgbtRed
                       + (-2) * swap[i][j - 1].rgbtRed + (2) * swap[i][j + 1].rgbtRed
                       + (-1) * swap[i + 1][j - 1].rgbtRed + swap[i + 1][j + 1].rgbtRed;

                // Gy
                Gy_B = (-1) * swap[i - 1][j - 1].rgbtBlue + (-2) * swap[i - 1][j].rgbtBlue + (-1) * swap[i - 1][j + 1].rgbtBlue
                       + swap[i + 1][j - 1].rgbtBlue + (2) * swap[i + 1][j].rgbtBlue + swap[i + 1][j + 1].rgbtBlue;

                Gy_G = (-1) * swap[i - 1][j - 1].rgbtGreen + (-2) * swap[i - 1][j].rgbtGreen + (-1) * swap[i - 1][j + 1].rgbtGreen
                       + swap[i + 1][j - 1].rgbtGreen + (2) * swap[i + 1][j].rgbtGreen + swap[i + 1][j + 1].rgbtGreen;

                Gy_R = (-1) * swap[i - 1][j - 1].rgbtRed + (-2) * swap[i - 1][j].rgbtRed + (-1) * swap[i - 1][j + 1].rgbtRed
                       + swap[i + 1][j - 1].rgbtRed + (2) * swap[i + 1][j].rgbtRed + swap[i + 1][j + 1].rgbtRed;
            }

            // Combine Gy and Gy
            b = round(sqrt(pow(Gx_B, 2) + pow(Gy_B, 2)));

            g = round(sqrt(pow(Gx_G, 2) + pow(Gy_G, 2)));

            r = round(sqrt(pow(Gx_R, 2) + pow(Gy_R, 2)));


            // Capping
            if (b > 255)
            {
                b = 255;
            }

            if (g > 255)
            {
                g = 255;
            }

            if (r > 255)
            {
                r = 255;
            }

            image[i][j].rgbtBlue = b;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtRed = r;
        }
    }
    return;
}
