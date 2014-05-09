//
//    Copyright (C) 2013-2014 Michael Geszkiewicz
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
//

#ifndef __BOARDS_H
#define __BOARDS_H

#include "hostmot2.h"

#define MAX_BOARDS 8

typedef enum {BOARD_ETH, BOARD_PCI, BOARD_EPP, BOARD_USB, BOARD_SPI} board_type;
typedef enum {BOARD_MODE_CPLD, BOARD_MODE_FPGA} board_mode;
typedef enum {BOARD_FLASH_NONE = 0, BOARD_FLASH_HM2, BOARD_FLASH_IO, BOARD_FLASH_GPIO, BOARD_FLASH_REMOTE, BOARD_FLASH_EPP} board_flash;

typedef struct board_struct board_t;

struct board_struct {
    board_type type;
    board_mode mode;
    board_flash flash;
    u8 flash_id;
    u32 flash_start_address;
    int fallback_support;
    char dev_addr[16];

    struct pci_dev *dev;
    void *base;
    int len;
    u32 mem_base;
#ifdef _WIN32
    tagPhysStruct_t mem_handle;
#endif
    u16 ctrl_base_addr;
    u16 data_base_addr;

    u16 base_lo;
    u16 base_hi;
    void *region;
    void *region_hi;
    int epp_wide;

    int (*open)(board_t *self);
    int (*close)(board_t *self);
    void (*print_info)(board_t *self);

    llio_t llio;
};

typedef struct {
    char *device_name;
    int list;
    int address;
    int verbose;
    int recover;
    int pci;
    int epp;
    int usb;
    int eth;
    int spi;
    char *dev_addr;
    u16 epp_base_addr;
    u16 epp_base_hi_addr;
} board_access_t;

extern board_t boards[MAX_BOARDS];
extern int boards_count;

#endif
