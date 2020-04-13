#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "File cannot be read");
        return 1;
    }

    int filecount = 0;
    BYTE buffer[512];
    char filename[8] = "";

    FILE *img = NULL;

    // Loop until break called
    while (1)
    {
        fread(buffer, 512, 1, file);

        // If end of file, break
        if (feof(file))
        {
            break;
        }

        // If first four bytes of of block indicates start of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not already writing to new jpeg
            if (img == NULL)
            {
                // Create new jpeg
                sprintf(filename, "%03i.jpg", filecount);
                img = fopen(filename, "w");

                // Write to new jpeg
                fwrite(buffer, 512, 1, img);
            }
            // Else if already writing to jpeg
            else
            {
                // Close current jpeg
                fclose(img);

                // Create new jpeg
                filecount++;
                sprintf(filename, "%03i.jpg", filecount);
                img = fopen(filename, "w");

                // Write to new jpeg
                fwrite(buffer, 512, 1, img);

            }
        }
        // Else if block is not start of new jpeg
        else
        {
            // If already writing to file
            if (img != NULL)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }

    // Close all streams
    fclose(img);
    fclose(file);
}
