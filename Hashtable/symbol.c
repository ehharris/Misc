#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 * <p>
 * @author <b>Elijah Harris</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** Defines the data structure used to store nodes in the hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** Defines the data structure for the symbol table */
struct sym_table {
  int      size;        /**< size of hash table          */
  node_t** hash_table;  /**< array of node_t pointers    */
  char**   addr_table;  /**< array of character pointers */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo Implement this function */
sym_table_t* symbol_init (int table_size) {
  debug("symbol_init was called with table_size = %d", table_size);
  sym_table_t* hashtable = NULL;
  if (table_size < 1) return NULL;
  if((hashtable = malloc(sizeof(sym_table_t))) == NULL) return NULL;
  if((hashtable->hash_table = malloc(sizeof(node_t*)* table_size)) == NULL) return NULL;
  for( int i = 0; i < table_size; i++){
      hashtable->hash_table[i] = NULL;
  }
  if((hashtable->addr_table = malloc(sizeof(char*)* LC3_MEMORY_SIZE)) == NULL) return NULL;
  for( int i = 0; i < LC3_MEMORY_SIZE; i++){
      hashtable->addr_table[i] = NULL;
}
  hashtable->size = table_size;
  debug("Made it");
  return hashtable;
}

/** @todo Don't Implement this function */
void symbol_add_unique (sym_table_t* symTab, const char* name, int addr) {
    char* name_copy = strdup(name);
    int hashval = symbol_hash(name);
    int addy = hashval % symTab->size;
    symbol_t yeah = {name_copy, addr};
    node_t* nord = malloc(sizeof(node_t));
    nord->hash = hashval;
    nord->symbol = yeah;
    if(symTab->hash_table[addy] != NULL){
        nord->next = symTab->hash_table[addy];
    }
    else{
        nord->next = NULL;
    }    
    symTab->hash_table[addy] = nord;
    if(symTab->addr_table[addr] == NULL) symTab->addr_table[addr] = name_copy;
} 


/** @todo Implement this function */
void symbol_term (sym_table_t* symTab) {
    symbol_reset(symTab);
    free(symTab->hash_table);
    free(symTab->addr_table);
    free(symTab);
}

/** @todo Implement this function */
void symbol_reset(sym_table_t* symTab) {
    int size = symTab->size;
    int i;
    for (i = 0; i < size; i++){
        if(symTab->hash_table[i] != NULL){
                free(symTab->hash_table[i]);
                symTab->hash_table[i] = NULL;
        }
    }
    
    for (i = 0; i < LC3_MEMORY_SIZE; i++){
        if(symTab->addr_table[i] != NULL){
            free(symTab->addr_table[i]);
            symTab->addr_table[i] = NULL;
        }
    }
    
}

/** @todo Implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
    int ptrToHash;
    int ptrToIndex;
    
    node_t* jay = symbol_search(symTab, name, &ptrToHash, &ptrToIndex);
    if (jay != NULL){
        return 0;
    }
    symbol_add_unique(symTab, name, addr);
    return 1;
}

/** @todo Implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* ptrToHash, int* ptrToIndex) {
    *ptrToHash = symbol_hash(name);
    *ptrToIndex = *ptrToHash % symTab->size;
    node_t* jar = symTab->hash_table[*ptrToIndex];
    while(jar != NULL){
    if (jar->hash == *ptrToHash){
            symbol_t eyy = jar->symbol;
            char* jay = eyy.name;
            if (strcasecmp(jay, name) == 0){
                return jar;
            }
    }
    jar = jar->next;
    }
    return NULL;
}

/** @todo Implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
    int ptrToHash;
    int ptrToIndex;
    node_t* jerry = symbol_search(symTab, name, &ptrToHash, &ptrToIndex);
    if (jerry == NULL) return NULL;
    return &jerry->symbol;
}

/** @todo Implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
    return symTab->addr_table[addr];
}

/** @todo Implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
    for(int i = 0; i < symTab->size; i++){
        node_t* hashtable = symTab->hash_table[i]; 
        if(hashtable != NULL){
            (*fnc)(&hashtable->symbol, data);
            node_t* op = hashtable->next;
            while(op != NULL){
                (*fnc)(&op->symbol, data);
                op = op->next;
            }
        }
    }
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
  return symTab->size;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
    //return ( *(int*)vp1 - *(int*)vp2 );
    symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
    symbol_t* sym2 = *((symbol_t**) vp2); // study qsort to understand this
    int j = sizeof(&sym1->name);
    if (sizeof(&sym2->name) > sizeof(&sym1->name)) j = sizeof(&sym2->name);
    for (int i = 0; i < j; i++){
        if (&sym1->name[i] > &sym2->name[i]) return 1;
        if ((&sym1->name[i] < &sym2->name[i]) || &sym1->name[i] == NULL) return -1;
    }
    return compare_addresses(vp1, vp2);
}

/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
    symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
    symbol_t* sym2 = *((symbol_t**) vp2); // study qsort to understand this
    return (&sym1->addr - &sym2->addr);
}

/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
  // will call qsort with either compare_names or compare_addresses
    symbol_t** ans;
    ans = (symbol_t**) malloc(symTab->size * (sizeof(symbol_t)));
    node_t** crash = symTab->hash_table;
    int j = 0;
    for(int i = 0; i < symTab->size; i++){
        if(crash[i] == NULL) j++;
        while (crash[i] != NULL){
            ans[i - j] = &crash[i]->symbol;
            crash[i] = crash[i]->next;
            j--;
        }
    }
    j = 0;
    for(int i = 0; i < (sizeof(&crash)); i++){
        if (ans[i] != NULL){
            j++;
        }
    }
    symbol_t** realAns = (symbol_t**) malloc(j * (sizeof(symbol_t)));
    for(int i = 0; i < j; i++){
        realAns[i] = ans[i];
    }
    free(ans);
    if (order == 0) //HASH
    {
        return realAns;
    }
    
    if(order == 1) //NAME
    {
        qsort(realAns, j, sizeof(symbol_t), compare_names);
        return realAns;
    }
    
    if(order == 2) //ADDR
    {
        qsort(realAns, j, sizeof(symbol_t), compare_addresses);
        return realAns;
    }
    return NULL;
}
