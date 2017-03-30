/* errors (copied from amiga.js) */

function SAEO_Error(err, msg) {
	this.err = err;
	this.msg = msg;
}
SAEO_Error.prototype = new Error;

var SAEE_None = 0;

var SAEE_AlreadyRunning = 1;
var SAEE_NotRunning = 2;
var SAEE_NoTimer = 3;
var SAEE_NoMemory = 4;
var SAEE_Assert = 5;
var SAEE_Internal = 6;

var SAEE_Config_Invalid = 10;

var SAEE_CPU_Internal = 20;
var SAEE_CPU_Requires68020 = 21;
var SAEE_CPU_Requires680EC20 = 22;
var SAEE_CPU_Requires68030 = 23;
var SAEE_CPU_Requires68040 = 24;

/*-----------------------------------------------------------------------*/

function ScriptedDisAssembler() {
	this.cpu = new SAEO_CPU();
	var err = this.cpu.setup_da(68030);
	if (err != SAEE_None)
		throw err;

	/*---------------------------------*/

	this.getConfig = function() {
		return this.cpu.getConfig_da();
	}
	this.disassemble = function() {
		return this.cpu.disassemble();
	}
}
