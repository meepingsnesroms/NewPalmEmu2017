#include "newcpu.h"
void op_6000(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(0)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6001(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(0)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6100(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	(Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}}}
void op_6101(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	(Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}}}
void op_6200(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(2)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6201(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(2)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6300(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(3)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6301(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(3)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6400(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(4)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6401(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(4)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6500(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(5)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6501(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(5)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6600(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(6)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6601(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(6)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6700(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(7)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6701(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(7)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6800(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(8)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6801(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(8)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6900(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(9)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6901(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(9)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6a00(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(10)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6a01(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(10)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6b00(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(11)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6b01(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(11)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6c00(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(12)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6c01(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(12)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6d00(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(13)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6d01(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(13)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6e00(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(14)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6e01(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(14)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6f00(ULONG NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	WORD src = nextiword();
	if (cctrue(15)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
void op_6f01(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	ULONG src = srcreg;
	if (cctrue(15)) (Shptr->regs).pc_p = (UWORD *)(oldpcp + (LONG)src);
}}}
