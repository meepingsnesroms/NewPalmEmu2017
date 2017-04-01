var ASMstring;

//in cpp . represents a sub item so it must be replaced with a inert character before conversion
function conv_DotsToUnderscore(){
    ASMstring = ASMstring.replace('.','_');
}

function CleanASM(dirtyasm){
    ASMstring = dirtyasm;
    conv_DotsToUnderscore();
}