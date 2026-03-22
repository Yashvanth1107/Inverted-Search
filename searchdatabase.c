#include "inverted.h"

/* normalize_token() cleans input word by removing any leading/trailing
 * Special characters and converts the result to lowercase.*/
static int normalize_token(const char *in, char *out, size_t out_size){
    int start = 0;
    int end = (int)strlen(in) - 1;

    //Remove unwanted characters from beginning
    while (start <= end && !isalnum((unsigned char)in[start]))
    {
        start++;
    }
    //Remove unwanted characters from end
    while (end >= start && !isalnum((unsigned char)in[end]))
    {
        end--;
    }
    if (start > end)
    {
        return 0;
    }
    //Copy valid chars
    size_t k = 0;
    for (int i = start; i <= end && k + 1 < out_size; ++i)
    {
        out[k++] = (char)tolower((unsigned char)in[i]);
    }
    out[k] = '\0';
    return (k > 0);
}

/* search_database() :
 * - Accepts a word from user
 * - Normalizes the word
 * - Computes hash index
 * - Searches main nodes
 * - Prints all file occurrences and count */
void search_database(MainNode *hashtable[]) 
{    
    char raw[WORD_SIZE];
    printf(CYAN "Enter the word to search: " RESET);

    if (scanf("%99s", raw) != 1)
    {
        printf(RED "ERROR: Input error.\n" RESET);
        return;
    }

    char token[WORD_SIZE];

    //Normalize input
    if (!normalize_token(raw, token, sizeof(token)))
    {
        printf(RED "ERROR: Invalid search token.\n" RESET);
        return;
    }

    //Determine hash index
    int index = isalpha(token[0]) ? token[0] - 'a' : SIZE - 1;

    MainNode *cur = hashtable[index];

    if (!cur)
    {
        printf(YELLOW "The word '%s' is not found in any file.\n" RESET, raw);
        return;
    }

    //Search main nodes for the word
    while (cur)
    {
        if (strcmp(cur->word, token) == 0)
        {
            printf(GREEN "The word '%s' is present in %d file(s):\n" RESET,raw, cur->file_count);

            //Print subnode info
            SubNode *s = cur->sub_link;
            while (s)
            {
                printf("→ " CYAN "%s" RESET " : " YELLOW "%d times\n" RESET,s->filename, s->word_count);
                s = s->link;
            }
            return;
        }
        cur = cur->link;
    }
    printf(YELLOW "The word '%s' is not found in any file.\n" RESET, raw);
}
