# VCrash

VCrash is a C++/C library used to display stack traces on Windows with MinGW64.

VCrash is header only but requires to be linked with the `dbghelp` library that is available by default on window (use the `-ldbghelp` option when linking). Also, to access to the name of the functions and their line count in the stack trace, you will need to generate a `pdb` file from the executable. To to this, use the `cv2pdb` executable of the repo or download it somewhere with `cv2pdb program.exe`

## Usage

```cpp
#include <iostream>
#include "vcrash.h"

int main(int argc,char ** argv){
    setup_crash_handler();
    // Write the rest of your program is usual
}
```

## An example

````cpp
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
````

Building:

```
g++ .\main.cpp -g -ldbghelp -o main.exe
cv2pdb .\main.exe
.\main.exe
```

The code above will print something like this (when a `pdb` file is provided)

````
A crash occured.
At faulty_function (.\main.cpp:7)
At faulty_caller (.\main.cpp:12)
At main (.\main.cpp:17)
````

Notice that the lines number are not exact, they only provide an approximate location for the line that caused the issue.

## Credit

http://theorangeduck.com/page/printing-stack-trace-mingw

Without this blog post, this would not be possible as I found very little good documentation on printing the stack with MinGW.