#ifndef FAT16_H
#define FAT16_H

#include <stdint.h>
#include <stdbool.h>


#define FAT_OEM_LENGTH 8
#define FAT_LABEL_LENGTH 11
#define FAT_FSTYPE_LENGTH 8
#define FAT_BOOTCODE_LENGTH 448
#define FAT_FILENAME_LENGTH 11

// This is the maximum filename length with long file names
#define FAT_MAX_FILENAME_LENGTH 255

#define FAT_ATTR_READONLY   0x01
#define FAT_ATTR_HIDDEN     0x02
#define FAT_ATTR_SYSTEM     0x04
#define FAT_ATTR_VOLUMEID   0x08
#define FAT_ATTR_DIRECTORY  0x10
#define FAT_ATTR_ARCHIVE    0x20
#define FAT_ATTR_LFN        0x0F

#define FAT_LFN_GET_ORDER(x) ((x) & 0x0f)

#define FAT16_GET_HOURS(x) ((x) >> 11)
#define FAT16_GET_MINUTES(x) ((x) >> 5 & 0x7f)
#define FAT16_GET_SECONDS(x) (2 * ((x) & 0x1f))

#define FAT16_GET_YEAR(x) (1980 + ((x) >> 9))
#define FAT16_GET_MONTH(x) ((x) >> 5 & 0x0f)
#define FAT16_GET_DAY(x) ((x) & 0x1f)

/*
    These are data structures saved on disk
*/

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

struct FAT16DirEntry {
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
} __attribute__((packed));

typedef struct FAT16DirEntry FAT16DirEntry;

struct FAT16LongFileName {
    uint8_t order;
    unsigned char filename1[10];
    uint8_t attribute;
    uint8_t entryType;
    uint8_t checksum;
    unsigned char filename2[12];
    uint16_t zero;
    unsigned char filename3[4];
} __attribute__((packed));

typedef struct FAT16LongFileName FAT16LongFileName;

typedef uint16_t FATEntry;

/*
    These are NOT actual structures on disk
*/

struct FAT16FileSystem {
    uint16_t *fat;
    char *ramdisk;
    struct FAT16BootRecord bootRecord;
    struct FAT16ExtendedBootRecord eBootRecord;
    int tableOffset;
    int rootDirOffset;
    int dataOffset;
} __attribute__((packed));

typedef struct FAT16FileSystem FAT16FileSystem;

/*
    Represents the status of a file that is being read
*/
struct FAT16FileHandle {
    // The cluster at which the file content starts. Used for rewinding
    int initialCluster;
    // The position in the file
    int position;
    // The current cluster where position is in
    int cluster;
    // The size(bytes) of the file. Used to avoid reading outside the file data
    int filesize;
};

typedef struct FAT16FileHandle FAT16FileHandle;

void fat16_set_diskinterface(struct DiskInterface *diskinterface);
int fat16_read_cluster(int cluster, char *buffer);

int fat16_open_support(const char *path, int length, FAT16DirEntry *entry);

int fat16_read_filesystem(struct DiskInterface *diskinterface);
int fat16_ls(int *offset, FAT16DirEntry *out, char *filename);
int fat16_open(const char *path, FAT16DirEntry *entry);
int fat16_fopen(const char *path, char mode, struct FAT16FileHandle *handle);
int fat16_fread(struct FAT16FileHandle *handle, int count, char *buffer);

int fat16_is_entry_end(FAT16DirEntry *entry);
int fat16_is_entry_unused(FAT16DirEntry *entry);
int fat16_get_next_cluster(int cluster);
int fat16_cluster_to_offset(int cluster);

int fat16_get_formatted_filename(unsigned char *, unsigned char *);

#endif