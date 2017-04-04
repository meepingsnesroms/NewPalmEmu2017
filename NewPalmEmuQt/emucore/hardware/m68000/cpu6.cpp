#include "newcpu.h"
void op_6000(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(0)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6001(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(0)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6100(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	(Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}}}
void op_6101(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	(Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}}}
void op_6200(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(2)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6201(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(2)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6300(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(3)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6301(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(3)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6400(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(4)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6401(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(4)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6500(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(5)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6501(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(5)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6600(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(6)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6601(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(6)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6700(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(7)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6701(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(7)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6800(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(8)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6801(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(8)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6900(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(9)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6901(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(9)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6a00(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(10)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6a01(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(10)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6b00(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(11)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6b01(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(11)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6c00(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(12)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6c01(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(12)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6d00(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(13)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6d01(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(13)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6e00(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(14)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6e01(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(14)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6f00(uint32_t NUOPPRAM)
{
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	int16_t src = nextiword();
	if (cctrue(15)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
void op_6f01(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
{	char *oldpcp = (char *)(Shptr->regs).pc_p;
{	uint32_t src = srcreg;
	if (cctrue(15)) (Shptr->regs).pc_p = (uint16_t *)(oldpcp + (int32_t)src);
}}}
