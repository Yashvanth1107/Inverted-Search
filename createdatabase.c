#include "inverted.h"

/* normalize_token() removes unwanted chars from beginning & end, 
 * It converts to lowercase, and returns a clean word.*/
static int normalize_token(const char *in, char *out, size_t out_size){
    
    int start = 0;
    int end = (int)strlen(in) - 1;

    //Skip unwanted characters at the beginning 
    while (start <= end && !isalnum((unsigned char)in[start]))
    {
        start++;
    }
    //Skip unwanted characters at the end 
    while (end >= start && !isalnum((unsigned char)in[end]))
    {
        end--;
    }
    //Word becomes empty after cleaning 
    if (start > end)
    {
        return 0;
    }
    //Copy valid chars in lowercase
    size_t k = 0;
    for (int i = start; i <= end && k + 1 < out_size; ++i)
    {
        out[k++] = (char)tolower((unsigned char)in[i]);
    }
    out[k] = '\0';
    return (k > 0);
}

/* create_database() reads each file in the given linked list and stores:
 *  - Unique words (MainNode)
 *  - Files containing that word (SubNode)
 *  - Number of times the word appears */
void create_database(SList *file_list, MainNode *hashtable[])
{
    //Initialize the hash table to NULL
    for (int i = 0; i < SIZE; ++i)
    {
        hashtable[i] = NULL;
    }
    //Process each file
    for (SList *f = file_list; f != NULL; f = f->link)
    {
        FILE *fp = fopen(f->filename, "r");
        if (!fp)
        {
            fprintf(stderr, RED "Warning: cannot open '%s'. Skipping.\n" RESET, f->filename);
            continue;
        }

        char raw[WORD_SIZE];

        //Read each token from file
        while (fscanf(fp, "%99s", raw) == 1)
        {
            char token[WORD_SIZE];

            //Normalize word
            if (!normalize_token(raw, token, sizeof(token)))
            {
                continue;
            }
            //Determine hash index 
            int index = isalpha(token[0]) ? token[0] - 'a' : SIZE - 1;

            //Search if the word already exists
            MainNode *m = hashtable[index];
            MainNode *found = NULL;

            while (m)
            {
                if (strcmp(m->word, token) == 0)
                {
                    found = m;
                    break;
                }
                m = m->link;
            }

            //If word not found → create MainNode + SubNode
            if (!found)
            {
                MainNode *newm = malloc(sizeof(MainNode));
                strncpy(newm->word, token, sizeof(newm->word) - 1);
                newm->word[sizeof(newm->word) - 1] = '\0';
                newm->file_count = 1;
                newm->sub_link = NULL;

                SubNode *s = malloc(sizeof(SubNode));
                strncpy(s->filename, f->filename, sizeof(s->filename) - 1);
                s->filename[sizeof(s->filename) - 1] = '\0';
                s->word_count = 1;
                s->link = NULL;

                newm->sub_link = s;

                //Insert at beginning of bucket
                newm->link = hashtable[index];
                hashtable[index] = newm;
            }
            else
            {
                //Word exists → check if file already listed
                SubNode *sn = found->sub_link;
                SubNode *sfound = NULL;

                while (sn)
                {
                    if (strcmp(sn->filename, f->filename) == 0)
                    {
                        sfound = sn;
                        break;
                    }
                    sn = sn->link;
                }

                //If new file → create new SubNode
                if (!sfound)
                {
                    SubNode *s = malloc(sizeof(SubNode));
                    strncpy(s->filename, f->filename, sizeof(s->filename) - 1);
                    s->filename[sizeof(s->filename) - 1] = '\0';
                    s->word_count = 1;
                    s->link = found->sub_link;

                    found->sub_link = s;
                    found->file_count++;
                }
                else
                {
                    //Same file → increase word count
                    sfound->word_count++;
                }
            }
        }
        fclose(fp);
    }
}