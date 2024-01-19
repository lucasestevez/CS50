#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int FILE_SIZE = 512;

void process_file(FILE *file);

int main(int argc, char *argv[]) {

    if (argc != 2) {

        printf("Usage: ./recover FILE\n");
        return  1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {

        printf("Could not open file.\n");
        return 1;
    }

    process_file(file);

    fclose(file);

}

void process_file(FILE *file) {

    int jpeg_number = 0;
    FILE *jpeg_file;

    while (true) {

        uint8_t buffer[FILE_SIZE];
        int read_bytes = fread(buffer, FILE_SIZE, 1, file);

        if (read_bytes != 1) {

            break;

        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef)) {

            if (jpeg_file > 0) {

                fclose(jpeg_file);

            }
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_number);
            jpeg_number++;

            jpeg_file = fopen(filename, "w");

        }

        if (jpeg_number > 0) {

            fwrite(buffer, FILE_SIZE, 1, jpeg_file);

        }
    }

     if (jpeg_file > 0) {

        fclose(jpeg_file);
     }
}
