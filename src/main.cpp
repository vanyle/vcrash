#include <iostream>
#include "vcrash.h"

void faulty_function(){
    int a;
    int * ref = &a;
    ref[20000] ++; // this causes a segfault.
}

void faulty_caller(){
    faulty_function();
}

int main(int argc,char ** argv){
    setup_crash_handler();
    faulty_caller();
}