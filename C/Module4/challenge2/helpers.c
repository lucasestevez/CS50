#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            int new_color = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = new_color;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width / 2; j++) {

            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;

        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            float red = 0, green = 0, blue = 0, count = 0;

             for (int aux_i = -1; aux_i < 2; aux_i++) {

                for (int aux_j = -1; aux_j < 2; aux_j++) {

                    if (i + aux_i < 0 || i + aux_i > height - 1) {

                        continue;
                    }

                    if (j + aux_j < 0 || j + aux_j > width - 1) {

                        continue;
                    }

                    red += image[i + aux_i][j + aux_j].rgbtRed;
                    green += image[i + aux_i][j + aux_j].rgbtGreen;
                    blue += image[i + aux_i][j + aux_j].rgbtBlue;
                    count++;
                }
            }

            copy[i][j].rgbtBlue = round(blue / count);
            copy[i][j].rgbtGreen = round(green / count);
            copy[i][j].rgbtRed = round(red / count);
        }
    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {

    RGBTRIPLE copy[height][width];

    int Gx[3][3] = {{-1,0,1},{-2,0-2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            float red_gx = 0, green_gx = 0, blue_gx = 0, red_gy = 0, green_gy = 0, blue_gy = 0;

             for (int aux_i = -1; aux_i < 2; aux_i++) {

                for (int aux_j = -1; aux_j < 2; aux_j++) {

                    if (i + aux_i < 0 || i + aux_i > height - 1) {

                        continue;
                    }

                    if (j + aux_j < 0 || j + aux_j > width - 1) {

                        continue;
                    }

                    red_gx += image[i + aux_i][j + aux_j].rgbtRed * Gx[aux_i + 1][aux_j + 1];
                    red_gy += image[i + aux_i][j + aux_j].rgbtRed * Gy[aux_i + 1][aux_j + 1];
                    green_gx += image[i + aux_i][j + aux_j].rgbtGreen * Gx[aux_i + 1][aux_j + 1];
                    green_gy += image[i + aux_i][j + aux_j].rgbtGreen * Gy[aux_i + 1][aux_j + 1];
                    blue_gx += image[i + aux_i][j + aux_j].rgbtBlue * Gx[aux_i + 1][aux_j + 1];
                    blue_gy += image[i + aux_i][j + aux_j].rgbtBlue * Gy[aux_i + 1][aux_j + 1];
                }
            }

            copy[i][j].rgbtRed = round(sqrt(pow(red_gx, 2) + pow(red_gy, 2)));
            copy[i][j].rgbtGreen = round(sqrt(pow(green_gx, 2) + pow(green_gy, 2)));
            copy[i][j].rgbtBlue = round(sqrt(pow(blue_gx, 2) + pow(blue_gy, 2)));
        }
    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }

}
