//
// Created by Bugen Zhao on 2020/3/25.
//

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "console.h"
#include "version.h"
#include "pmap.h"
#include "monitor.h"

extern "C" {
void i386InitLitchi(void) {
    // Clear .BSS section
    extern char edata[], end[];
    mem::set(edata, 0, end - edata);

    // Init the console for I/O, and print welcome message
    console::init();
    console::out::print("%<%s%c %<%s!\n%<Kernel version %s\n(C) BugenZhao %d%03x\n\n",
                        YELLOW, "Hello", ',', LIGHT_MAGENTA, "Litchi", WHITE, LITCHI_VERSION, 2, 0x20);

    // Init memory
    vmem::init();

    // Go to the monitor
    int errno = monitor::main();
    kernelPanic("Monitor dead with errno %d", errno);
}
}