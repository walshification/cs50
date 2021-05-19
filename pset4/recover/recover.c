/**
 * Problem Set 4: Recover
 * ----------------------
 * Implement a program called recover that recovers JPEGs from a
 * forensic image.
 *
 * It should accept exactly one argument, the name of a forensic image.
 * Otherwise, remind the user of correct usage and return 1.
 *
 * If the image can't be opened, inform the user return 1.
 *
 * Generate files named ###.jpg, where ### is a three-digit decimal
 * number, starting with 000 for the first image and counting up.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // If not provided the correct argument, inform the user of usage.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *image = fopen(argv[1], "r");
    // If the image cannot be opened, inform the user.
    if (image == NULL)
    {
        printf("Image cannot be opened.\n");
        return 1;
    }

    int file_number = 0;
    char file_name[8];
    sprintf(file_name, "%03i.jpg", file_number);
    FILE *recovered_image = fopen(file_name, "w");
    if (recovered_image == NULL)
    {
        printf("Couldn't open file to write recovered image.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];

    // Fast-forward to the first JPG.
    while (!(buffer[0] == 0xff &&
             buffer[1] == 0xd8 &&
             buffer[2] == 0xff &&
             (buffer[3] & 0xf0) == 0xe0))
    {
        fread(buffer, sizeof(BYTE), BLOCK_SIZE, image);
    }

    // Begin writing the first one so we can start our recovery loop.
    fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, recovered_image);

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, image))
    {
        // If we reach a new file ...
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Finish the one in progress.
            fclose(recovered_image);
            file_number++;

            // Start the next.
            sprintf(file_name, "%03i.jpg", file_number);
            recovered_image = fopen(file_name, "w");
            if (recovered_image == NULL)
            {
                printf("Couldn't open file to write recovered image.\n");
                return 1;
            }

            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, recovered_image);
        }
        else
        {
            // Continue writing JPG.
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, recovered_image);
        }
    }
}
