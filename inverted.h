#ifndef INVERTED_H
#define INVERTED_H

/* Standard header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define SIZE 27 

/* Maximum word length allowed */
#define WORD_SIZE 100

/* Hash table size — not used for hashing, but kept for safety */
#define TABLE_SIZE 50

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

/* ------------------ SUBNODE STRUCTURE ------------------
 * Each SubNode stores:
 * - filename     → name of the file containing the word
 * - word_count   → how many times the word occurs in that file
 * - link         → next SubNode (linked list of files)
 */
typedef struct SubNode {
    char filename[100];
    int word_count;
    struct SubNode *link;
} SubNode;

/* ------------------ MAINNODE STRUCTURE ------------------
 * Each MainNode stores a *unique word*
 * - word         → unique word
 * - file_count   → how many files contain this word
 * - sub_link     → points to SubNode list (files list)
 * - link         → next MainNode (words linked list)
 */
typedef struct MainNode {
    char word[50];
    int file_count;
    SubNode *sub_link;
    struct MainNode *link;
} MainNode;

/* ------------------ SLIST STRUCTURE ------------------
 * SList stores input file names used for creating database.
 * It is a simple linked list of file names.
 */
typedef struct SList {
    char filename[100];
    struct SList *link;
} SList;
int validate_file(char *filename, SList **file_list);

/* FUNCTION DECLARATIONS */
void create_database(SList *file_list, MainNode *hashtable[]);
int get_index(char *word);
void to_lowercase(const char *src, char *dest);
void display_database(MainNode *hashtable[]);
void search_database(MainNode *hashtable[]);
void save_database(MainNode *hashtable[]);
void update_database(MainNode *hashtable[]);

#endif
