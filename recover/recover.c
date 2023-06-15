#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Unable to open file succesfully.\n");
        return 1;
    }

    #define BLOCK_SIZE 512
    typedef uint8_t  BYTE;

    //Memory for writing name of jpeg and a counter variable
    char *nbuff = malloc(8);
    int num = 0;

    BYTE buffer[BLOCK_SIZE];

    FILE *jpeg = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous file
            if (num > 0)
            {
                fclose(jpeg);
            }

            // Prepare the name to be given
            sprintf(nbuff, "%03i.jpg", num);

            // Open the new file to write jpeg into
            jpeg = fopen(nbuff, "w");

            if (jpeg == NULL)
            {
                fclose(card);
                printf("Could not create %s\n", nbuff);
                return 1;
            }

            // Count new jpeg
            num++;
        }

        // Write current block
        if (num > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpeg);
        }
    }

fclose(card);
free(nbuff);

return 0;
}
