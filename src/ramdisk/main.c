#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "fat16.h"
#include "fat16util.h"


void print_boot_record(struct FAT16BootRecord *boot_record) {
    printf("OEM: "); print_s((char *) boot_record->OEM, 8);
    printf("\nBytes per sector: %d\n", boot_record->bytesPerSector);
    printf("Sectors per cluster: %d\n", boot_record->sectorsPerCluster);
    printf("Reserved sectors: %d\n", boot_record->reservedSectors);
    printf("File Allocation Tables: %d\n", boot_record->fats);
    printf("Directory entries: %d\n", boot_record->maxRootEntries);
    printf("Volume sectors: %d\n", boot_record->volumeSectors);
    printf("Media descriptor type: %d\n", boot_record->mediaDescriptorType);
    printf("Sectors per FAT: %d\n", boot_record->sectorsPerFat);
    printf("Sectors per track: %d\n", boot_record->sectorsPerTrack);
    printf("Heads per storage unit: %d\n", boot_record->headsPerStorage);
    printf("Hidden sectors: %d\n", boot_record->hiddenSectors);
    printf("Large sector count: %d\n", boot_record->largeSectorCount);
}

void print_extended_boot_record(struct FAT16ExtendedBootRecord *record) {
    printf("--- Extended Boot Record ---\n");
    printf("Drive number: %d\n", record->drive);
    printf("Signature: %x\n", record->signature);
    printf("Volume Serial ID: %x\n", record->volumeId);
    printf("Label string: "); print_s(record->label, FAT_LABEL_LENGTH);
    printf("\nSystem identifier: "); print_s(record->fstype, FAT_FSTYPE_LENGTH);
    printf("\n");
}

void list_dir(int dir_offset)
{
    FAT16DirEntry e;
    while (fat16_ls(&dir_offset, &e)) {
        printf("Filename: "); print_s(e.filename, 11);
        printf("\nSize: %d\n", e.filesize);
        printf("Attributes: %x\n", e.attributes);
        printf("Cluster start: %d\n", e.lowStartingClusterNumber);
    }
}

extern char *ramdisk;
extern FAT16FileSystem fs;

int main(int argc, char **args) 
{
    FILE *fd;
    if (argc > 1) {
        fd = fopen(args[1], "rb");
    } else {
        fd = fopen("sample.fat16", "rb");
    }
    fseek(fd, 0L, SEEK_END);
    uint32_t size = ftell(fd);
    rewind(fd);
    ramdisk = (char *) malloc(size);
    assert(fread(ramdisk, 1, size, fd) == size);
    fclose(fd);

    fat16_read_filesystem(ramdisk, &fs);

    print_boot_record(&fs.bootRecord);
    print_extended_boot_record(&fs.eBootRecord);
    
    printf("--- Content of / ---\n");
    list_dir(fs.rootDirOffset);
    printf("---\n");

    FAT16DirEntry e;
    int offset = fs.rootDirOffset;
    while (fat16_ls(&offset, &e) && strncmp(e.filename, "L33T", 4)) {}
    
    struct FAT16FileHandle handle;
    handle.cluster = e.lowStartingClusterNumber;
    handle.position = 0;
    handle.filesize = 14;
    handle.initialCluster = e.lowStartingClusterNumber;
    char buffer[1000];
    fat16_fread(&handle, 10, buffer);
    printf("Ho letto 10 byte: "); print_s(buffer, 10);
    fat16_fread(&handle, 4, buffer);
    print_s(buffer, 4);
    
    return 0;
}