
#include "../tl_common.h"
#include "../common/mempool.h"
#if (MODULE_BUFM_ENABLE)
#include "../common/bufm.h"
#endif
#if (MODULE_PRIQ_ENABLE)
#include "../common/priority_queue.h"
#endif
#include "../common/error.h"
#include "../drivers/mouse.h"
#include "ut.h"

//////////////////////////////////////////////////////
void ut_test_types(void){
    STATIC_ASSERT(sizeof(u16) == 2);
    STATIC_ASSERT(sizeof(u32) == 4);
    STATIC_ASSERT(sizeof(u64) == 8);
    STATIC_ASSERT(sizeof(L"1") == 4);            // -fshort-wchar flag must be set for gcc
    STATIC_ASSERT(sizeof(L"12") == 6);            // -fshort-wchar flag must be set for gcc

}

void ut_test_bits(void){
    STATIC_ASSERT(BIT_LOW_BIT(1) == 0);
    STATIC_ASSERT(BIT_LOW_BIT(2) == 1);
    STATIC_ASSERT(BIT_LOW_BIT(3) == 0);
    STATIC_ASSERT(BIT_LOW_BIT(0xf0) == 4);
    STATIC_ASSERT(BIT_HIGH_BIT(0xf0) == 7);
    STATIC_ASSERT(FLD_MASK_VAL(0x001230, 0xf0, 6) == 0x1260);
    STATIC_ASSERT(MASK_VAL(0xf0, 6, 0x0f, 3) == 0x63);
    STATIC_ASSERT(MASK_VAL(0xf0, 6, 0x0f, 3) != 0x65);

    STATIC_ASSERT(BIT_RNG(0, 1) == 0x3);
    STATIC_ASSERT(BIT_RNG(2, 5) == 0x3c);

    STATIC_ASSERT(ONES(0) == 0);
    STATIC_ASSERT(ONES(5) == 0x1f);

    STATIC_ASSERT((BITS6(1, 2, 3, 4, 5, 6) == 0x7e));
    STATIC_ASSERT((BITS(1, 2) == 0x06));                //  needs  c99 support
    STATIC_ASSERT((BITS(1, 2, 3, 4, 5, 6, 7, 8) == 0x1fe));    //  needs  c99 support

    STATIC_ASSERT(BIT_IS_SET_HIGH((u32)0x80000010));
    
}

void ut_test_bits_dyn(){
    u8 a = 0x10; u16 b = 0x10; u32 c = 0x10; 
    BIT_SET_HIGH(a);
    BIT_SET_HIGH(b);
    BIT_SET_HIGH(c);
    ut_assert("set high char", a == 0x90);
    ut_assert("set high short", b == 0x8010);
    ut_assert("set high int", c == 0x80000010);

}

void ut_test_assert_works(void){
    ut_assert("Unit test works!", false);
    ut_case_fail = 0;
}

void ut_test_endian(void){
    ut_assert("Must be little endian", IS_LITTLE_ENDIAN);
}

MEMPOOL_DECLARE(mempool_test_pool, mempool_test_mem, 10, 5);
void ut_test_mempool(void){
    mem_pool_t* pool = mempool_init(&mempool_test_pool, mempool_test_mem, 10, 5);
    u8 * p1 = (u8*)mempool_alloc(pool);
    mem_block_t * pMb1 = mempool_header(p1);
    u8 * p2 = (u8*)mempool_alloc(pool);
    mem_block_t * pMb2 = mempool_header(p2);
    ut_assert("Mem list next block fail", pMb1->next_block == (void*)pMb2);
    mempool_alloc(pool);
    u8 * p4 = (u8*)mempool_alloc(pool);
    u8 * p5 = (u8*)mempool_alloc(pool);
    u8 * p6 = (u8*)mempool_alloc(pool);
    mem_block_t * pMb4 = mempool_header(p4);
    mem_block_t * pMb5 = mempool_header(p5);
    ut_assert("Mem list last block fail", pMb4->next_block == (void*)pMb5);
    ut_assert("Mem list tail", pMb5->next_block == 0);
    ut_assert("Mem list out of memory", 0 == p6);
    mempool_free(pool, p1);
    ut_assert("Mem list free 1", pool->free_list == mempool_header(p1));
    mempool_free(pool, p2);
    ut_assert("Mem list free 2", pool->free_list == mempool_header(p2));
    ut_assert("Mem list free 2", pool->free_list->next_block == mempool_header(p1));
    ut_assert("Mem list free 2", pool->free_list->next_block->next_block == 0);
    
}

#if (MODULE_ETH_ENABLE)
#include "../uip/core/net/uip_arp.h"
#endif
void ut_test_eth_hw(void){
#if (MODULE_ETH_ENABLE)
    STATIC_ASSERT(sizeof(struct uip_eth_hdr) == 14);    // uip struct must be packed  -fpack-struct
#endif
}

void ut_test_gpio_read_write(void){
    foreach(i, GPIO_MAX_COUNT){
        gpio_set_output_en(BIT(i), 1);
        gpio_write(BIT(i), 1);
        assert(gpio_read(BIT(i)) == BIT(i));
        gpio_write(BIT(i), 0);
        assert(gpio_read(BIT(i)) == 0);
    }
    foreach(i, GPIO_MAX_COUNT){
        gpio_set_output_en((BIT(i)|GPIO_FUNC_MASK), 1);
        gpio_write((BIT(i)|GPIO_FUNC_MASK), 1);
        assert(gpio_read((BIT(i)|GPIO_FUNC_MASK)) == BIT(i));
        gpio_write((BIT(i)|GPIO_FUNC_MASK), 0);
        assert(gpio_read((BIT(i)|GPIO_FUNC_MASK)) == 0);
    }
}

void ut_test_gpio_interrupt(void){
}
#if(MODULE_MOUSE_ENABLE && MOUSE_HAS_WHEEL)
extern int mouse_wheel_chk_dir(u32 w0, u32 w1);
void ut_test_mouse_wheel_driver(void){
    int count = 0;
    u8 w0[] = {0,0,1,1,1,0,0,1,0,0,1,1};
    u8 w1[] = {0,0,0,0,1,1,0,1,1,0,0,1};
    foreach_arr(i, w0){
        count += mouse_wheel_chk_dir(w0[i], w1[i]);
    }
    assert(count == 2);

    count = 0;
    u8 w2[] = {0,0,0,0,1,1,0,1,1,0,1};
    u8 w3[] = {0,0,1,1,1,0,0,1,0,1,1};
    foreach_arr(i, w2){
        count += mouse_wheel_chk_dir(w2[i], w3[i]);
    }
    assert(count == -2);
}
#endif

#if (MODULE_BUFM_ENABLE)
void ut_test_bufm(void)
{
    bufm_init();
    u8* p1 = bufm_allocate(32);
    memset(p1, 0x0a, 20);

    u8* p2 = bufm_allocate(150);
    memset(p2, 0x0b, 10);

    rst_t ret = bufm_free(p2);
    ut_assert("buffer free 1", ret == ERR_NONE);
    
    ret = bufm_free(p1);
    ut_assert("buffer free 1", ret == ERR_NONE);
    
    ret = bufm_free(p1);
    ut_assert("buffer free 1", ret == ERR_BUF_DUPLICATE_FREE);

    u8 *p[11];
    int  i =0;
    for (i = 0; i < 10; i++) {
        p[i] = bufm_allocate(170);
    }

    p1 = bufm_allocate(170);
    ut_assert("buffer free 1", p1 == NULL);

    ret = bufm_free(p1);
    ut_assert("buffer free 1", ret == ERR_BUF_INVALID_PARAM);

    for (i = 0; i < 10; i++) {
        ret = bufm_free(p[i]);
        ut_assert("buffer free 1", ret == ERR_NONE);
    }
}
#endif

#if (MODULE_PRIQ_ENABLE)
void ut_test_priQ(void)
{
    priQueue_t q;
    rst_t ret;
    u8* p1, *p2, *p3, *p4, *p5;
    priQ_init(&q, NULL);

    // test non-priority

    p1 = bufm_allocate(170);
    p1[5] = 0x0a;
    
    ret = priQ_push(&q, p1);
    ut_assert("priQ push ", ret == ERR_NONE);

    p2 = priQ_pop(&q);
    ut_assert("priQ pop ", p2[5] == 0x0a);
    ut_assert("priQ pop ", q.current_capacity == 0);

    p2 = bufm_allocate(170);
    p3 = bufm_allocate(170);
    p4 = bufm_allocate(170);

    ret = priQ_push(&q, p1);
    ut_assert("priQ push ", ret == ERR_NONE);
    ret = priQ_push(&q, p2);
    ut_assert("priQ push ", ret == ERR_NONE);
    ret = priQ_push(&q, p3);
    ut_assert("priQ push ", ret == ERR_NONE);
    ret = priQ_push(&q, p4);
    ut_assert("priQ push ", ret == ERR_NONE);

    ret = priQ_delete(&q, p2);
    ut_assert("priQ push ", ret == ERR_NONE);

    p5 = priQ_pop(&q);
    ut_assert("priQ push ", p5 == p1);
    p5 = priQ_pop(&q);
    ut_assert("priQ push ", p5 == p3);
    p5 = priQ_pop(&q);
    ut_assert("priQ push ", p5 == p4);

    ret = priQ_push(&q, p1);
    ret = priQ_push(&q, p2);
    ret = priQ_push(&q, p3);
    ret = priQ_push(&q, p4);
    priQ_freeQueue(&q);

    // test priority


    
}
#endif

///////////////////////////////////////////////////////
int ut_case_fail = 0;
int ut_cases_run = 0;
int ut_cases_success = 0;
static void ut_run(ut_func_t test){
    ut_case_fail = 0;
    test();
    ++ut_cases_run;
    if(!ut_case_fail){
        ++ut_cases_success;
    }
}

int ut_in_test;
static void ut_run_all() {
    ut_in_test = 1;
    ut_run(ut_test_assert_works);
    ut_run(ut_test_endian);
    ut_run(ut_test_mempool);
    ut_run(ut_test_bits_dyn);
    ut_run(ut_test_gpio_read_write);
    ut_run(ut_test_gpio_interrupt);
    ut_run(ut_test_eth_hw);
#if (MODULE_BUFM_ENABLE)
    ut_run(ut_test_bufm);
#endif
#if (MODULE_PRIQ_ENABLE)
    ut_run(ut_test_priQ);
#endif
#if(MODULE_MOUSE_ENABLE && MOUSE_HAS_WHEEL)
    ut_run(ut_test_mouse_wheel_driver);
#endif
    ut_in_test = 0;
}

// do not delete, this is  sample code of mixing protothread and timer
#if 0
#include "../os/et.h"
#include "../os/ev.h"
#include "../mcu/clock_i.h"
static et_t test_pt;
static void ut_test_protothread(void* data){
    static u8 count = 0;
    ET_BEGIN(&test_pt);
    for(count = 0; count < 20; ++count){
        if(!BIT_IS_EVEN(count)){
            break;
        }
        ET_YIELD_TIME(&test_pt, 10);
    }
    ET_END(&test_pt);
}
static int ut_test_protothread2(void* data){
    ut_test_protothread(0);
    return 10;
}
static ev_time_event_t test_pt_timer = {ut_test_protothread2};
#endif

int ut_unit_test() {
//    ev_on_timer(&test_pt_timer, 5);

    ut_cases_success = ut_cases_run = 0;
    ut_run_all();
    printf("Tests pass %d/%d\r\n", ut_cases_success, ut_cases_run);
    return (ut_cases_success != ut_cases_run);    //  0:  success, else: fail
}

