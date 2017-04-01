var rom_addr;

var sda = null;//new ScriptedDisAssembler();
var cfg = null;

var result = [];
var showAddr = true;
var showCode = true;
var upperCase = true;
var filesize = 0;
function result2text() {
	var i, j, text = "";
	for (i = 0; i < result.length; i++) {
		var addr = result[i][0];
		var code = result[i][1];
		var words = result[i][2];
		var inst = result[i][3];

		if (showAddr)
			text += sprintf(upperCase ? "$%06X " : "$%06x ", addr);
		if (showCode) {
			for (j = 0; j < words; j++) text += sprintf(upperCase ? "%04X " : "%04x ", code[j]);
			//for (j = words; j < 5; j++) text += "&nbsp;&nbsp;&nbsp;&nbsp; ";
			for (j = words; j < 5; j++) text += "     ";
		}
		text += upperCase ? inst.toUpperCase() : inst;
		//text += "<br/>";
		text += "\n";

		if (addr + words*2 >= filesize) break;
	}
	return text;
}

function Disassemble68kAddr(addr,opcodes){
    cfg.offset = addr - rom_addr;
    cfg.limit  = opcodes;
    result = sda.disassemble();
    return result2text();
}

function LoadRomTo68kDisasm(data,startloc,size){
    rom_addr = startloc;
    
    //Target device is Palm m515:
    //CPU: DragonBall MC68VZ328 
    //Opcode set: M68020
    sda = new ScriptedDisAssembler();
    cfg = sda.getConfig(); /* reference to config */
    
    for(var count = 0;count < size;count++){
        cfg.code += String.fromCharCode(data[count]);
    }
 
    filesize = size;
    cfg.prefx = "0x";
    cfg.reloc = false;
    //ROM now loaded and mapped to 68k address space
}