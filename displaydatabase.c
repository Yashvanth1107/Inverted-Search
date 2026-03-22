#include <stdio.h>
#include "inverted.h"

/* display_database()
 * Displays the complete inverted index in table format:
 * [index] [word] [filecount] [filename] [wordcount]
 * For each MainNode (unique word), all SubNodes (files and
 * counts) are printed */
void display_database(MainNode *hashtable[])
{
    //Print table header
    printf(CYAN "%-10s%-15s%-15s%-20s%-15s\n" RESET, "[index]", "[word]", "[filecount]", "[filename]", "[wordcount]");

    for (int i = 0; i < SIZE; i++)
    {
        MainNode *main = hashtable[i];
        //Traverse all main nodes at index 'i'
        while (main != NULL)
        {    
            SubNode *sub = main->sub_link;
            int first = 1;  // To print main node details only once

            //Traverse all subnodes
            while (sub != NULL)
            {
                if (first)
                {
                    //Print full row including main node data
                    printf("%-10d%-15s%-15d%-20s%-15d\n",i, main->word, main->file_count,sub->filename, sub->word_count);
                    first = 0;
                }
                else
                {
                    //Only print subnode data with indentation
                    printf("%-40s%-20s%-15d\n", "",sub->filename, sub->word_count);
                }
                sub = sub->link;
            }
            main = main->link;
        }
    }
}