/**************************************************************************************************
  Filename:       bufm.h
  Revised:        $Date: 2013-05-27 $

  Description:    Implementation of buffer management
**************************************************************************************************/

#include "../tl_common.h"
#include "bufm.h"
#include "string.h"
#include "mempool.h"
#include "utility.h"
#include "error.h"

#ifdef WIN32
#include <malloc.h>
#endif


#if (MODULE_BUFM_ENABLE)

/**
 *  @brief Index of data payload for each buffer in bytes
 */
enum {
    SIZE_0_IDX = 0,
    SIZE_1_IDX,
    SIZE_2_IDX,
    NUM_SIZE,
};


/**************************** Private Variable Definitions *******************/

typedef struct {
    /**
    * head-of-queue array for free buffers
    */
    bufferItem_t* qHead;

    /**
    * available buffer number for each size blocks
    */
    u8 availBufNum;

    /**
    * specify the size of current buffer blocks;
    */
    u16 size;


} bufm_blocks_t;


typedef struct bufm_vars {

    bufm_blocks_t bufferBlocks[NUM_SIZE];
} bufm_vars_t;


bufm_vars_t bufm_vs;
bufm_vars_t *bufm_v = &bufm_vs;

MEMPOOL_DECLARE(size_0_pool, size_0_mem, SIZE_0, DFLT_BUFFER_ITEM_COUNT);
MEMPOOL_DECLARE(size_1_pool, size_1_mem, SIZE_1, DFLT_BUFFER_ITEM_COUNT);
MEMPOOL_DECLARE(size_2_pool, size_2_mem, SIZE_2, DFLT_BUFFER_ITEM_COUNT);

/*********************************************************************
 * @fn      bufm_isExisted
 *
 * @brief   Return whether the buffer is in the available buffer 
 *
 * @param   pd - the pointer of a data, which is previously allocated
 *
 * @return  Pointer of bufferItem
 */
u8 bufm_isExisted(u8 index, mem_block_t* block)
{
    mem_pool_t *pool = (mem_pool_t*)bufm_v->bufferBlocks[index].qHead;
    mem_block_t* curBlock = pool->free_list;

    while (curBlock) {
        if (block == curBlock) {
            return 1;
        } 
        curBlock = curBlock->next_block;
    }
    return 0;
}

u8* bufm_retriveMempoolHeader(u8* pd)
{
    return pd - (OFFSETOF(bufferItem_t, data) - OFFSETOF(mem_block_t, data));
}


/*********************************************************************
 * @fn      bufm_reset
 *
 * @brief   Reset the buffer management module
 *
 * @param   None
 *
 * @return  None
 */
void bufm_reset(void)
{
    int i;
    mem_pool_t *pool;
    u16 size[NUM_SIZE] = {SIZE_0, SIZE_1, SIZE_2};
    mem_pool_t *memPool[NUM_SIZE] = {&size_0_pool, &size_1_pool, &size_2_pool};
    //size_2_mem = (u8*)malloc(SIZE_2 * DFLT_BUFFER_ITEM_COUNT);
    u8* mem[NUM_SIZE] = {size_0_mem, size_1_mem, size_2_mem};

    memset(bufm_v, 0, sizeof(bufm_vars_t));

    /* reinitialize available buffer */
    for (i = 0; i < NUM_SIZE; i++) {
        bufm_v->bufferBlocks[i].availBufNum = DFLT_BUFFER_ITEM_COUNT;
        //pool = mempool_init(&memPool[i], mem[i], size[i], DFLT_BUFFER_ITEM_COUNT);
        bufm_v->bufferBlocks[i].qHead = (bufferItem_t*)mempool_init(memPool[i], mem[i], size[i], DFLT_BUFFER_ITEM_COUNT);
        bufm_v->bufferBlocks[i].size = size[i];
    }
}

/*********************************************************************
 * @fn      bufm_init
 *
 * @brief   Initialize the buffer management module
 *
 * @param   None
 *
 * @return  None
 */
void bufm_init(void)
{
    bufm_reset();
}



/*********************************************************************
 * @fn      bufm_allocate
 *
 * @brief   Allocate an available buffer according to the requested size 
 *
 * @param   size - requested size
 *
 * @return  Pointer of allocated buffer
 */
u8* bufm_allocate(u16 size)
{
    u8 index, i, r;
    bufferItem_t *pNewBuf;

    if (size > SIZE_MAX) {
        /* the size parameter is wrong */
        return NULL;
    }

    r = irq_disable();

    /* find related the buffer blocks */
    for (i = 0; i < NUM_SIZE; i++) {
        if (size <= bufm_v->bufferBlocks[i].size - OFFSETOF(bufferItem_t, data)) {
            index = i;
            break;
        }
    }

    if (!bufm_v->bufferBlocks[index].availBufNum) {
        /* no available buffer */
        irq_restore(r);
        return NULL;
    }

    bufm_v->bufferBlocks[index].availBufNum--;
    u8 *temp = (u8*)mempool_alloc((mem_pool_t*)bufm_v->bufferBlocks[index].qHead);
    pNewBuf = (bufferItem_t*)(temp - 4);
    pNewBuf->sizeIdx = index;
#if __DEBUG__    
#ifndef WIN32
    pNewBuf->next = (bufferItem_t*)(0xbbbbbbbb);
#endif    
#endif    
    irq_restore(r);

    return pNewBuf->data;
}


/*********************************************************************
 * @fn      bufm_free
 *
 * @brief   Return a previously allocated buffer to a free-buffer Queue 
 *
 * @param   dataPtr - the pointer to free
 *
 * @return  free status
 */
rst_t bufm_free(u8* dataPtr)
{
    u8 r;
    bufferItem_t *pDelBuf;

    if (!dataPtr) {
        return ERR_BUF_INVALID_PARAM;
    }

    r = irq_disable();

    pDelBuf = bufm_getHeadPtr(dataPtr);

    /* check whether the buffer is duplicated release */
    if (bufm_isExisted (pDelBuf->sizeIdx, (mem_block_t*)pDelBuf)) {
        assert(0);
        irq_restore(r);
        return ERR_BUF_DUPLICATE_FREE;
    }

    mempool_free((mem_pool_t*)bufm_v->bufferBlocks[pDelBuf->sizeIdx].qHead, bufm_retriveMempoolHeader(dataPtr));
    bufm_v->bufferBlocks[pDelBuf->sizeIdx].availBufNum++;

#if __DEBUG__
    memset(dataPtr, 0, DFLT_LARGE_BUF_SIZE);
#endif

    irq_restore(r);
    return ERR_NONE;
}


/*********************************************************************
 * @fn      bufm_getHeadPtr
 *
 * @brief   Get the header pointer of a buffer item 
 *
 * @param   pd - the pointer of a data, which is previously allocated
 *
 * @return  Pointer of bufferItem
 */
bufferItem_t* bufm_getHeadPtr(u8* pd)
{
    return (bufferItem_t*)(pd - OFFSETOF(bufferItem_t, data));
}


#endif  /* MODULE_BUFM_ENABLE */






