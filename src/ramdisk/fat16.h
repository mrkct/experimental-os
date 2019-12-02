#ifndef FAT16_H
#define FAT16_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define FAT_OEM_LENGTH 8
#define FAT_LABEL_LENGTH 11
#define FAT_FSTYPE_LENGTH 8
#define FAT_BOOTCODE_LENGTH 448
#define FAT_FILENAME_LENGTH 11

struct FAT16BootRecord {
    unsigned char jmp[3];
    unsigned char OEM[FAT_OEM_LENGTH];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t fats;
    uint16_t maxRootEntries;
    uint16_t volumeSectors;
    uint8_t mediaDescriptorType;
    uint16_t sectorsPerFat;
    uint16_t sectorsPerTrack;
    uint16_t headsPerStorage;
    uint32_t hiddenSectors;
    uint32_t largeSectorCount;
} __attribute__((packed));

struct FAT16ExtendedBootRecord {
    uint8_t drive;
    uint8_t reserved;
    uint8_t signature;
    uint32_t volumeId;
    unsigned char label[FAT_LABEL_LENGTH];
    unsigned char fstype[FAT_FSTYPE_LENGTH];
    unsigned char bootcode[FAT_BOOTCODE_LENGTH];
    uint16_t bootSignature; 
} __attribute__((packed));

struct FAT16StandardDirectory {
    unsigned char filename[FAT_FILENAME_LENGTH];
    uint8_t attributes;
    uint8_t reserved;
    uint8_t creationTimeSec;
    uint16_t creationTime;
    uint16_t creationDate;
    uint16_t lastAccessDate;
    uint16_t highStartingClusterNumber;
    uint16_t lastModTime;
    uint16_t lastModDate;
    uint16_t lowStartingClusterNumber;
    uint32_t filesize;
};

struct FAT16LongFileName {
    uint8_t order;
    unsigned char filename1[10];
    uint8_t attribute;
    uint8_t entryType;
    uint8_t checksum;
    unsigned char filename2[12];
    uint16_t zero;
    unsigned char filename3[4];
};

typedef uint16_t FATEntry;

struct FAT16FileSystem {
    char *ramdisk;
    struct FAT16BootRecord bootRecord;
    struct FAT16ExtendedBootRecord eBootRecord;
    int tableOffset;
    int dataOffset;
} __attribute__((packed));

typedef struct FAT16FileSystem FAT16FileSystem;


int fat16_read_filesystem(char *start, FAT16FileSystem *out);

#endif