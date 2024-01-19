#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP_INFO \
"Usage instructions:\n\n" \
"1) To search for a substring in a file:\n" \
"   Run: ./str <substring> <filename>\n" \
"   Example: ./str \"hello\" str.txt\n\n" \
"2) To search for a substring from standard input:\n" \
"   Run: ./str <substring>\n" \
"   After running the command, enter the string you " \
"want to search through on the console.\n" \
"   Example: ./str \"hello\"\n" \
"   Then type your text and press Enter.\n"

int searchSubstring(char *substring, int subStrLen, FILE *f)
{
    char fbuffer[128];
    int currentMatch = 0;
    int i = 0;
    int answer = 0;

    while(fgets(fbuffer, sizeof(fbuffer), f)) {
        for(i = 0; fbuffer[i] != '\0'; i++) {
            if(fbuffer[i] == substring[currentMatch]) {
                currentMatch += 1;

                if(currentMatch == subStrLen) {
                    currentMatch = 0;
                    answer+=1;
                }
            } else {
                currentMatch = 0;
                if(fbuffer[i] == substring[0]) {
                    currentMatch += 1;
                }
            }
        }
    }

    return answer;
}

int strLen(char *str)
{
    char *firstElement = str;
    while(*str){
        str++;
    }
    return str - firstElement;
}

void printHelpInfo()
{
    printf(HELP_INFO);
}

void handleLineRead(char *substring, int subStrLen, FILE *f) {
    int currentChar = 0;
    int bufferSize = 4 * sizeof(char);
    char *fbuffer = malloc(bufferSize);
    //Substr search
    int subStrMatched = subStrLen;
    int currentSubStr = 0;

    while(1) {

        if(!fgets(fbuffer + currentChar, bufferSize - currentChar, f)) {
            perror("Error reading from file");
            exit(3);
        }

        while(fbuffer[currentChar]) {
            // searching for the first substring match
            if(fbuffer[currentChar] == *(substring + currentSubStr)) {
                subStrMatched-=1;
                currentSubStr++;
                if(subStrMatched == 0) {
                    printf("Substring found\n");
                }
            } else {
                subStrMatched = subStrLen;
                currentSubStr = 0;
            }

            currentChar++;

            if(currentChar >= bufferSize - 1) {
                bufferSize *= 2;
                char *temp = realloc(fbuffer, bufferSize);
                if (temp == NULL) {
                    free(fbuffer);
                    exit(1);
                }
                fbuffer = temp;
            }
        }
    }
    free(fbuffer);
}

int main(int argc, char *argv[])
{
    char *word;
    char *fileName;
    FILE *f;

    if(argc < 2) {
        fprintf(stderr, "Too few arguments!\n");
        printHelpInfo();
        return 1;
    }

    if(strcmp(argv[2],"grep") == 0) {
        word = argv[1];
        f = stdin;
        if(!f) {
            printf("Unable to open stdin\n");
            exit(2);
        }

        handleLineRead(word, strLen(word), f);
    }

    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printHelpInfo(); // execute help information
    } else if (argc == 3) {
        word = argv[1]; 
        fileName = argv[2];

        f = fopen(fileName, "r");
        if(!f) {
            perror(fileName);
            exit(1);
        }

        printf("%d\n", searchSubstring(word, strLen(word), f));
        fclose(f);
    } else if (argc == 2){
        word = argv[1]; 
        f = stdin;

        printf("%d\n", searchSubstring(word, strLen(word), f));
    } else {
        printf("No words was entered!\n");
    }

    return 0;
}