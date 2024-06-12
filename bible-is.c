#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256
#define MAX_FILENAME_LENGTH 256

// Structure to store information about a verse
struct verse {
    char book[MAX_FIELD_LENGTH];   // Book name
    char abbr[MAX_FIELD_LENGTH];   // Abbreviation of book name
    int book_num;                  // Book number
    int chapter;                   // Chapter number
    int verse_num;                 // Verse number
    char text[MAX_LINE_LENGTH];    // Verse text
};

// Function to print program usage
void print_usage() {
    printf("Usage: bible -B <book_name> [-V <chapter>:<verse>]\n");
}

// Function to trim leading and trailing whitespace characters from a string
void trim(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && (str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == ' '))
        str[i--] = '\0';
}

// Main function
int main(int argc, char *argv[]) {
    // Check if there are enough command-line arguments
    if (argc < 3) {
        print_usage();
        return 1;
    }

    char *filename = "/usr/local/bin/kjv.tsv";  // File name of the .tsv file
    char book_name[MAX_FIELD_LENGTH] = "";  // Book name entered by user
    int chapter = -1, verse = -1;   // Chapter and verse entered by user

    // Parse command line arguments
    for (int i = 1; i < argc; i += 2) {
        // Check for option -B (book name)
        if (strcmp(argv[i], "-B") == 0) {
            strncpy(book_name, argv[i + 1], MAX_FIELD_LENGTH - 1);
        } 
        // Check for option -V (chapter:verse)
        else if (strcmp(argv[i], "-V") == 0) {
            char *token = strtok(argv[i + 1], ":");
            if (token != NULL) {
                chapter = atoi(token);
                token = strtok(NULL, ":");
                if (token != NULL)
                    verse = atoi(token);
            }
        }
    }

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the file line by line
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        // Create a structure to store verse information
        struct verse v;
        // Parse each line of the file
        sscanf(line, "%s\t%s\t%d\t%d\t%d\t%[^\n]", v.book, v.abbr, &v.book_num, &v.chapter, &v.verse_num, v.text);
        // Remove leading and trailing whitespace characters from the book name
        trim(v.book);
        // Check if the book name matches the specified criteria
        if (strcmp(v.book, book_name) == 0) {
            // Check if the chapter matches the specified criteria
            if (chapter == -1 || v.chapter == chapter) {
                // Check if the verse matches the specified criteria
                if (verse == -1 || v.verse_num == verse) {
                    // Print the verse
                    printf("%s %d:%d - %s\n", v.book, v.chapter, v.verse_num, v.text);
                }
            }
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
