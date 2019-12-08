#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "fat16.h"
#include "fat16util.h"

char *ramdisk;

FAT16FileSystem fs;
int CLUSTER_SIZE;

int fat16_is_entry_end(FAT16DirEntry *entry) {
    return *((char *) entry) == 0x00;
}

int fat16_is_entry_unused(FAT16DirEntry *entry) {
    return *((char *) entry) == 0xe5;
}

int fat16_cluster_to_offset(int cluster) {
    return cluster * CLUSTER_SIZE;
}

char *fat16_find_cluster(int cluster) {
    return (char *) (ramdisk + fs.dataOffset + CLUSTER_SIZE * (cluster - 2));
}

int fat16_get_next_cluster(int cluster) {
    uint16_t *fat = (uint16_t *) (ramdisk + fs.tableOffset);
    return fat[cluster];
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
    out->dataOffset = out->rootDirOffset + out->bootRecord.maxRootEntries * sizeof(FAT16DirEntry);

    CLUSTER_SIZE = out->bootRecord.sectorsPerCluster * out->bootRecord.bytesPerSector;

    return 0;
}

/*
    Returns the next entry in a directory, given an offset in the disk.
    @param offset: The offset in the disk, in bytes, where a list of folder 
    entries starts. This will be changed to point to the next entry in the 
    folder
    @param out: A FAT16DirEntry struct where the read entry will be put

    Returns 1 when there might be more entries in the folder, 0 when there are 
    no more. The out param will contain a new entry when the function returns 1

    An example for reading an entire folder can be

    FAT16DirEntry current_entry;
    int off = ROOT_DIR_OFFSET;
    while (fat16_ls(&off, &current_entry)) {
        // Do something with current_entry
    }
*/
int fat16_ls(int *offset, FAT16DirEntry *out)
{
    FAT16DirEntry *entry = (FAT16DirEntry *) (ramdisk + *offset);
    while (fat16_is_entry_unused(entry) && !fat16_is_entry_end(entry)) {
        *offset += sizeof(FAT16DirEntry);
        entry++;
    }

    if (fat16_is_entry_end(entry)) {
        return 0;
    } else {
        *offset += sizeof(FAT16DirEntry);
        *out = *entry;
        return 1;
    }
}

/*
    Finds the entry with the given name and returns it in the 'out' argument. 
    @param name: The name of the entry to search for. Only the first 8 
    characters will be used for the comparison, also they need to be upper case
    TODO: Change these limitations
    @param diroffset: The offset in the disk of the directory in which to find 
    the entry
    @param out: Where, if an entry is found, the entry will be stored
    Returns 0 if an entry with the given name was found, -1 otherwise.
*/
int fat16_findentry(const char *name, int diroffset, FAT16DirEntry *out) {
    FAT16DirEntry entry;
    while(fat16_ls(&diroffset, &entry)) {
        if (strncmp(entry.filename, name, 8) == 0) {
            *out = entry;
            return 0;
        }
    }

    return -1;
}

/*
    Reads up to 'count' bytes into the array 'buffer' from the file 'handle'. 
    The file position is advanced up to 'count' bytes forward.
    Returns the number of read bytes, this can be lower than requested.
*/
int fat16_fread(struct FAT16FileHandle *handle, int count, char *buffer) {
    int i = 0;
    int copied = 0;
    int position = handle->position;
    
    int cluster_index = handle->cluster;
    char *cluster = fat16_find_cluster(handle->cluster);
    
    while (copied < count && position < handle->filesize) {
        buffer[i++] = cluster[position++ % CLUSTER_SIZE];
        copied++;
        if (position % CLUSTER_SIZE == 0) {
            cluster_index = fat16_get_next_cluster(cluster_index);
            cluster = fat16_find_cluster(cluster_index);
        }
    }
    handle->position = position;
    handle->cluster = cluster_index;

    return copied;
}