#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // check arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open image.\n");
        return 1;
    }
    // define buffer name a output
    BYTE buffer[512];
    char *filename = malloc(9);
    FILE *img;
    int number = 0;
    // while read
    while (fread(buffer, sizeof(buffer), 1, file))
    {
        //
        // fread(buffer, sizeof(buffer), 1, file);
        // if  header JGP
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if create img close past
            if (number != 0)
            {
                fclose(img);
            }
            // create name
            sprintf(filename, "%03i.jpg", number);
            // open new img
            img = fopen(filename, "w");
            // img exists
            // write jpg
            fwrite(buffer, sizeof(buffer), 1, img);

            number++;
        }
        // if jpg but is body write too
        else
        {
            if (img)
            {
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
    }
    free(filename);
    fclose(file);
    return 0;
}