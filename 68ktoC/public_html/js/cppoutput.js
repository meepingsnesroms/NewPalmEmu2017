/* global CPPHeaderAsString */

var cppfile_rawtext = "";

function gen_cppfileheader(){
    cppfile_rawtext += CPPHeaderAsString;
}

function gen_apiname(apiname){
    var apiheader = "void " + apiname + "(){" + '\n';
    cppfile_rawtext += apiheader;
}

