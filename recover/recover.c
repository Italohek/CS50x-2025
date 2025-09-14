#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE 512
#define true 1

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover CARD\n");
        return 1;
    }

    // open the card file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open the file\n");
        return 2;
    }

    // create a buffer for a block of data
    BYTE buffer[512];
    FILE *output = NULL; // pointing to NULL to simbolize
                         // that is safe and is not pointing anywhere

    int counter = 0;
    char name[8];

    while (true)
    {
        size_t bytesRead = fread(buffer, 1, SIZE, input);
        // check if it is the final of the card
        if (bytesRead == 0 && feof(input))
            break;

        bool header = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                      (buffer[3] & 0xf0) == 0xe0;

        if (header)
        {
            // close the previous file if it exists
            if (output != NULL)
            {
                fclose(output);
                counter++;
            }

            // open a new JPEG file
            sprintf(name, "%03i.jpg", counter);
            output = fopen(name, "w");
        }

        // if a JPEG file is open, write the block
        if (output != NULL)
        {
            fwrite(buffer, 1, bytesRead, output);
        }
        // close files
    }
    fclose(output);
    fclose(input);
    return 0;
}
