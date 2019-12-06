#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "fat16.h"

int fat16_read_filesystem(char *start, FAT16FileSystem *out);

char *ramdisk;

void print_s(char*, int);

void print_s(char *s, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%c", s[i]);
    }
}

void print_boot_record(struct FAT16BootRecord *boot_record) {
    printf("OEM: "); print_s((char *) boot_record->OEM, 8);
    printf("\nBytes per sector: %d\n", boot_record->bytesPerSector);
    printf("Sectors per cluster: %d\n", boot_record->sectorsPerCluster);
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

int fat16_read_filesystem(char *disk, FAT16FileSystem *out)
{
    char *pos = disk;
    
    memcpy(&out->bootRecord, pos, sizeof(struct FAT16BootRecord));
    
    pos += sizeof(struct FAT16BootRecord);
    memcpy(&out->eBootRecord, pos, sizeof(struct FAT16ExtendedBootRecord));
    
    int signature = out->eBootRecord.signature;
    if (signature != 0x29 && signature != 0x28) {
        return -1;
    }

    int sector_size = out->bootRecord.bytesPerSector;
    struct FAT16BootRecord *br = &out->bootRecord;
    out->tableOffset = br->reservedSectors * sector_size;
    out->rootDirOffset = out->tableOffset;
    out->rootDirOffset += (sector_size * br->sectorsPerFat * br->fats);
    out->dataOffset = out->rootDirOffset + out->bootRecord.maxRootEntries * 32;

    return 0;
}

int fat16_find_entry(const char *entryname, FAT16FileSystem *fs, FAT16DirEntry *folder, FAT16DirEntry *out)
{
    printf("-- Printing content of %s --\n", entryname);
    // int children = folder->filesize / sizeof(FAT16DirEntry);
    int children = fs->bootRecord.maxRootEntries;
    printf("The folder has %d files in it: \n", children);
    // TODO: Convert cluster number into offset. This only works for root
    FAT16DirEntry *entry = (FAT16DirEntry *) ramdisk;
    int dirOffset = fs->rootDirOffset;
    for (int i = 0; i < children; i++) {
        entry = (FAT16DirEntry *) (ramdisk + dirOffset);
        if (*entry->filename == 0x00 || *entry->filename == 0xe5) {
            continue;
        }
        printf("Filename: "); print_s(entry->filename, 11);
        printf("\nSize: %d\n\n", entry->filesize);
        dirOffset += sizeof(FAT16DirEntry);
    }

    return 0;
}

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

    FAT16FileSystem fs;
    fat16_read_filesystem(ramdisk, &fs);

    print_boot_record(&fs.bootRecord);
    print_extended_boot_record(&fs.eBootRecord);
    
    // print_root_directory(&fs);
    fat16_find_entry("/", &fs, NULL, NULL);
}