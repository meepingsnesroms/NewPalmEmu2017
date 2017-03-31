/* global SAEC_Memory_addrbank_flag_CHIPRAM, SAEC_Memory_addrbank_flag_RAM, SAEC_Memory_addrbank_flag_THREADSAFE, SAEV_config, SAEC_Config_CPU_Model_68020, SAER_Memory_banks */

var rom_data;
var rom_addr;
var rom_size;

function palmrom_get32(addr){
        addr -= rom_addr;
        //the >>> operator prevents javascript from treating the vale as signed
        return ((rom_data[addr] << 24) | (rom_data[addr+1] << 16) | (rom_data[addr+2] << 8) | rom_data[addr+3]);
}
function palmrom_get16(addr){
        addr -= rom_addr;
        return (rom_data[addr] << 8) | rom_data[addr+1];
}
function palmrom_get8(addr){
        addr -= rom_addr;
        return rom_data[addr];
}
function palmrom_put32(addr, l){
    //the dissasmbler should not modify the rom
}
function palmrom_put16(addr, w){
    //the dissasmbler should not modify the rom
}
function palmrom_put8(addr, b){
    //the dissasmbler should not modify the rom
}
function palmrom_check(addr, size){
    addr -= rom_addr;
    return (addr + size) <= rom_size;
}
function palmrom_xlate(addr){
    /*
    addr = (addr & chipmem_bank.mask) >>> 0;
    return addr;
    */
   return true;
}

var palmrom_bank = new SAEO_Memory_addrbank(
    palmrom_get32, palmrom_get16, palmrom_get8,
    null, null, null,
    palmrom_xlate, palmrom_check, null, "chip", "Palm OS ROM",
    palmrom_get32, palmrom_get16,
    SAEC_Memory_addrbank_flag_RAM | SAEC_Memory_addrbank_flag_THREADSAFE | SAEC_Memory_addrbank_flag_CHIPRAM
);

function null_get32()           {return 0x00000000;}
function null_get16()           {return 0x0000;    }
function null_get8()            {return 0x00;      }
function null_check(addr, size) {return false;/*invalid, return false*/}
function null_xlate(addr)       {return 0;/*invalid, return 0*/}

var null_bank = new SAEO_Memory_addrbank(
    null_get32, null_get16, null_get8,
    null, null, null,
    null_xlate, null_check, null, "chip", "Palm OS ROM",
    null_get32, null_get16,
    SAEC_Memory_addrbank_flag_RAM | SAEC_Memory_addrbank_flag_THREADSAFE | SAEC_Memory_addrbank_flag_CHIPRAM
);

function FIXED_map_banks(banktype, bankstart, bankstofill) {
    for(var count = 0;count < bankstofill;count++){
        SAER_Memory_banks[bankstart + count] = banktype;
    }
}

var m68kmem = new SAEO_Memory();
var sda = null;//new ScriptedDisAssembler();
var cfg = null;

function Disassemble68kAddr(addr){
    cfg.offset = addr;
    for(var count = 0;count < rom_size;count++){
        cfg.code += rom_data[count];
    }
    return sda.disassemble();
}

function LoadRomTo68k(data,startloc,size){
    rom_data = data;
    rom_addr = startloc;
    rom_size = size;
    
    
    //round to nearest bank
    if(size & 0x0000FFFF){
        size += 0x00010000;
        size &= 0xFFFF0000;
    }
    FIXED_map_banks(null_bank, 0x0000/*starting bank*/, 0xFFFF/*banks to map*/);
    FIXED_map_banks(palmrom_bank, startloc >>> 16, size >>> 16);
    
    
    //Target device is Palm m515:
    //CPU: DragonBall MC68VZ328 
    //Opcode set: M68020
    sda = new ScriptedDisAssembler();
    cfg = sda.getConfig(); /* reference to config */
 
    //ROM now loaded and mapped to 68k address space
}