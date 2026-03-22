#include "inverted.h"

// save_database saves the complete inverted index into a backup file.

void save_database(MainNode *hashtable[])
{    
    FILE *fp;
    char backup_filename[100];

    //Check if database is empty
    int empty = 1;
    for (int i = 0; i < SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            empty = 0;
            break;
        }
    }
    if (empty)
    {
        printf(RED "Database is empty. Nothing to save.\n" RESET);
        return;
    }

    //Get backup file name
    printf(CYAN "Enter the backup filename: " RESET);
    scanf("%99s", backup_filename);

    //Open file for writing
    fp = fopen(backup_filename, "w");
    if (fp == NULL)
    {
        perror(RED "Error opening backup file" RESET);
        return;
    }

    //Traverse hash table
    for (int i = 0; i < SIZE; i++)
    {
        MainNode *mtemp = hashtable[i];
        // Traverse main nodes
        while (mtemp != NULL)
        {
            // Save main node data
            fprintf(fp, "#%d;%s;%d;", i, mtemp->word, mtemp->file_count);

            // Traverse sub nodes
            SubNode *stemp = mtemp->sub_link;
            while (stemp != NULL)
            {
                fprintf(fp, "%s;%d;", stemp->filename, stemp->word_count);
                stemp = stemp->link;
            }

            // End of one main node
            fprintf(fp, "#\n");
            mtemp = mtemp->link;
        }
    }

    fclose(fp);
    printf(GREEN "Database saved successfully in " YELLOW "%s\n" RESET, backup_filename);
}

