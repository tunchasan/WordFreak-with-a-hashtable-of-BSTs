#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Node.h"
#include "HashTable.h"

// Represents hash table array (length : 26)
HashNode** hashTable = NULL;

// Converts given text into words
void wordConverter(char*);

// Converts given word to lowercase
char* toLowerCase(char*);

// Finds according hashTable's index for the given word
void hashTableWordPlacer(const char*);

int main(int argc, char  *argv[])
{
    if(argc == 0) { // Standart input
        // TODO
    }
    else if(argc > 1){ // Handle given txt files

        // Initialize hash table
        hashTable = createHashTable();

        int fdin;

        char *buf = (char*)malloc(1024*(sizeof(char)));

        fdin = open(argv[1],O_RDONLY);

        while(read(fdin, buf, 1024) > 0)
        {
            // Sends each row to wordConverter
            wordConverter(buf);
        }

        close(fdin);
    }

  return 0;
}

void wordConverter(char* line){
    // counter
    int i;
    // Replace space for each character that' not a alphacharacter
    for(i = 0; i < strlen(line); i++){
        if(!isalpha(line[i])){
            line[i] = ' ';
        }
    }

    // To lowercase
    line = toLowerCase(line);

    // Represents a seperated word
    const char *word;

    word = strtok(line, " ");

    while (word != NULL)  {
      word = strtok (NULL, " ");

      if(word == NULL) break;

      // Sends "word" to the function for placing it to the according index 
      hashTableWordPlacer(strdup(word));
    }
}

char* toLowerCase(char* text) {
    // Represents a lowercase word
    char *word = (char*)malloc(strlen(text) * sizeof(char));

    int i;

    for(i = 0; i < strlen(text); i++){

        char ch = tolower(text[i]);

        word[i] = ch;
    }

    return word;
}

void hashTableWordPlacer(const char* word){
    int i;
    for(i = 0; i < 26; i++){
        if(hashTable[i]->letter == word[0]){
            printf("I FOUND MY PLACE : %c : %s\n", hashTable[i]->letter, word);
        }
    }
}