
#-----------------------------------------------------------------------
# : pass arguments to umaincall helper.
#-----------------------------------------------------------------------
.section .text
.global lib_call
.type lib_call, @function

#define CSR_DLBOUND0LO 0x890
#define CSR_DLBOUND0HI 0x891
#define CSR_DLBOUND1LO 0x892
#define CSR_DLBOUND1HI 0x893
#define CSR_DJBOUND0LO 0x8c0
#define CSR_DJBOUND0HI 0x8c1
#define CSR_DJBOUND0HI 0x8c1
#define CSR_DJCFG 0x8c8
#define CSR_DLCFG 0x880

lib_call:
    addi   sp, sp, -8
    sd     ra, 0(sp)
   li t0, 0x4000000000
   li t1, 0x2000000000
   li t2, 0xb
   li t3, 0x1
   csrw CSR_DLBOUND0LO, zero
   csrw CSR_DLBOUND0HI, t0
   csrw CSR_DLCFG, t2
   fence.i
    mv    t0, a0
    mv    a0, a1
    mv    a1, a2
    mv    a2, a3
    mv    a3, a4
    mv    a4, a5
    mv    a5, a6
    .word 0x0002908b    // dasicscall.jr ra, t0
   csrw CSR_DLBOUND0LO, zero
   csrw CSR_DLBOUND0HI, zero
   csrw CSR_DLCFG, zero
    ld     ra, 0(sp)
    addi   sp, sp, 8
    ret