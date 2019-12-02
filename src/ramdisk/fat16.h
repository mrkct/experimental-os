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
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t fats;
    uint16_t max_root_entries;
    uint16_t volume_sectors;
    uint8_t media_descriptor_type;
    uint16_t sectors_per_fat;
    uint16_t sectors_per_track;
    uint16_t heads_per_storage;
    uint32_t hidden_sectors;
    uint32_t large_sector_count;
} __attribute__((packed));

struct FAT16ExtendedBootRecord {
    uint8_t drive;
    uint8_t reserved;
    uint8_t signature;
    uint32_t volume_id;
    unsigned char label[FAT_LABEL_LENGTH];
    unsigned char fstype[FAT_FSTYPE_LENGTH];
    unsigned char bootcode[FAT_BOOTCODE_LENGTH];
    uint16_t boot_signature; 
} __attribute__((packed));

struct FAT16StandardDirectory {
    unsigned char filename[FAT_FILENAME_LENGTH];
    uint8_t attributes;
    uint8_t reserved;
    uint8_t creation_time_sec;
    uint16_t creation_time;
    uint16_t creation_date;
    uint16_t last_access_date;
    uint16_t high_start_cluster_number;
    uint16_t last_mod_time;
    uint16_t last_mod_date;
    uint16_t low_start_cluster_number;
    uint32_t filesize;
};

struct FAT16LongFileName {
    uint8_t order;
    unsigned char filename1[10];
    uint8_t attribute;
    uint8_t entry_type;
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