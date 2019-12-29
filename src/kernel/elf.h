#ifndef ELF_H
#define ELF_H

#include <stdint.h>
#include <stddef.h>

#define ELF_MAGIC 0x464C457FU

#define ELF_PROG_LOAD 1

struct ELFHeader {
    uint32_t magic;
    uint8_t arch;
    uint8_t endianness;
    uint8_t headerVersion;
    uint8_t abi;
    uint8_t unused[8];
    uint16_t type;
    uint16_t isa;
    uint32_t version;
    uint32_t entry;
    uint32_t progHeader;
    uint32_t sectHeader;
    uint32_t flags;
    uint16_t headerSize;
    uint16_t progEntrySize;
    uint16_t progEntries;
    uint16_t sectEntrySize;
    uint16_t sectEntries;
    uint16_t idkWhatThisIs;
} __attribute__((packed));

typedef struct ELFHeader ELFHeader;

struct ELFProgHeader {
    uint32_t type;
    uint32_t dataOffset;
    uint32_t vAddr;
    uint32_t unused;
    uint32_t fileSize;
    uint32_t memSize;
    uint32_t flags;
    uint32_t alignment;
} __attribute__((packed));

typedef struct ELFProgHeader ELFProgHeader;

#endif