var palmrom_bank = new SAEO_Memory_addrbank(
        palmrom_get32, palmrom_get16, palmrom_get8,
        null, null, null,
        palmrom_xlate, palmrom_check, null, "chip", "Palm OS ROM",
        palmrom_get32, palmrom_get16,
        SAEC_Memory_addrbank_flag_RAM | SAEC_Memory_addrbank_flag_THREADSAFE | SAEC_Memory_addrbank_flag_CHIPRAM
);

var SAEDisassemble = new ScriptedDisAssembler();

function Disassemble68kAddr(addr){
    SAEDisassemble.cpu.setPC_normal(addr);
    return SAEDisassemble.disassemble();
}

function LoadRomTo68k(startloc){
    //todo
}