#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024       // Maximum length of a line in the file
#define MAX_FIELD_LENGTH 256       // Maximum length of a field (book name, abbreviation, etc.)


struct verse {
    char book[MAX_FIELD_LENGTH];   // Book name
    char abbr[MAX_FIELD_LENGTH];   // abbreviation of book name
    int book_num;                  // Book number
    int chapter;                   // Chapter number
    int verse_num;                 // Verse number
    char text[MAX_LINE_LENGTH];    // Verse text
};

void print_usage() {
    printf("Usage: bible -B <book_name_or_abbr> [-V <chapter>:<verse>]\n");
}

void trim(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && (str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == ' '))
        str[i--] = '\0';
}

// Main 
int main(int argc, char *argv[]) {
    // Check if there are enough command-line arguments
    if (argc < 3) {
        print_usage();
        return 1;
    }

    char *filename = "/usr/local/bin/kjv.tsv";  
    char book_name[MAX_FIELD_LENGTH] = "";  
    int chapter = -1, verse = -1;   

    // Parse command line arguments
    for (int i = 1; i < argc; i += 2) {
        // Check for option -B (book name or abbreviation)
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

    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        
        struct verse v;
        
        sscanf(line, "%[^\t]\t%[^\t]\t%d\t%d\t%d\t%[^\n]", v.book, v.abbr, &v.book_num, &v.chapter, &v.verse_num, v.text);
        
        trim(v.book);
        trim(v.abbr);

        
        // printf("Parsed: Book: %s, Abbr: %s, Book Num: %d, Chapter: %d, Verse: %d, Text: %s\n", v.book, v.abbr, v.book_num, v.chapter, v.verse_num, v.text);

        
        if (strcmp(v.book, book_name) == 0 || strcmp(v.abbr, book_name) == 0) {
            
            if (chapter == -1 || v.chapter == chapter) {
                
                if (verse == -1 || v.verse_num == verse) {
                    
                    printf("%s %d:%d - %s\n", v.book, v.chapter, v.verse_num, v.text);
                }
            }
        }
    }

    
    fclose(file);

    return 0;
}
