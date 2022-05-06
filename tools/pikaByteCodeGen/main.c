#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"
#include "PikaParser.h"
#include "dataStrs.h"
#include "PikaCompiler.h"
#include "libpikabinder.h"

PikaObj* __pikaMain;

void pikaCompileFileWithInfo(char* filename){
    __platform_printf("    compiling %s...\r\n", filename);
    pikaCompileFile(filename);
}

void main() {
    /* run pika_binder to bind C modules */
    pika_binder();
    pikaCompileFileWithInfo("main.py");
    return;
}