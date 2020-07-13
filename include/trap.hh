//
// Created by Bugen Zhao on 7/13/20.
//

#ifndef LITCHI_INCLUDE_TRAP_HH
#define LITCHI_INCLUDE_TRAP_HH

#include <include/string.hpp>
#include <include/panic.hpp>

namespace trap {
    enum class TrapType : int {
        divide = 0,
        debug,
        nmi,
        breakpoint,
        overflow,
        bound,
        illegalOp,
        device,
        doubleFault,
        coprocessor,    // reserved
        invalidTss,     // invalid task switch segment
        segmentNP,      // segment not present
        stack,
        gpFault,        // general protection fault
        pageFault,
        /* reserved, */
        fpError = 16,
        alignment,
        machineCheck,
        simdError,

        syscall = 88
    };

    struct Registers {
        /* registers as pushed by pusha */
        uint32_t edi;
        uint32_t esi;
        uint32_t ebp;
        uint32_t oesp;          /* Useless */
        uint32_t ebx;
        uint32_t edx;
        uint32_t ecx;
        uint32_t eax;
    } __attribute__((packed));

    struct Frame {
        /* manually saved */
        struct Registers regs;  /* pusha */
        uint16_t es;            /* movL */
        uint16_t padding1;
        uint16_t ds;            /* movL */
        uint16_t padding2;
        uint32_t trapNumber;    /* push imm */

        /* auto saved by x86 hardware */
        uint32_t err;
        uintptr_t eip;          /* iret */
        uint16_t cs;
        uint16_t padding3;
        uint32_t eflags;

        /* below here only when crossing rings, such as from user to kernel */
        uintptr_t esp;
        uint16_t ss;
        uint16_t padding4;

        inline void clear() {
            mem::clear(this, sizeof(*this));
        }

        // pop the trap frame and goto user mode
        inline void pop() {
            asm volatile (
            "movl %0, %%esp\n"      // move tf to stack
            "popal\n"
            "popl %%es\n"           // must be LONG
            "popl %%ds\n"
            "addl $0x8, %%esp\n"    // skip trap number and err
            "iret\n"                // IRET!!!
            :
            :"g"(this)              // put this to any General reg
            :"memory"               // do not reorder
            );

            kernelPanic("failed to pop and iret trap frame %08x", this);
        }
    } __attribute__((packed));
}

#endif //LITCHI_INCLUDE_TRAP_HH
