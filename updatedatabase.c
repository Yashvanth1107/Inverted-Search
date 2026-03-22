/* update_database(), reads backup file saved by save_database()
 * Expected format:
 * #index;word;filecount;file1;count1;file2;count2;*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverted.h"

void update_database(MainNode *hashtable[])
{    
    char filename[100];
    printf(CYAN "Enter backup file name: " RESET);
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    
    //Validation
    if (!fp)
    {
        printf(RED "Error: Cannot open %s\n" RESET, filename);
        return;
    }

    //Clear old database
    for (int i = 0; i < SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    char line[1000];
    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] != '#')
        {
            continue;
        }
        int index, file_count;
        char word[50];
        char *token = strtok(line, ";");   // #index
        if (!token) continue;

        index = atoi(token + 1);           // skip '#'

        token = strtok(NULL, ";");         // word
        if (!token) continue;
        strcpy(word, token);

        token = strtok(NULL, ";");         // file_count
        if (!token) continue;
        file_count = atoi(token);

        //Create MainNode
        MainNode *mnew = malloc(sizeof(MainNode));
        strcpy(mnew->word, word);
        mnew->file_count = file_count;
        mnew->sub_link = NULL;

        //Insert in hash table
        mnew->link = hashtable[index];
        hashtable[index] = mnew;

        //Read remaining: file;count;file;count;
        for (int i = 0; i < file_count; i++)
        {
            char *fname = strtok(NULL, ";");
            char *count_str = strtok(NULL, ";");

            if (!fname || !count_str)
            {
                break;
            }
            int count = atoi(count_str);

            SubNode *snew = malloc(sizeof(SubNode));
            strcpy(snew->filename, fname);
            snew->word_count = count;

            //Insert subnode
            snew->link = mnew->sub_link;
            mnew->sub_link = snew;
        }
    }
    fclose(fp);
    printf(GREEN "Database restored successfully from %s\n" RESET, filename);
}
