//main() takes a uint8 array
function main(file){
    //the starting address for execution
    var initlocation = (file[4] << 24) | (file[5] << 16) | (file[6] << 8) | file[7];
    //the bank in memory the rom is loaded to, the first bank and inital execution bank are always the same
    var romaddress = initlocation & 0xFFFF0000;
    
    logprintf("Size of file: " + file.length + '\n');
    logprintf("68k ROM Load Addr: " + "0x" + romaddress.toString(16).toUpperCase() + '\n');
    logprintf("68k Execution Start Addr: " + "0x" + initlocation.toString(16).toUpperCase() + '\n');
    
    LoadRomTo68k(file,romaddress,file.length);
    Disassemble68kAddr(initlocation);
    
}
