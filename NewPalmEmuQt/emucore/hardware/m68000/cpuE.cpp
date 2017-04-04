#include "newcpu.h"
void op_e000(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=val&1; val = ((uint32_t)val >> 1) | sign;
	}}
	NFLG = sign != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e008(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	int carry = 0;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e010(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e018(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&1; val = (uint32_t)val >> 1;
	if(carry) val |= cmask;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e020(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=val&1; val = ((uint32_t)val >> 1) | sign;
	}}
	NFLG = sign != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e028(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	int carry = 0;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e030(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e038(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&1; val = (uint32_t)val >> 1;
	if(carry) val |= cmask;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e040(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=val&1; val = ((uint32_t)val >> 1) | sign;
	}}
	NFLG = sign != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e048(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	int carry = 0;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e050(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e058(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&1; val = (uint32_t)val >> 1;
	if(carry) val |= cmask;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e060(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=val&1; val = ((uint32_t)val >> 1) | sign;
	}}
	NFLG = sign != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e068(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	int carry = 0;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e070(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e078(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&1; val = (uint32_t)val >> 1;
	if(carry) val |= cmask;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e080(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=val&1; val = ((uint32_t)val >> 1) | sign;
	}}
	NFLG = sign != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e088(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	int carry = 0;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e090(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e098(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&1; val = (uint32_t)val >> 1;
	if(carry) val |= cmask;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e0a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=val&1; val = ((uint32_t)val >> 1) | sign;
	}}
	NFLG = sign != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e0a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	int carry = 0;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e0b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&1; val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e0b8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&1; val = (uint32_t)val >> 1;
	if(carry) val |= cmask;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e0d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=val&1; val = (val >> 1) | sign;
	NFLG = sign != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e0d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=val&1; val = (val >> 1) | sign;
	NFLG = sign != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}}
void op_e0e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=val&1; val = (val >> 1) | sign;
	NFLG = sign != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}}
void op_e0e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=val&1; val = (val >> 1) | sign;
	NFLG = sign != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e0f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=val&1; val = (val >> 1) | sign;
	NFLG = sign != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}}
void op_e0f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=val&1; val = (val >> 1) | sign;
	NFLG = sign != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e0f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=val&1; val = (val >> 1) | sign;
	NFLG = sign != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e100(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else { 	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign)VFLG=1;
	}}
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e108(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e110(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e118(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if(carry)  val |= 1;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else { 	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign)VFLG=1;
	}}
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e138(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t cnt = (Shptr->regs).d[srcreg];
{	int8_t data = (Shptr->regs).d[dstreg];
{	uint8_t val = data;
	uint32_t cmask = 0x80;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if(carry)  val |= 1;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (val) & 0xff;
}}}}}
void op_e140(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else { 	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign)VFLG=1;
	}}
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e148(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e150(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e158(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if(carry)  val |= 1;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else { 	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign)VFLG=1;
	}}
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e178(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t cnt = (Shptr->regs).d[srcreg];
{	int16_t data = (Shptr->regs).d[dstreg];
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if(carry)  val |= 1;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}}}
void op_e180(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else { 	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign)VFLG=1;
	}}
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e188(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e190(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e198(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t cnt = srcreg;
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if(carry)  val |= 1;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e1a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	uint32_t sign = cmask & val;
	cnt &= 63;
	VFLG = 0;
	if (!cnt) { CFLG = 0; } else { 	for(;cnt;--cnt){
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign)VFLG=1;
	}}
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e1a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	}
	CFLG = (Shptr->regs).x = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e1b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	}
	CFLG = (Shptr->regs).x;
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e1b8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t cnt = (Shptr->regs).d[srcreg];
{	int32_t data = (Shptr->regs).d[dstreg];
{	uint32_t val = data;
	uint32_t cmask = 0x80000000;
	int carry = 0;
	cnt &= 63;
	if (!cnt) { CFLG = 0; } else {	for(;cnt;--cnt){
	carry=val&cmask; val <<= 1;
	if(carry)  val |= 1;
	}
	CFLG = carry!=0;
}
	NFLG = (val & cmask) != 0; ZFLG = val == 0; VFLG = 0;
	(Shptr->regs).d[dstreg] = (val);
}}}}}
void op_e1d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign) VFLG=1;
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e1d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign) VFLG=1;
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}}
void op_e1e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign) VFLG=1;
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}}
void op_e1e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign) VFLG=1;
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e1f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign) VFLG=1;
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}}
void op_e1f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign) VFLG=1;
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e1f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
	VFLG = 0;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	uint32_t sign = cmask & val;
	CFLG=(Shptr->regs).x=(val&cmask)!=0; val <<= 1;
	if ((val&cmask)!=sign) VFLG=1;
	NFLG = (val&cmask) != 0;
	ZFLG = val == 0;
	put_word(dataa,val);
}}}}
void op_e2d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	carry=val&1; val >>= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e2d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
{	uint16_t val = data;
	int carry = val&1;
	carry=val&1; val >>= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e2e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	carry=val&1; val >>= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e2e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	carry=val&1; val >>= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e2f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	carry=val&1; val >>= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e2f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	carry=val&1; val >>= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e2f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	carry=val&1; val >>= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e3d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e3d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e3e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e3e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e3f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e3f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e3f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = (Shptr->regs).x = carry!=0;
	put_word(dataa,val);
}}}}
void op_e4d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e4d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e4e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e4e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e4f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e4f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e4f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if((Shptr->regs).x) val |= cmask;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e5d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e5d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e5e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e5e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e5f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e5f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e5f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if((Shptr->regs).x) val |= 1;
	(Shptr->regs).x = carry != 0;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
(Shptr->regs).x = CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e6d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if(carry) val |= cmask;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e6d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if(carry) val |= cmask;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e6e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if(carry) val |= cmask;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e6e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if(carry) val |= cmask;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e6f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if(carry) val |= cmask;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e6f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if(carry) val |= cmask;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e6f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	int carry = val&1;
	uint32_t cmask = 0x8000;
	val >>= 1;
	if(carry) val |= cmask;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e7d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if(carry)  val |= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e7d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	(Shptr->regs).a[srcreg] += 2;
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if(carry)  val |= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e7e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k dataa = (Shptr->regs).a[srcreg];
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if(carry)  val |= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e7e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if(carry)  val |= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e7f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k dataa = (Shptr->regs).a[srcreg];
	dataa = get_disp_ea (dataa, nextiword());
{	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if(carry)  val |= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}}
void op_e7f8(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = (int32_t)(int16_t)nextiword();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if(carry)  val |= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
void op_e7f9(uint32_t NUOPPRAM)
{
{{	offset_68k dataa = nextilong();
	int16_t data = get_word(dataa);
{	uint16_t val = data;
	uint32_t cmask = 0x8000;
	int carry = val&cmask;
	val <<= 1;
	if(carry)  val |= 1;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(val)) == 0;
	NFLG = ((int16_t)(val)) < 0;
CFLG = carry!=0;
	put_word(dataa,val);
}}}}
