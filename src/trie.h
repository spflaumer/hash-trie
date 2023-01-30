#ifndef __TRIE_H

#include <stdbool.h>

#ifndef OPTN
    #define OPTN
#endif

#ifndef TRIE_CHARS
    // Initialize the trie with 69 Chars by default (lowercase ARE converted to uppercase unless otherwise specified); 
    // Can be changed to any value by defining the macro before including this header (requieres modification to NORM macro to fit the new indexes)
    // Combined with the NORM macro this covers all ASCII characters between 32 and 126 (from 'space' to '~')
    #ifndef TRIE_CASE_INSEN
        #define TRIE_CHARS 94
    #endif
    #ifdef TRIE_CASE_INSEN
        #define TRIE_CHARS 69
    #endif
#endif

#ifndef TRIE_NORM
    // NORM normalizes the input ASCII characters to match indexes in the trie
    #ifndef TRIE_CASE_INSEN
        #define TRIE_NORM(c) (c >= 32 ? (c <= 126 ? (c - 32) : (TRIE_CHARS + 1)) : (TRIE_CHARS + 1))
    #endif
    #ifdef TRIE_CASE_INSEN // define this before including this header to case insentivise the trie
        #define TRIE_NORM(c) (c >= 32 ? (c <= 126 ? (c >= 97 ? (c <= 122 ? (c - 64) : (c >= 123 ? (c - 58) : (TRIE_CHARS + 1))) : (c - 32)) : (TRIE_CHARS + 1)) : (TRIE_CHARS + 1)) 
    #endif
#endif

typedef struct trie {
    struct trie *head;
    struct trie *key[TRIE_CHARS + 1];
    bool end;
    OPTN
} trie_t;

int init_trie_node(trie_t **root);

#define __TRIE_H
#endif