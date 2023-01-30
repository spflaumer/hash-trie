// GNU GPLv3 License notice at the bottom of this File
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRIE_CASE_INSEN
#include "trie.h"

char *trie_errlut[] = { "the root was empty!", "an invalid character was supplied!" };

int init_trie_node(trie_t **root){
    if(*root != NULL) { // don't init over an existing node
        return -1;
    }

    *root = calloc(1, sizeof(trie_t));
    trie_t *tmp = *root;
    for(unsigned char c = 0; c < TRIE_CHARS; c++) {
        tmp->key[c] = NULL;
    }
    tmp->head = NULL;

    return 0;
}

int trie_add_str(const char *dat, trie_t **root){
    if(*root == NULL){
        init_trie_node(root);
    }

    trie_t *tmp = *root;
    for(size_t i = 0; i < strlen(dat); i++){
        if(TRIE_NORM(dat[i]) == 127){
            return -2;
        }
        if(tmp->key[TRIE_NORM(dat[i])] == NULL){
            init_trie_node(&tmp->key[TRIE_NORM(dat[i])]);
            tmp = tmp->key[TRIE_NORM(dat[i])];
        } else {
            tmp = tmp->key[TRIE_NORM(dat[i])];
        }
    }
    tmp->end = true;

    return 0;
}

trie_t *trie_search(const char *dat, trie_t *root){
    if(root == NULL) return NULL;

    trie_t *tmp = root;
    for(size_t i = 0; i < strlen(dat); i++){
        if(tmp->key[TRIE_NORM(dat[i])] == NULL) return NULL;
        tmp = tmp->key[TRIE_NORM(dat[i])];
    }

    if(!tmp->end) return NULL;
    return tmp;
}
/*
    trie.c - Classic implementation of a Trie with some extra features
    Copyright (C) 2023  Simon Peter "spflaumer" Pflaumer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/