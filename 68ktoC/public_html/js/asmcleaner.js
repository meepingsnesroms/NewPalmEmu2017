var ASMstring = "";

//in cpp . represents a sub item so it must be replaced with a inert character before conversion
function conv_DotsToUnderscore(){
    ASMstring = ASMstring.replace(/\./g,'_');
}

//converts $ to goto label
function conv_MoneyToGotoLabel(){
    //"M68KPC_"
}

function CleanASM(dirtyasm){
    ASMstring = dirtyasm;
    conv_DotsToUnderscore();
    conv_MoneyToGotoLabel();
    return ASMstring;
}