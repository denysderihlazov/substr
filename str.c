#include <stdio.h>
#include <stdlib.h>

int searchSubstringInFile(char *substring, int strLen, char *fileName)
{
    FILE *f;
    f = fopen(fileName, "r");

    if(!f) {
        perror(fileName);
        exit(1);
    }

    char fbuffer[3];
    int currentMatch = 0;
    int i = 0;
    int answer = 0;

    while(fgets(fbuffer, sizeof(fbuffer), f)) {

        for(i = 0; fbuffer[i] != '\0'; i++) {
            if(fbuffer[i] == substring[currentMatch]) {
                currentMatch += 1;

                if(currentMatch == strLen) {
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
    fclose(f);

    return answer;
}

int strLen(char *str) {
    char *firstElement = str;
    while(*str){
        str++;
    }
    return str - firstElement;
}

int main(int argc, char *argv[])
{
    char *word;
    char *fileName;
    if(argc > 2) {
        word = argv[1];
        fileName = argv[2];

        printf("The phrase '%s' matches %d times.\n",
            word, searchSubstringInFile(word, strLen(word), fileName));
    } else {
        printf("No words was entered!\n");
    }

    return 0;
}