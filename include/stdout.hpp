//
// Created by Bugen Zhao on 2020/3/27.
//

#ifndef LITCHI_STDOUT_HPP
#define LITCHI_STDOUT_HPP

#include <include/types.h>
#include <include/vargs.hpp>
#include <include/color.h>

// Generic printFmt oriented putChar func pointer
typedef void (*_gePutCharFunction)(int, void *);

// printf.c

namespace console {
    namespace out {
        int printVa(const char *fmt, va_list ap);

        int print(const char *fmt, ...);
    }

    namespace err {
        void printVa(const char *fmt, va_list ap);

        void print(const char *fmt, ...);
    }
}

void filePrintFmtVa(int fd, const char *fmt, va_list ap);

void filePrintFmt(int fd, const char *fmt, ...);

// printfmt.c

void _gePrintNumber(_gePutCharFunction putChar, void *putdat, unsigned long long num, unsigned base, int width,
                    int paddingChar, bool capital, enum color_t fore, enum color_t back);

void _gePrintFmtVa(_gePutCharFunction putChar, void *putdat, const char *fmt, va_list ap, enum color_t defFore,
                   enum color_t defBack);

void _gePrintFmt(_gePutCharFunction putChar, void *putdat, const char *fmt, ...);


#endif //LITCHI_STDOUT_HPP