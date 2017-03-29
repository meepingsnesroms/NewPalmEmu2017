#include <stdio.h>
#include <stdlib.h>
#include "cfl.h"

void main(void)
{
    CFL * cfl = new CFL();
    if (!cfl) 
    {
        printf("Unable to crate CFL object.");
        return;
    }        
    if (!cfl->openLibrary("hello.cfl"))
    {
        printf("Unable to open CFL file.");
        return;
    }    
    if (cfl->exists("hello.txt"))    
    {
        printf("Cfl does not contain hello.txt file.");
        return;
    }
    printf("%s",cfl->getFile("hello.txt"));
    delete cfl;
}