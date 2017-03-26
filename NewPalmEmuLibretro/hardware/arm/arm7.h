// GB Enhanced+ Copyright Daniel Baxter 2014
// Licensed under the GPLv2
// See LICENSE.txt for full license text

// File : arm7.h
// Date : April 09, 2014
// Description : ARM7TDMI emulator
//
// Emulates an ARM7TDMI CPU in software
// This is basically the core of the GBA

#ifndef GBA_CPU
#define GBA_CPU

#include <string>
#include <iostream>
#include <vector>

#include "types.h"
#include "dataexchange.h"

//hack
#include "minifunc.h"

/*
#include "common.h"
#include "timer.h"
#include "mmu.h"
#include "lcd.h"
#include "apu.h"
*/

/*
#define read_u32 read_u32_fast
#define read_u16 read_u16_fast
#define read_u8 read_u8_fast
*/

/*
#define mem_check_32(addr,value,action) \
	if(action)value = mem->read_u32(addr); \
	else mem->write_u32(addr,value)

#define mem_check_16(addr,value,action) \
	if(action)value = mem->read_u16(addr); \
	else mem->write_u16(addr,value)

#define mem_check_8(addr,value,action) \
	if(action)value = mem->read_u8(addr); \
	else mem->write_u8(addr,value)
*/

uint32 get_long(uint32 addr);
uint16 get_word(uint32 addr);
uint8 get_byte(uint32 addr);
void put_long(uint32 addr,uint32 l);
void put_word(uint32 addr,uint16 w);
void put_byte(uint32 addr,uint8 b);

class fakemmu{
public:
	/*
	//read
	//inline u32 read_u32_fast(u32 addr){return belong(get_long(addr));}
	//inline u16 read_u16_fast(u32 addr){return beword(get_word(addr));}

	inline u32 read_u32(u32 addr){return belong(get_long(addr));}
	inline u16 read_u16(u32 addr){return beword(get_word(addr));}
	inline u8 read_u8(u32 addr){return get_byte(addr);}

	inline u32 read_u32_fast(u32 addr){return read_u32(addr);}
	inline u16 read_u16_fast(u32 addr){return read_u16(addr);}



	//write
	//inline void write_u32_fast(u32 addr,u32 value){put_long(addr,belong(value));}
	//inline void write_u16_fast(u32 addr,u16 value){put_word(addr,beword(value));}

	inline void write_u32(u32 addr,u32 value){put_long(addr,belong(value));}
	inline void write_u16(u32 addr,u16 value){put_word(addr,beword(value));}
	inline void write_u8(u32 addr,u8 value){put_byte(addr,value);}

	inline void write_u32_fast(u32 addr,u32 value){write_u32(addr,value);}
	inline void write_u16_fast(u32 addr,u16 value){write_u16(addr,value);}
	*/


	//read
	//inline u32 read_u32_fast(u32 addr){return belong(get_long(addr));}
	//inline u16 read_u16_fast(u32 addr){return beword(get_word(addr));}

	inline u32 read_u32(u32 addr){return get_long(addr);}
	inline u16 read_u16(u32 addr){return get_word(addr);}
	inline u8 read_u8(u32 addr){return get_byte(addr);}

	inline u32 read_u32_fast(u32 addr){return read_u32(addr);}
	inline u16 read_u16_fast(u32 addr){return read_u16(addr);}



	//write
	//inline void write_u32_fast(u32 addr,u32 value){put_long(addr,belong(value));}
	//inline void write_u16_fast(u32 addr,u16 value){put_word(addr,beword(value));}

	inline void write_u32(u32 addr,u32 value){put_long(addr,value);}
	inline void write_u16(u32 addr,u16 value){put_word(addr,value);}
	inline void write_u8(u32 addr,u8 value){put_byte(addr,value);}

	inline void write_u32_fast(u32 addr,u32 value){write_u32(addr,value);}
	inline void write_u16_fast(u32 addr,u16 value){write_u16(addr,value);}
};


/* CPSR Flags */
const u32 CPSR_N_FLAG = 0x80000000;
const u32 CPSR_Z_FLAG = 0x40000000;
const u32 CPSR_C_FLAG = 0x20000000;
const u32 CPSR_V_FLAG = 0x10000000;
const u32 CPSR_Q_FLAG = 0x8000000;
const u32 CPSR_IRQ = 0x80;
const u32 CPSR_FIQ = 0x40;
const u32 CPSR_STATE = 0x20;
const u32 CPSR_MODE = 0x1F;


class ARM7
{
	public:

	//ARM instruction enumerations
	enum arm_instructions
	{
		UNDEFINED,
		PIPELINE_FILL,
		ARM_3,
		ARM_4,
		ARM_5,
		ARM_6,
		ARM_7,
		ARM_9,
		ARM_10,
		ARM_11,
		ARM_12,
		ARM_13,
		ARM_14,
		ARM_15,
		ARM_16,
		ARM_17,
		THUMB_1,
		THUMB_2,
		THUMB_3,
		THUMB_4,
		THUMB_5,
		THUMB_6,
		THUMB_7,
		THUMB_8,
		THUMB_9,
		THUMB_10,
		THUMB_11,
		THUMB_12,
		THUMB_13,
		THUMB_14,
		THUMB_15,
		THUMB_16,
		THUMB_17,
		THUMB_18,
		THUMB_19
	};

	//ARM CPU mode enumerations
	enum cpu_modes
	{
		USR,
		SYS,
		FIQ,
		SVC,
		ABT,
		IRQ,
		UND
	};

	//ARM CPU instruction mode enumerations
	enum instr_modes
	{
		ARM,
		THUMB
	};

	//BIOS read-state enumerations
	enum bios_state
	{
		BIOS_STARTUP,
		BIOS_IRQ_EXECUTE,
		BIOS_IRQ_FINISH,
		BIOS_SWI_FINISH
	};

	cpu_modes current_cpu_mode;
	instr_modes arm_mode;
	bios_state bios_read_state;

	//Internal registers - 32bits each
	struct registers
	{
		//General purpose registers
		u32 r0;
		u32 r1;
		u32 r2;
		u32 r3;
		u32 r4;
		u32 r5;
		u32 r6;
		u32 r7;
		u32 r8;
		u32 r9;
		u32 r10;
		u32 r11;
		u32 r12;

		//Stack Pointer - SP
		u32 r13; 

		//Link Register - LR
		u32 r14;

		//Program Counter - PC
		u32 r15;

		//Current Program Status Register - CPSR
		u32 cpsr;

		//Banked FIQ registers
		u32 r8_fiq;
		u32 r9_fiq;
		u32 r10_fiq;
		u32 r11_fiq;
		u32 r12_fiq;
		u32 r13_fiq;
		u32 r14_fiq;
		u32 spsr_fiq;

		//Banked Supervisor registers
		u32 r13_svc;
		u32 r14_svc;
		u32 spsr_svc;

		//Banked Abort registers
		u32 r13_abt;
		u32 r14_abt;
		u32 spsr_abt;

		//Banked IRQ registers
		u32 r13_irq;
		u32 r14_irq;
		u32 spsr_irq;

		//Banked Undefined registers
		u32 r13_und;
		u32 r14_und;
		u32 spsr_und;

	} reg;

	bool running;
	bool needs_flush;
	bool in_interrupt;
	bool sleep;

	bool swi_vblank_wait;

	u32 instruction_pipeline[3];
	arm_instructions instruction_operation[3];
	u8 pipeline_pointer;

	u8 debug_message;
	u32 debug_code;
	u32 debug_cycles;

	fakemmu* mem;
	//gba only stuff
	/*
	AGB_MMU* mem;

	//Audio-Video and other controllers
	struct io_controllers
	{
		AGB_LCD video;
		AGB_APU audio;
		std::vector<gba_timer> timer;
	} controllers;
	*/

	ARM7();
	~ARM7();

	//ARM pipelining functions
	void fetch();
	void decode();
	void execute();
	void update_pc();
	void flush_pipeline();

	void reset();

	//Get and set ARM registers
	u32 get_reg(u8 g_reg) const;
	void set_reg(u8 s_reg, u32 value);
	u32 get_spsr() const;
	void set_spsr(u32 value);

	//ARM instructions
	void branch_exchange(u32 current_arm_instruction);
	void branch_link(u32 current_arm_instruction);
	void data_processing(u32 current_arm_instruction);
	void psr_transfer(u32 current_arm_instruction);
	void multiply(u32 current_arm_instruction);
	void single_data_transfer(u32 current_arm_instruction);
	void halfword_signed_transfer(u32 current_arm_instruction);
	void block_data_transfer(u32 current_arm_instruction);
	void single_data_swap(u32 current_arm_instruction);
	void software_interrupt_breakpoint(u32 current_arm_instruction);

	//THUMB instructions
	void move_shifted_register(u16 current_thumb_instruction);
	void add_sub_immediate(u16 current_thumb_instruction);
	void mcas_immediate(u16 current_thumb_instruction);
	void alu_ops(u16 current_thumb_instruction);
	void hireg_bx(u16 current_thumb_instruction);
	void load_pc_relative(u16 current_thumb_instruction);
	void load_store_reg_offset(u16 current_thumb_instruction);
	void load_store_sign_ex(u16 current_thumb_instruction);
	void load_store_imm_offset(u16 current_thumb_instruction);
	void load_store_halfword(u16 current_thumb_instruction);
	void load_store_sp_relative(u16 current_thumb_instruction);
	void get_relative_address(u16 current_thumb_instruction);
	void add_offset_sp(u16 current_thumb_instruction);
	void push_pop(u16 current_thumb_instruction);
	void multiple_load_store(u16 current_thumb_instruction);
	void conditional_branch(u16 current_thumb_instruction);
	void unconditional_branch(u16 current_thumb_instruction);
	void long_branch_link(u16 current_thumb_instruction);

	//System functions
	//gba only
	/*
	void clock(u32 access_address, bool first_access);
	void clock();
	void clock_timers();
	void clock_dma();
	*/

	//disable gba clock
	inline void clock(){/*null*/}
	inline void clock(u32 addr,bool first){/*null*/}
	void handle_interrupt();

	//DMA functions
	void dma0();
	void dma1();
	void dma2();
	void dma3();

	//Misc CPU helpers
	void update_condition_logical(u32 result, u8 shift_out);
	void update_condition_arithmetic(u32 input, u32 operand, u32 result, bool addition);
	bool check_condition(u32 current_arm_instruction) const;
	u8 logical_shift_left(u32& input, u8 offset);
	u8 logical_shift_right(u32& input, u8 offset);
	u8 arithmetic_shift_right(u32& input, u8 offset);
	u8 rotate_right(u32& input, u8 offset);
	void rotate_right_special(u32& input, u8 offset);

	inline void mem_check_32(u32 addr, u32& value, bool load_store){
		if(load_store)value = mem->read_u32(addr);
		else mem->write_u32(addr,value);
	}

	inline void mem_check_16(u32 addr, u32& value, bool load_store){
		if(load_store)value = mem->read_u16(addr);
		else mem->write_u16(addr,value);
	}

	inline void mem_check_8(u32 addr, u32& value, bool load_store){
		if(load_store)value = mem->read_u8(addr);
		else mem->write_u8(addr,value);
	}

	//HLE Software Interrupts (BIOS Calls)
	void process_swi(u32 comment);
	/*
	void swi_softreset();
	void swi_registerramreset();
	void swi_div();
	void swi_divarm();
	void swi_sqrt();
	void swi_arctan();
	void swi_arctan2();
	void swi_cpufastset();
	void swi_cpuset();
	void swi_halt();
	void swi_sleep();
	void swi_vblankintrwait();
	void swi_lz77uncompvram();
	void swi_rluncompvram();
	void swi_huffuncomp();
	void swi_getbioschecksum();
	void swi_bgaffineset();
	void swi_objaffineset();
	void swi_bitunpack();
	void swi_midikey2freq();
	*/
};
		
#endif // GBA_CPU
