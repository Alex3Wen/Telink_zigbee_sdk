
#ifdef MCU_CORE_3520

	.code	16
@********************************************************************************************************
@                                           MACROS AND DEFINIITIONS
@********************************************************************************************************

					@ Mode, correspords to bits 0-5 in CPSR
	.equ MODE_BITS,		0x1F	@ Bit mask for mode bits in CPSR
	.equ IRQ_MODE, 		0x12	@ Interrupt Request mode
	.equ SVC_MODE, 		0x13	@ Supervisor mode

	.equ IRQ_STK_SIZE,	0x100
	
@********************************************************************************************************
@                                            TC32 EXCEPTION VECTORS
@********************************************************************************************************
	.include "version.in"
	.section	.vectors,"ax"
	.global		__reset
	.global	 	__irq
	.global 	__start

__start:					@ MUST,  referenced by boot.link

	.extern irq_handler

	.org 0x0
	tj	__reset
	.word	(BUILD_VERSION)
	.org 0x8
	.word	(0x544c4e4b)
	.word	(0x00880080)

	.org 0x10
	tj		__irq
	.org 0x18
@********************************************************************************************************
@                                   LOW-LEVEL INITIALIZATION
@********************************************************************************************************
	.extern  main
	.balign 4
	.org 0x20
__reset:

	tloadr	r0, FLL_D
	tloadr	r1, FLL_D+4
	tloadr	r2, FLL_D+8
	
FLL_STK:
	tcmp	r1, r2
	tjge	FLL_STK_END
	tstorer r0, [r1, #0]
	tadd    r1, #4
	tj		FLL_STK
FLL_STK_END:

	tloadr	r0, DAT0
	tmcsr	r0			
	tloadr	r0, DAT0 + 8
	tmov	r13, r0  

	tloadr	r0, DAT0 + 4
	tmcsr	r0	
	tloadr	r0, DAT0 + 12
	tmov	r13, r0  

	tmov	r0, #0
	tloadr	r1, DAT0 + 16
	tloadr	r2, DAT0 + 20

ZERO:
	tcmp	r1, r2
	tjge	ZERO_END
	tstorer	r0, [r1, #0]
	tadd    r1, #4
	tj		ZERO
ZERO_END:

	tloadr	r1, DAT0 + 28
	tloadr	r2, DAT0 + 32

ZERO_TAG:
	tcmp	r1, r2
	tjge	ZERO_TAG_END
	tstorer	r0, [r1, #0]
	tadd    r1, #4
	tj		ZERO_TAG
ZERO_TAG_END:
	
SETIC:
	tloadr     r1, DAT0 + 24
	tmov	r0, #7;
	tstorerb	r0, [r1, #0]
	tmov	r0, #8;
	tstorerb	r0, [r1, #1]
	@tmov		r0, #0;
	@tstorerb	r0, [r1, #2]


	tloadr		r1, DATA_I
	tloadr		r2, DATA_I+4
	tloadr		r3, DATA_I+8
	
COPY_DATA:
	tcmp		r2, r3
	tjge		COPY_DATA_END
	tloadr		r0, [r1, #0]
	tstorer 	r0, [r2, #0]
	tadd    	r1, #4
	tadd		r2, #4
	tj			COPY_DATA
COPY_DATA_END:

	tjl	main
END:	tj	END

	.balign	4
DAT0:
	.word	0x12			    @IRQ    @0
	.word	0x13			    @SVC    @4
	.word	(irq_stk + IRQ_STK_SIZE)
	.word	(0x80a000)		    @12  stack end
	.word	(_start_bss_)               @16
	.word	(_end_bss_)                 @20
	.word   (0x80060c)                  @24
	.word   (0x808700)                  @28
	.word   (0x808800)                  @32
DATA_I:	
	.word	_dstored_
	.word	_start_data_
	.word	_end_data_
	
FLL_D:
	.word	0xffffffff
	.word	(_start_data_)	
	.word	(0x80a000)	


	.align 4
__irq:
     tpush       {r14}
     tpush       {r0, r1, r2, r3, r4, r5, r6, r7}
     tmrss       r0
     tmov        r7, r9
     tmov        r6, r10
     tmov        r5, r11
     tmov        r4, r12
     tmov        r3, r8
     tpush       {r0, r3, r4, r5, r6, r7}

     tjl         irq_handler

     tpop        {r0, r3, r4, r5, r6, r7}
     tmov        r9,r7
     tmov        r10,r6
     tmov        r11,r5
     tmov        r12,r4
     tmov        r8,r3
     tmssr       r0
     tpop        {r0, r1, r2, r3, r4, r5, r6, r7}
     treti       {r15}


	.org 256
ASMEND:

	.section .bss
	.align 4
	.lcomm irq_stk, IRQ_STK_SIZE
	.end

#endif
