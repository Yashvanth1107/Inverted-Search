#include "inverted.h"

/* validate_file()
 * Checks:
 *  - file extension (.txt)
 *  - file exists
 *  - file is not empty
 *  - file is not duplicate */
int validate_file(char *filename, SList **file_list){
    
    //Check extension
    char *dot = strrchr(filename, '.');
    
    if (!dot || strcmp(dot, ".txt") != 0)
    {
        printf(RED "ERROR: Invalid file extension → %s\n" RESET, filename);
        return 0;
    }

    //File exists or not
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf(YELLOW "Skipping: File does not exist → %s\n" RESET, filename);
        return 0;
    }

    //Empty file or not
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    if (size == 0){
        printf(YELLOW "Skipping: File is empty → %s\n" RESET, filename);
        return 0;
    }

    //Duplicate is present or not
    SList *temp = *file_list;
    while (temp)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            printf(YELLOW "Skipping: Duplicate file → %s\n" RESET, filename);
            return 0;
        }
        temp = temp->link;
    }

    //Insert into SList
    SList *new = malloc(sizeof(SList));
    strcpy(new->filename, filename);
    new->link = NULL;

    if (*file_list == NULL)
    {
        *file_list = new;
    }
    else
    {
        SList *last = *file_list;
        while (last->link)
            last = last->link;
        last->link = new;
    }
    printf(YELLOW "File added -> %s\n" RESET, filename);
    return 1;
}