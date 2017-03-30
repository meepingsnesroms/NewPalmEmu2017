//main() takes a uint8 array
function main(file){
    logprintf("Size of file:" + file.length + '\n');
    //recompiling starts here
    //
    //the starting address for execution
    var initlocation = (file[4] << 24) | (file[5] << 16) | (file[6] << 8) | file[7];
    
    //the bank in memory the rom is loaded to, the top 2 bytes are the bank
    //the first bank and inital exeution bank are always the same
    var romaddress = initlocation & 0xFFFF0000;
    
    
    
}
