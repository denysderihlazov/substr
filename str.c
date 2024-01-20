#include <stdio.h>
#include <stdlib.h>

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
    // Substr search
    int currentSubStr = 0;
    int subStrFound = 0;
    // Grepstyle output
    int currentLineStart = 0;

    while(1) {

        if(!fgets(fbuffer + currentChar, bufferSize - currentChar, f)){
            printf("Error reading from file");
            exit(3);
        }

        while(fbuffer[currentChar]) {
            if(fbuffer[currentChar] == '\n') {
                // Print grep style line with found substring
                if(subStrFound){
                    printf("\n%.*s\n", currentChar - currentLineStart, fbuffer + currentLineStart);
                    exit(4);
                }
                currentLineStart  = currentChar + 1;
                subStrFound = 0;
            }

            // searching for the first substring match and printing whole line
            if(fbuffer[currentChar] == substring[currentSubStr]) {
                currentSubStr++;
                if (currentSubStr == subStrLen) {
                    subStrFound = 1;
                }
            } else {
                currentSubStr = 0;
            }

            currentChar++;

            if(currentChar >= bufferSize - 1) {
                bufferSize *= 2;
                char *temp = realloc(fbuffer, bufferSize);
                if (temp == NULL) {
                    free(fbuffer);
                    exit(5);
                }
                fbuffer = temp;
            }
        }
    }
    free(fbuffer);
}

int strCompare(char *str1, char *str2) {
    int i = 0;
    while(*(str1+i) != '\0' && *(str2+i) != '\0') {
        if((int)*(str1+i) == (int)*(str2+i) && (int)*(str1+i+1) == (int)*(str2+i+1)) {
            i++;
        } else {
            return 0;
        }
    }
    return 1; //In contrast to strcmp(), my function returns 1 when strings are identical.
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

    if(strCompare(argv[1], "-h") || strCompare(argv[1], "--help")) {
        printHelpInfo(); // execute help information
    } else if (argc == 4 && strCompare(argv[3],"grep")) {
        word = argv[1]; 
        fileName = argv[2];

        f = fopen(fileName, "r");
        if(!f) {
            perror(fileName);
            exit(0);
        }
        
        handleLineRead(word, strLen(word), f);
        fclose(f);
    } else if (argc == 3 && strCompare(argv[2],"grep")) {
        word = argv[1];
        f = stdin;
        if(!f) {
            printf("Unable to open stdin\n");
            exit(1);
        }

        handleLineRead(word, strLen(word), f);
        fclose(f);
    } else if (argc == 3) {
        word = argv[1]; 
        fileName = argv[2];

        f = fopen(fileName, "r");
        if(!f) {
            perror(fileName);
            exit(2);
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