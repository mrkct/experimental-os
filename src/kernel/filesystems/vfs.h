#ifndef VFS_H
#define VFS_H

#define VFS_FS_NAME_LEN 16
#define VFS_NAME_LEN 32

typedef struct DateTime {
    int year, month, day;
    int hour, minute, second;
} DateTime;

typedef struct File {
    char name[VFS_NAME_LEN+1];
    int filesize;
    void *fs_defined;
} File;

typedef struct Dir {
    char name[VFS_NAME_LEN+1];
    void *fs_defined;
} Dir;

enum DirEntryType {
    FILE,
    DIRECTORY
};

typedef struct DirEntry {
    char name[VFS_NAME_LEN+1];
    enum DirEntryType type;
    DateTime creation;
    DateTime lastUpdate;
    void *fs_defined;
} DirEntry;

typedef struct VFSInterface {
    char filesystem[VFS_FS_NAME_LEN];

    int (*fopen)(char *path, File *out);
    int (*fread)(char *buffer, int count, File *file);
    int (*fwrite)(char *buffer, int count, File *file);
    int (*fclose)(File *file);
    // int (*fseek)(File *file, int offset, int whence);
    // int (*makedir)(char *path);
    int (*listdir)(char *path, int index, Dir *out);
} VFSInterface;


typedef File *FileDesc;

/*
    Uses the argument virtual file system interface as the VFS for all the 
    operations on the disk.
    Returns 0 on success. There are no fail codes
*/
int vfs_setroot(VFSInterface *);

/*
    Opens a file as a byte stream. Path is expected to be an absolute one. 
    Supported modes are:
    - "r" : Opens the file for reading
    - "w" : UNIMPLEMENTED: Opens the file for writing. If it doesn't exists it 
            will be created. If a file with the same name already eixsts it 
            will be overwritten
    - "r+": UNIMPLEMENTED
    - "w+": UNIMPLEMENTED
           
    Returns a file descriptor, to be used for each operation to refer to
    the opened file, on success. Returns 0 on fail.
*/
FileDesc kfopen(char *path, char *mode);

/*
    Reads 'count' bytes from the passed file into 'buffer' starting from the 
    current cursor position. The buffer is expected to have enough space for 
    the read bytes. The number of read bytes can be lower than count if, for 
    example, the file ends. Each read moves the file cursor forward for the 
    number of bytes read
    Returns the number of read bytes
*/
int kfread(char *buffer, int count, FileDesc fd);

/*
    UNIMPLEMENTED
    Writes 'count' bytes from 'buffer' in the file at the current cursor 
    position in the file. 
    Returns the number of written bytes
*/
int kfwrite(char *buffer, int count, FileDesc fd);

/*
    Closes the file, freeing its resources
    Returns 0 on success
*/
int kfclose(FileDesc fd);

#endif