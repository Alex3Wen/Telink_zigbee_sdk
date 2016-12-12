
#pragma once

#include "../common/types.h"


#define FLASH_4K_PAGE_NUM              16
#define FLASH_PAGE_SIZE                256

#define NV_MAX_SECTION_BLOCK           6

#define NV_SECTION_SIZE                (FLASH_PAGE_SIZE * FLASH_4K_PAGE_NUM)


/* 1000*256 = 250K */
#define START_PAGE_FOR_NV       (800 * FLASH_PAGE_SIZE)

#define END_PAGE_FOR_NV         (START_PAGE_FOR_NV + (NV_SECTION_SIZE * NV_MAX_SECTION_BLOCK))


#define NV_HEADER_TABLE_SIZE           10

#define INVALID_NV_VALUE               0xFF

#define MOUDLES_START_ADDR(modules)   (START_PAGE_FOR_NV + NV_SECTION_SIZE * (modules))

#define MOUDLES_AVALIABLE_SIZE(usedSize)  (FLASH_4K_PAGE_NUM * FLASH_PAGE_SIZE - (usedSize))

#define PAGE_AVALIABLE_SIZE(offset)       (FLASH_PAGE_SIZE - (offset % FLASH_PAGE_SIZE))

#define PAGE_HEADER_SISE  (sizeof(page_header_t))
#define NV_HEADER_SIZE  (sizeof(nv_header_t))

#define READ_BYTES_PER_TIME                 16     

#if 0
#define PAGE_INFO_NUM_PER_PAGE  (FLASH_PAGE_SIZE/sizeof(page_header_t))
typedef struct {
    u8 id;
    u8 offset;
} id_info_t;

typedef struct {
    u8 availableSize;
    id_info_t idTbl[ID_TABLE_SIZE];
    u8 reserved;
} page_header_t;

typedef struct {
    u8 pageId;
    u8 pageHdrId;
    u8 idTblIndex;
} id_pos_t;


typedef struct {
    /* info for nv block */
    u32 addr;
    u16 len;
    u8 id;
    u8 checksum;
} nv_header_t;

typedef struct {
    /* addr of header */
    u32 hdrAddr;
    nv_header_t hdrInfo;
} item_info_t;

#endif


typedef enum {
    DS_PIB_MODULE = 0,
    DS_TABLE_MODULE = 1,
    DS_PROFILE_MODULE = 2,
    DS_USER_MODULS = 3,
    DS_MAX_MOULDS,
} ds_module_t;

typedef struct {
    u16 offset;
    u16 len;
    u8 id;
} nv_header_t;


typedef struct {
    u16 usedSize;
    nv_header_t hdrList[NV_HEADER_TABLE_SIZE];
} page_header_t;

typedef struct {
    /* addr of header */
    u16 usedSize;
    u16 nvOffset;
    nv_header_t hdrInfo;
} item_info_t;




rst_t ds_nvWrite(u8 modules, u8 id, u16 len, u8 *buf);
void ds_initNV(u8 rst);
rst_t ds_nvRead(u8 modules, u8 id, u16 len, u8 *buf);
rst_t ds_resetModule(u8 modules);

rst_t ds_userSaveToFlash(u8 id, u16 len, u8 *buf);
rst_t ds_userLoadFromFlash(u8 id, u16 len, u8 *buf);
rst_t ds_userReset(void);


