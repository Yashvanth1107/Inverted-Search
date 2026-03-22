#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverted.h"

int main(int argc, char *argv[]) 
{    
    //Validate command-line args
    if (argc < 2) 
    {
        printf(RED "Usage: %s file1.txt file2.txt ...\n" RESET, argv[0]);
        return 1;
    }
    SList *file_list = NULL; // File list head
    for (int i = 1; i < argc; i++)
    {
        validate_file(argv[i], &file_list);
    }
    //Exit if no valid files
    if (!file_list) 
    {
        printf(RED "No valid files to process. Exiting.\n" RESET);
        return 1;
    }

    //Initializing hashtable
    MainNode *hashtable[SIZE] = { NULL };

    int db_created = 0;
    int db_updated = 0;

    int choice;
    while (1) 
    {
        //Menu
        printf(CYAN "------ Inverted Search Menu ------\n" RESET);
        printf(GREEN "1. Create Database\n" RESET);
        printf(GREEN "2. Display Database\n" RESET);
        printf(GREEN "3. Search Database\n" RESET);
        printf(GREEN "4. Save Database\n" RESET);
        printf(GREEN "5. Update Database\n" RESET);
        printf(GREEN "6. Exit\n" RESET);

        //Input check
        if (scanf("%d", &choice) != 1)
        {
            printf(RED "ERROR: Invalid input, please enter 1-6.\n" RESET);
            while (getchar() != '\n');
            continue;
        }

        //Menu operations
        switch (choice) 
        {
            case 1: // Create DB
                if (db_created) 
                    printf(MAGENTA "Database already created.\n" RESET);
                else if (db_updated) 
                    printf(MAGENTA "Database already updated, cannot create now.\n" RESET);
                else 
                {
                    create_database(file_list, hashtable);
                    db_created = 1;
                    printf(GREEN "Database created successfully.\n" RESET);
                }
                break;

            case 2: // Display DB
                display_database(hashtable);
                break;

            case 3: // Search DB
                search_database(hashtable);
                break;

            case 4: // Save DB
                save_database(hashtable);
                break;

            case 5: // Update DB
                if (db_created) 
                    printf(MAGENTA "Database already created. Cannot update now.\n" RESET);
                else if (db_updated) 
                    printf(MAGENTA "Database already updated.\n" RESET);
                else 
                {
                    update_database(hashtable);
                    db_updated = 1;
                    printf(GREEN "Database updated successfully.\n" RESET);
                }
                break;

            case 6: // Exit
                printf(YELLOW "Exiting...\n" RESET);
                return 0;

            default:
                printf(RED "Invalid choice. Please enter 1-6.\n" RESET);
        }
    }
}