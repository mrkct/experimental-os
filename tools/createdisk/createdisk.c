#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SECTOR_SIZE 512


int main(int argc, char **argv)
{
    if (argc > 1 && strcmp("-h", argv[1]) == 0) {
        printf("usage: crd <size of the disk in MB> <name of the output file>\n");
        return 0;
    }
    int disksize = 1024 * 1024; // 1MB
    char *filename = "disk.img";
    if (argc > 1)
        disksize = 1024 * 1024 * atoi(argv[1]);
    if (argc > 2)
        filename = argv[2];
    
    printf("Creating a disk of %dMB called %s\n", disksize / 1024 / 1024, filename);

    FILE *out = fopen(filename, "wb");
    char sector[SECTOR_SIZE];
    for (int i = 0; i < disksize / SECTOR_SIZE; i++) {
        memset(sector, i, SECTOR_SIZE);
        assert(SECTOR_SIZE == fwrite(sector, 1, SECTOR_SIZE, out));
    }
    fclose(out);
    printf("Written successfully\n");
    return 0;
}