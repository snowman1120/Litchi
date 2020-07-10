//
// Created by Bugen Zhao on 2020/2/21.
//

// Naive basic string library

#include <string.h>
#include <types.h>
#include <ctype.h>


namespace mem {
    void *set(void *dest, uint8_t val, size_t count) {
        uint8_t *_dest = (uint8_t *) dest;
        while (count--)
            *(_dest++) = val;
        return dest;
    }

    void *copy(void *dest, const void *src, size_t count) {
        uint8_t *_dest = (uint8_t *) dest;
        uint8_t *_src = (uint8_t *) src;
        while (count--)
            *(_dest++) = *(_src++);
        return dest;
    }

    void clear(void *dest, size_t count) {
        set(dest, 0, count);
    }
}

namespace str {
    size_t count(const char *str) {
        size_t len = 0;
        while (*(str++))
            len++;
        return len;
    }

    char *append(char *dest, const char *src) {
        size_t len = count(dest);
        copy(dest + len, src);
        return dest;
    }

    char *copy(char *dest, const char *src) {
        char *ret = dest;
        while (*src)
            *(dest++) = *(src++);
        *dest = 0;
        return ret;
    }

    int cmp(const char *lhs, const char *rhs) {
        while (*lhs && *rhs && *lhs == *rhs)
            lhs++, rhs++;
        return *lhs - *rhs;
    }

    int cmpCase(const char *lhs, const char *rhs) {
        char a, b;
        while (*lhs && *rhs) {
            a = isCapital(*lhs) ? ((*lhs) - 'A' + 'a') : *lhs;
            b = isCapital(*rhs) ? ((*rhs) - 'A' + 'a') : *rhs;
            if (a != b) return a - b;
            lhs++, rhs++;
        }
        return *lhs - *rhs;
    }

    // Return the pointer to specific character in string
    char *find(const char *str, char c) {
        for (; *str; str++)
            if (*str == c) return (char *) str;
        return nullptr;
    }

    // Split string by any char in delimiters, return the count of substrings
    // Note: str will be split up to (bufCount - 1) pieces,
    //  since the last char * will always be NULL
    int split(char *str, const char *delimiters, char **resultBuf, size_t bufCount, bool ignoreQuo) {
        if (str == NULL) return -1;
        size_t count = 0;
        int quo = 0;

        while (count < bufCount - 1) {
            while (*str && find(delimiters, *str) != NULL) *str++ = '\0';
            if (*str == '\0') break;
            resultBuf[count++] = str;
            while (*str && (quo || find(delimiters, *str) == NULL)) {
                if (!ignoreQuo && *str == '\"') {
                    if (!quo) resultBuf[count - 1] = str + 1;
                    quo = !quo;
                    *str = '\0';
                }
                str++;
            }
        }

        if (quo) return -1;

        resultBuf[count] = NULL;
        return count;
    }

    // Split string by any whitespaces, return the count of substrings
    // Note: str will be split up to (bufCount - 1) pieces,
    //  since the last char * will always be NULL
    int splitWs(char *str, char **resultBuf, size_t bufCount) {
        return split(str, WHITESPACE, resultBuf, bufCount, true);
    }
}
