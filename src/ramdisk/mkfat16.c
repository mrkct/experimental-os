#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "fat16.h"

char *ramdisk;

void print_s(char*, int);

void print_s(char *s, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%c", s[i]);
    }
}

int fat16_is_entry_end(FAT16DirEntry *entry) {
    return *((char *) entry) == 0x00;
}

int fat16_is_entry_unused(FAT16DirEntry *entry) {
    return *((char *) entry) == 0xe5;
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

int fat16_listdir(FAT16FileSystem *fs, FAT16DirEntry *folder, FAT16DirEntry **out)
{
    int allocated = 20;
    int size = 0;
    *out = malloc(allocated * sizeof(FAT16DirEntry));
    
    FAT16DirEntry *entry = (FAT16DirEntry *) (ramdisk + fs->rootDirOffset);
    while ( !fat16_is_entry_end(entry) ) {
        if ( fat16_is_entry_unused(entry) ) {
            entry++;
            continue;
        } else if (size == allocated) {
            allocated *= 2;
            *out = realloc(*out, allocated * sizeof(FAT16DirEntry));
        }
        (*out)[size++] = *entry;
        entry++;
    }

    return size;
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
    
    FAT16DirEntry *content;
    int content_size = fat16_listdir(&fs, NULL, &content);
    printf("--- There are %d entries in root ---\n", content_size);
    for (int i = 0; i < content_size; i++) {
        printf("Filename: "); print_s(content[i].filename, 11);
        printf("\nFilesize: %d\n\n", content[i].filesize);
    }
}