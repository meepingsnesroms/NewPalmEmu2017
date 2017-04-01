/* global CPPHeaderAsString */

var cppfile_rawtext = "";

function gen_cppfileheader(){
    cppfile_rawtext += CPPHeaderAsString;
}

function gen_apiname(apiname){
    var apiheader = "void " + apiname + "(){" + '\n';
    cppfile_rawtext += apiheader;
}

function gen_opcoderun(opcodename){
    var newline = "M68K_" + opcodename + "();";
    cppfile_rawtext += newline;
}

