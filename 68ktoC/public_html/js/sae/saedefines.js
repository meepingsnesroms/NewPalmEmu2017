var SAEC_Video_DEF_AMIGA_WIDTH = 360; //720 / 2;
var SAEC_Video_DEF_AMIGA_HEIGHT = 284; //568 / 2;
var SAEC_Video_MAX_AMIGA_WIDTH = 376; //752 / 2; //AMIGA_WIDTH_MAX
var SAEC_Video_MAX_AMIGA_HEIGHT = 288; //576 / 2; //AMIGA_HEIGHT_MAX

var SAEC_Video_MIN_UAE_WIDTH = 160;
var SAEC_Video_MAX_UAE_WIDTH = 3072; //max_uae_width
var SAEC_Video_MIN_UAE_HEIGHT = 128;
var SAEC_Video_MAX_UAE_HEIGHT = 2048; //max_uae_height

var SAEE_Assert = 5;



var SAER = null;

function SAEF_log() {
    var str = sprintf.apply(this, arguments);
    if (console.log) console.log(str);
    logprintf(str);
}
function SAEF_info() {
    var str = sprintf.apply(this, arguments);
    if (console.info) console.info(str);
    logprintf(str);
}
function SAEF_warn() {
    var str = sprintf.apply(this, arguments);
    if (console.warn) console.warn(str);
    logprintf(str);
}
function SAEF_error() {
    var str = sprintf.apply(this, arguments);
    if (console.error) console.error(str);
    logprintf(str);
}

/*

function SAEF_fatal() {
	var argumentsArray = Array.prototype.slice.call(arguments);
	var err = argumentsArray[0];
	var str = sprintf.apply(this, argumentsArray.slice(1));
	if (console.error) console.error(str);
        logprintf(str);
	throw new SAEO_Error(err, str);
}

function SAEF_assert(cond) {
	if (!cond) {
		var err = SAEE_Assert;
		var str = "Assertion failed. This is a bug in SAE.";
		if (console.error) console.error(str);
		throw new SAEO_Error(err, str);
	}
}

*/