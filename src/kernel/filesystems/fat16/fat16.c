#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <kernel/devices/vdisk.h>
#include <kernel/lib/kassert.h>
#include <klibc/string.h>
#include <klibc/ctype.h>
#include <kernel/filesystems/vfs.h>
#include <kernel/filesystems/fat16/fat16.h>


static FAT16FileSystem fs;
static struct DiskInterface *disk;
static int CLUSTER_SIZE;

void fat16_set_diskinterface(struct DiskInterface *diskinterface)
{
    disk = diskinterface;
}

int fat16_is_entry_end(FAT16DirEntry *entry) {
    return *((char *) entry) == 0x00;
}

int fat16_is_entry_unused(FAT16DirEntry *entry) {
    return *((unsigned char *) entry) == 0xe5;
}

int fat16_is_entry_lfn(FAT16DirEntry *entry) {
    return entry->attributes == FAT_ATTR_LFN;
}

/*
    Returns the offset in bytes in the data region of the disk of the given 
    cluster
*/
int fat16_cluster_to_offset(int cluster) {
    return (cluster-2) * CLUSTER_SIZE;
}

int fat16_get_formatted_filename(unsigned char *fatfilename, unsigned char *filename)
{
	int filename_len = 0;
	int name_len = FAT_FILENAME_LENGTH - 4;
	while (name_len >= 0 && fatfilename[name_len] == ' ')
		name_len--;
	name_len++;
	filename_len += name_len;
	memcpy(filename, fatfilename, name_len);
	
	if (fatfilename[FAT_FILENAME_LENGTH-3] != ' ') {
		filename[filename_len++] = '.';
		for (int i = FAT_FILENAME_LENGTH - 3; i < FAT_FILENAME_LENGTH; i++) {
			if (fatfilename[i] != ' ') {
				filename[filename_len++] = fatfilename[i];
			}
		}
	}
	filename[filename_len++] = '\0';
	
	return filename_len;
}

/*
    Reads the given cluster from disk and stores it in buffer. 'buffer' is 
    expected to be at least CLUSTER_SIZE bytes long
    Returns the result of read_bytes
*/
int fat16_read_cluster(int cluster, char *buffer)
{
    int offset = fat16_cluster_to_offset(cluster);
    return disk->read_bytes(fs.dataOffset + offset, CLUSTER_SIZE, buffer);
}

int fat16_get_next_cluster(int cluster) {
    return fs.fat[cluster];
}

int fat16_strcmp(unsigned char *a, unsigned char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0' && toupper(a[i]) == toupper(b[i])) {
        i++;
    }
    
    return toupper(a[i]) - toupper(b[i]);
}

/*
    Initializes a FAT16FileSystem struct from a disk.
    Returns 0 on success, -1 if the disk is not a valid FAT16 disk.
*/
int fat16_read_filesystem(struct DiskInterface *diskinterface)
{
    size_t br_size = sizeof(struct FAT16BootRecord);
    size_t ebr_size = sizeof(struct FAT16ExtendedBootRecord);
    disk = diskinterface;
    disk->read_bytes(0, br_size, (char *) &fs.bootRecord);
    disk->read_bytes(br_size, ebr_size, (char *) &fs.eBootRecord);
    
    int signature = fs.eBootRecord.signature;
    if (signature != 0x29 && signature != 0x28) {
        return -1;
    }

    // Checks for the file system
    int bytesPerSector = fs.bootRecord.bytesPerSector;
    if (bytesPerSector != 512 && bytesPerSector != 1024 && bytesPerSector != 2048 && bytesPerSector != 4096) {
        return -1;
    }
    // TODO: Implement the other checks
    // see: http://read.pudn.com/downloads77/ebook/294884/FAT32%20Spec%20%28SDA%20Contribution%29.pdf

    int sector_size = fs.bootRecord.bytesPerSector;
    struct FAT16BootRecord *br = &fs.bootRecord;
    fs.tableOffset = br->reservedSectors * sector_size;
    fs.rootDirOffset = fs.tableOffset;
    fs.rootDirOffset += (sector_size * br->sectorsPerFat * br->fats);
    fs.dataOffset = fs.rootDirOffset + fs.bootRecord.maxRootEntries * sizeof(FAT16DirEntry);

    CLUSTER_SIZE = fs.bootRecord.sectorsPerCluster * fs.bootRecord.bytesPerSector;

    return 0;
}

/*
    Returns the next entry in a directory, given an offset in the disk.
    @param offset: The offset in the disk, in bytes, where a list of folder 
    entries starts. This will be changed to point to the next entry in the 
    folder
    @param out: A File struct where the read entry will be put
    @param filename: A string where the filename will be written. This is 
    expected to be at least 255 characters long and it will be zero terminated

    Returns 1 when there might be more entries in the folder, 0 when there are 
    no more. The out param will contain a new entry when the function returns 1

    An example for reading an entire folder can be

    File file;
    char filename[255];
    int off = ROOT_DIR_OFFSET;
    while (fat16_ls(&off, &file, filename)) {
        // Do something with file
    }
*/
int fat16_ls(int *offset, FAT16DirEntry *out, char *filename)
{
    FAT16DirEntry entry = (FAT16DirEntry) {0};

    kassert(0 == disk->read_bytes(*offset, sizeof(FAT16DirEntry), (char *) &entry));
    bool used_lfn = false;
    while ( (fat16_is_entry_unused(&entry) && !fat16_is_entry_end(&entry)) || fat16_is_entry_lfn(&entry)) {
        if (filename != NULL && fat16_is_entry_lfn(&entry)) {
            used_lfn = true;
            /*
                In a long file name entry the actual name is split in 3 parts 
                in the structure. Each part is made of 2 bytes character but 
                only the first character is used. The string is 0 terminated 
                and the rest is filled with 0xff
            */
            FAT16LongFileName *lfn = (FAT16LongFileName *) &entry;
            int filename_offset = (10 + 12 + 4)/2 * (FAT_LFN_GET_ORDER(lfn->order)-1);
            for (int i = 0; i < 10; i += 2) {
                filename[filename_offset++] = lfn->filename1[i];
            }
            for (int i = 0; i < 12; i += 2) {
                filename[filename_offset++] = lfn->filename2[i];
            }
            for (int i = 0; i < 4; i += 2) {
                filename[filename_offset++] = lfn->filename3[i];
            }
        }
        *offset += sizeof(FAT16DirEntry);
        kassert(0 == disk->read_bytes(*offset, sizeof(FAT16DirEntry), (char *) &entry));
    }

    if (fat16_is_entry_end(&entry)) {
        return 0;
    } else {
        *offset += sizeof(FAT16DirEntry);
        *out = entry;
        if (!used_lfn) {
            fat16_get_formatted_filename(entry.filename, filename);
        }

        return 1;
    }
}

/*
    Finds the entry with the given name and returns it in the 'out' argument. 
    @param name: The name of the entry to search for. Note that the name of 
    the entries are not case-sensitive ("Hello", "HELLO", "hElLo" are the same)
    @param diroffset: The offset in the disk of the directory in which to find 
    the entry
    @param out: Where, if an entry is found, the entry will be stored
    Returns the disk offset of the entry if found (>0), -1 otherwise
*/
int fat16_findentry(unsigned char *name, int diroffset) {
    FAT16DirEntry entry;
    char filename[FAT_MAX_FILENAME_LENGTH + 1];
    while(fat16_ls(&diroffset, &entry, filename)) {
        if (fat16_strcmp(filename, name) == 0) {
            return diroffset - sizeof(FAT16DirEntry);
        }
    }

    return -1;
}

/*
    See `fat16_open`, this is the implementation of that function.
    @param path: Absolute path, starting with '/', to the entry
    @param length: Length of the path string
    @returns disk offset on success, -1 if it wasnt able to follow the 
    path(missing directory, for example)
*/
int fat16_open_support(const char *path, int length, FAT16DirEntry *entry) {
    if (length <= 1){
        return fs.rootDirOffset;
    }

    int last_slash = length - 1;
    while (last_slash > 0 && path[last_slash] != '/') {
        last_slash--;
    }

    int diroff = fat16_open_support(path, last_slash, entry);
    // Directory was not found
    if (diroff < 0)     return -1;

    // Extracts the path of the parent folder
    unsigned char dirname[FAT_MAX_FILENAME_LENGTH];
    int dirname_length = length - (last_slash+1);
    memcpy(dirname, &path[last_slash+1], dirname_length);
    dirname[dirname_length] = '\0';

    int entry_off = fat16_findentry(dirname, diroff);
    if (entry_off < 0) {
        return -1;
    }
    FAT16DirEntry e;
    kassert(0 == disk->read_bytes(entry_off, sizeof(FAT16DirEntry), (char *) &e));
    if (entry != NULL) { *entry = e; }

    return fs.dataOffset + fat16_cluster_to_offset(e.lowStartingClusterNumber);
}

/*
    Returns the disk offset of the content of the entry in an absolute path. 
    This function does no checks if the path is syntactically correct, you 
    need to respect the format. In particular: 
    - The path needs to start with '/'
    - It should NOT end with '/'
    This also returns the entry in the parent directory if the 'entry' 
    argument is not NULL. This will return nothing if you request the root, as 
    it doesn't have a parent.
    
    NOTE: This is the CONTENT OF THE ENTRY, not the entry itself. If you pass a
    path to a directory you will get the offset of the first entry in the 
    folder. If you pass a path to a file you will get the offset of the first 
    cluster of the file. If you want the entry in the folder see the 'entry' 
    argument.

    Returns the offset of the content of entry in the disk or -1 if the path couldn't be 
    followed.
*/
int fat16_open(const char *path, FAT16DirEntry *entry) {
    return fat16_open_support(path, strlen(path), entry);
}

/*
    Opens a file given an absolute pathname. 
    TODO: This only works for reading, implement write & append
    Returns 0 on success, -1 if the file could not be opened
*/
int fat16_fopen(const char *path, char mode, struct FAT16FileHandle *handle) {
    // TODO: Implement other modes
    kassert(mode == 'r');

    FAT16DirEntry entry;
    int file_off = fat16_open(path, &entry);
    if (file_off <= 0)
        return -1;

    handle->position = 0;
    handle->cluster = entry.lowStartingClusterNumber;
    handle->initialCluster = entry.lowStartingClusterNumber;
    handle->filesize = entry.filesize;

    return 0;
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
    char cluster[CLUSTER_SIZE];
    kassert(0 == fat16_read_cluster(handle->cluster, cluster));

    while (copied < count && position < handle->filesize) {
        buffer[i++] = cluster[position++ % CLUSTER_SIZE];
        copied++;
        if (position % CLUSTER_SIZE == 0) {
            cluster_index = fat16_get_next_cluster(cluster_index);
            kassert(0 == fat16_read_cluster(cluster_index, cluster));
        }
    }
    handle->position = position;
    handle->cluster = cluster_index;

    return copied;
}