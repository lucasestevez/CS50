#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int new_color = round((red + green + blue) / 3);

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

            float blue = 0, green = 0, red = 0, count = 0;

            for (int aux_i = -1; aux_i < 2; aux_i++) {

                for (int aux_j = -1; aux_j < 2; aux_j++) {

                    if (i + aux_i < 0 || i + aux_i > height - 1) {

                        continue;
                    }

                    if (j + aux_j < 0 || j + aux_j > width - 1) {

                        continue;
                    }

                    blue += image[i + aux_i][j + aux_j].rgbtBlue;
                    green += image[i + aux_i][j + aux_j].rgbtGreen;
                    red += image[i + aux_i][j + aux_j].rgbtRed;
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

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int new_red = round(.393 * red + .769 * green + .189 * blue);
            int new_green = round(.349 * red + .686 * green + .168 * blue);
            int new_blue = round(.272 * red + .534 * green + .131 * blue);

            image[i][j].rgbtRed = new_red;
            image[i][j].rgbtGreen = new_green;
            image[i][j].rgbtBlue = new_blue;
        }
    }
}
