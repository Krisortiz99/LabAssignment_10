#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    char* word[20];
    struct Trie* next;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if(word == NULL){
        return NULL;
    }
    struct Trie* Temp = pTrie;
    Temp->word = word;

    if(pTrie->next == NULL){
        pTrie->next = Temp;
        free(Temp);
    }
    else 
        insert(pTrie->next, word);

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{   
    int count;
    while(pTrie != NULL){
        if(pTrie->word == word){
            count++;
        }
        pTrie= pTrie->next;
    }
    return(count);
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{ 
    while(pTrie!= NULL){
        free(pTrie);
        pTrie = pTrie->next;
    }
}

// Initializes a trie structure
struct Trie *createTrie()
{   
    struct Trie* newTrie = malloc(sizeof(struct Trie*));
    newTrie->word ==NULL;
    for(int i = 0; i < 256; i++)
        newTrie->next == NULL;
    return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int count;
    char Word[20];
    FILE *Fr = fopen(filename, "r");
    while (Fr){
        fscanf(Fr, "%s", &Word);
        if(Word == pInWords)
            count++;
    }
    return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}