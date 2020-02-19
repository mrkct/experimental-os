#ifndef ATA_H
#define ATA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#define IDE_SECTOR_SIZE     512
#define IDE_READSTATUS_TIMEOUT  200

enum {
    IDE_IRQ = 14,

    IDE_PORT_BASE = 0x1F0,

    IDE_PORT_DATA = IDE_PORT_BASE + 0,
    IDE_PORT_FEAT_ERR = IDE_PORT_BASE + 1,
    IDE_PORT_SECTOR_CNT = IDE_PORT_BASE + 2,
    IDE_PORT_LBA_LOW_8 = IDE_PORT_BASE + 3,
    IDE_PORT_LBA_MID_8= IDE_PORT_BASE + 4,
    IDE_PORT_LBA_HIGH_8 = IDE_PORT_BASE + 5,
    IDE_PORT_DRIVE_HEAD = IDE_PORT_BASE + 6,
    IDE_PORT_COMMAND_STATUS = IDE_PORT_BASE + 7,

    IDE_PORT_PRIMARY_CTL = 0x3F6,
};

enum ide_status_format {
    IDE_STATUS_BUSY = (1 << 7),
    IDE_STATUS_READY = (1 << 6),
    IDE_STATUS_DRIVE_FAULT = (1 << 5),
    IDE_STATUS_DATA_REQUEST = (1 << 3),
    IDE_STATUS_DATA_CORRECT = (1 << 2),
    IDE_STATUS_ERROR = (1 << 0),

    /* This is not a real part of the status, but we report this if the status check hits the timeout */
    IDE_STATUS_TIMEOUT = (1 << 8),
};

enum ide_ctl_format {
    IDE_CTL_STOP_INT = (1 << 1),
    IDE_CTL_RESET = (1 << 2)
};

/* Lower 4 bits of the drive_head hold the extra 4-bit for LBA28 mode */
enum ide_drive_head_format {
    IDE_DH_SHOULD_BE_SET = (1 << 5) | (1 << 7),
    IDE_DH_LBA = (1 << 6),

    /* Set this bit to use the slave IDE drive instead of master */
    IDE_DH_SLAVE = (1 << 4),
};

enum ide_command_format {
    IDE_COMMAND_PIO_LBA28_READ = 0x20,
    IDE_COMMAND_PIO_LBA28_WRITE = 0x30,

    IDE_COMMAND_DMA_LBA28_READ = 0xC8,
    IDE_COMMAND_DMA_LBA28_WRITE = 0xCA,

    IDE_COMMAND_CACHE_FLUSH = 0xE7,
    IDE_COMMAND_IDENTIFY = 0xEC,
};

struct ide_identify_format {
    uint16_t config; /* lots of obsolete bit flags */
    uint16_t cyls;/* "physical" cyls */
    uint16_t reserved2; /* reserved (word 2) */
    uint16_t heads;  /* "physical" heads */
    uint16_t track_bytes; /* unformatted bytes per track */
    uint16_t sector_bytes; /* unformatted bytes per sector */
    uint16_t sectors; /* "physical" sectors per track */
    uint16_t vendor0; /* vendor unique */
    uint16_t vendor1; /* vendor unique */
    uint16_t vendor2; /* vendor unique */
    uint8_t serial_no[20]; /* 0 = not_specified */
    uint16_t buf_type;
    uint16_t buf_size; /* 512 byte increments; 0 = not_specified */
    uint16_t ecc_bytes; /* for r/w long cmds; 0 = not_specified */
    uint8_t  fw_rev[8]; /* 0 = not_specified */
    uint8_t  model[40]; /* 0 = not_specified */
    uint8_t  max_multsect; /* 0=not_implemented */
    uint8_t  vendor3; /* vendor unique */
    uint16_t dword_io; /* 0=not_implemented; 1=implemented */
    uint8_t  vendor4; /* vendor unique */
    uint8_t  capability; /* bits 0:DMA 1:LBA 2:IORDYsw 3:IORDYsup*/
    uint16_t reserved50; /* reserved (word 50) */
    uint8_t  vendor5; /* vendor unique */
    uint8_t  tPIO;  /* 0=slow, 1=medium, 2=fast */
    uint8_t  vendor6; /* vendor unique */
    uint8_t  tDMA;  /* 0=slow, 1=medium, 2=fast */
    uint16_t field_valid; /* bits 0:cur_ok 1:eide_ok */
    uint16_t cur_cyls; /* logical cylinders */
    uint16_t cur_heads; /* logical heads */
    uint16_t cur_sectors; /* logical sectors per track */
    uint16_t cur_capacity0; /* logical total sectors on drive */
    uint16_t cur_capacity1; /*  (2 words, misaligned int)     */
    uint8_t  multsect; /* current multiple sector count */
    uint8_t  multsect_valid; /* when (bit0==1) multsect is ok */
    uint32_t lba_capacity; /* total number of sectors */
    uint16_t dma_1word; /* single-word dma info */
    uint16_t dma_mword; /* multiple-word dma info */
    uint16_t eide_pio_modes; /* bits 0:mode3 1:mode4 */
    uint16_t eide_dma_min; /* min mword dma cycle time (ns) */
    uint16_t eide_dma_time; /* recommended mword dma cycle time (ns) */
    uint16_t eide_pio;       /* min cycle time (ns), no IORDY  */
    uint16_t eide_pio_iordy; /* min cycle time (ns), with IORDY */
    uint16_t reserved69; /* reserved (word 69) */
    uint16_t reserved70; /* reserved (word 70) */
} __attribute__((packed));

int ide_identify_master(struct ide_identify_format *);

#endif