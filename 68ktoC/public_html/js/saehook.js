/* global SAEC_Memory_addrbank_flag_CHIPRAM, SAEC_Memory_addrbank_flag_RAM, SAEC_Memory_addrbank_flag_THREADSAFE */

var rom_data;
var rom_addr;
var rom_size;

function palmrom_get32(addr) {
        addr -= rom_addr;
        //the >>> operator prevents javascript from treating the vale as signed
        return ((rom_data[addr] << 24) | (rom_data[addr+1] << 16) | (rom_data[addr+2] << 8) | rom_data[addr+3]) >>> 0;
}
function palmrom_get16(addr) {
        addr -= rom_addr;
        return (rom_data[addr] << 8) | rom_data[addr+1];
}
function palmrom_get8(addr) {
        addr -= rom_addr;
        return rom_data[addr];
}
function palmrom_put32(addr, l) {
    //the dissasmbler should not modify the rom
}
function palmrom_put16(addr, w) {
    //the dissasmbler should not modify the rom
}
function palmrom_put8(addr, b) {
    //the dissasmbler should not modify the rom
}
function palmrom_check(addr, size) {
    addr -= rom_addr;
    return (addr + size) <= rom_size;
}
function palmrom_xlate(addr) {
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

var DisassemblerMemory = new SAEO_Memory();
var SAEDisassemble = new ScriptedDisAssembler();

function Disassemble68kAddr(addr){
    SAEDisassemble.cpu.setPC_normal(addr);
    return SAEDisassemble.disassemble();
}

function LoadRomTo68k(data,startloc,size){
    rom_data = data;
    rom_addr = startloc;
    size = rom_size;
    //round to nearest bank
    if(size & 0x0000FFFF){
        size += 0x00010000;
        size &= 0xFFFF0000;
    }
    SAER_Memory_mapBanks(palmrom_bank, startloc >> 16, size >> 16, 0/*only needed if provided unformatted data*/);
    SAEDisassemble.cpu.reset(true/*hard reset*/);
    //ROM now loaded and mapped to 68k address space
}