#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie *children[26];
    int count;
};

struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *pCurrent = pTrie;
    for (int i = 0; i < strlen(word); i++)
    {
        if (pCurrent->children[word[i] - 'a'] == NULL)
        {
            pCurrent->children[word[i] - 'a'] = createTrie();
            pCurrent = pCurrent->children[word[i] - 'a'];
        }
        else
        {
            pCurrent = pCurrent->children[word[i] - 'a'];
        }
    }
    pCurrent->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *pCurrent = pTrie;
    for (int i = 0; i < strlen(word); i++)
    {
        if (pCurrent->children[word[i] - 'a'] == NULL)
        {
            return 0;
        }
        else
        {
            pCurrent = pCurrent->children[word[i] - 'a'];
        }
    }
    return pCurrent->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->children[i] != NULL)
        {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->count = 0;
    for (int i = 0; i < 26; i++)
    {
        pTrie->children[i] = NULL;
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }
    int numWords = 0;
    fscanf(fp, "%d", &numWords);
    for (int i = 0; i < numWords; i++)
    {
        pInWords[i] = (char *)malloc(sizeof(char) * 256);
        fscanf(fp, "%s", pInWords[i]);
    }
    fclose(fp);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}