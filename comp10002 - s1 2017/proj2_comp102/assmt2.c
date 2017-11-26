/* =========================================================
	COMP10002 FOUNDATIONS OF FUN
	ASSESSMENT 2
	Author: Naufal Fikri (nsetiawan@student.unimelb.edu.au)
	Student ID: 844027
   ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

/* CONSTANTS */
#define HEADER_SIDE "========================="
#define STAGE_NUM_ONE 1
#define STAGE_NUM_TWO 2 
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5

#define ENTRY_START '#'
#define END_OF_DICT '%'

#define MAX_NAME_LENGTH 50
#define DICTIONARY_SIZE 100
#define NUM_WORD_TYPES 3
#define FIRST_NAME_TYPE 0
#define LAST_NAME_TYPE 1
#define DEFAULT_TYPE 2
#define WORD_TYPE_0	"FIRST_NAME"
#define WORD_TYPE_1 "LAST_NAME"
#define WORD_TYPE_2 "NOT_NAME"

#define SUCCESS 1
#define FAILURE 0
#define SEARCH_NOT_FOUND -1

#define DEFAULT_BOOL_VECTOR {0,0,1}
#define DEFAULT_PROB_VECTOR {0,0,100}
#define MAX_PROBABILITY 100

#define DEBUG 0

/*
	LINKED LIST IMPLEMENTATION
	Author: Naufal Fikri (nauffik@gmail.com)
*/

typedef char WordType[MAX_NAME_LENGTH];
typedef struct node NodeType;

struct node {
	WordType value;
	NodeType *next;
};

typedef struct {
	NodeType *head;
	NodeType *tail;
	int itemCount;
} ListType;

ListType *createList();
NodeType *getItem(ListType *list, int pos);
void popItem(ListType *list, int pos);
void insertAtHead(ListType *list, WordType value);
void insertAtTail(ListType *list, WordType value);
void insertItem(ListType *list, WordType value, int pos);
void deleteList(ListType *list);


ListType *createList() {
	ListType *list;
	list = (ListType*)malloc(sizeof(*list));
	assert(list != NULL);
	list->head = list->tail = NULL;
	list->itemCount = 0;
	return list;
}

NodeType *getItem(ListType *list, int pos) {
	assert(pos >= 0 && pos < list->itemCount);
	NodeType *node = list->head;
	int i;
	for (i = 0; i < pos; i++){
		node = node->next;
	}
	return node;
}


void insertAtHead(ListType *list, WordType value) {
	NodeType *newNode = (NodeType*)malloc(sizeof(*newNode));
	assert(list != NULL && newNode != NULL);
	strcpy(newNode->value, value);
	(list->itemCount)++;
	newNode->next = list->head;
	list->head = newNode;
	if (list->tail == NULL) {
		list->tail = newNode;
	}
}

void insertAtTail(ListType *list, WordType value){
	NodeType *newNode = (NodeType*)malloc(sizeof(*newNode));
	assert (list != NULL && newNode != NULL);
	strcpy(newNode->value, value);
	(list->itemCount)++;
	if (list->tail != NULL) {
		list->tail->next = newNode;
	}
	list->tail = newNode;
	if (list->head == NULL) {
		list->head = newNode;
	}
}

void insertItem(ListType *list, WordType value, int pos) {
	assert(pos >= 0 && pos < list->itemCount);
	NodeType *newNode = (NodeType*)malloc(sizeof(*newNode));
	assert(list != NULL && newNode != NULL);
	strcpy(value, newNode->value);
	NodeType *prev = getItem(list, pos-1);
	newNode->next = prev->next;
	prev->next = newNode;
	(list->itemCount)++;
}

void deleteList(ListType *list){
	NodeType *node, *prev;
	node = list->head;
	while (node) {
		prev = node;
		node = node->next;
		free(node);
	}
	free(list);
}

/*	
	The assignment code begins here.	

*/

/* Custom defined types */
/* A structure for one 'Dictionary Entry', every entry has the word itself and
the probabilities */
typedef struct {
	char word[MAX_NAME_LENGTH];
	int wordLength;
	int probabilities[NUM_WORD_TYPES];
} DictEntryType;

/* A structure for the 'dictionary' */
typedef struct {
	DictEntryType entries[MAX_NAME_LENGTH];
	int numEntries;
} DictionaryType;

/* Function Prototypes */
void stageOne(DictEntryType *dictEntry, int *numEntries);
void stageTwo(DictionaryType *dictionary);
void stageThree(ListType *sentence);
void stageFour(DictionaryType dictionary, ListType sentence);
void stageFive(DictionaryType dictionary, ListType sentence);
/* input functions */
int readDictionaryEntry(DictEntryType *dictEntry);
int readIntSequence(int *array, int dim);
void skipLine();
int readInputToList(ListType *list);
/* output functions */
void printHeading(int stagenum);
void printEntry(DictEntryType dictionary[], int index, int dim);
int addToDictionary(DictionaryType *dict, DictEntryType newEntry,
	int maxEntries);
/* other functions */
void copyArray(int *src, int  *dest, int dims);
void printList(ListType *list);
void classify(char *word, int *output, DictionaryType *dictionary,
	int numWordTypes);
int smarterClassify(NodeType *word, DictionaryType *dictionary,
	int numWordTypes);
int search(char *str, DictEntryType strArray[], int itemCount);
void printWordTypes(WordType word, int *booleans, char *wordTypes[], 
	int numWordTypes);
double averageWordLength(DictionaryType *dict);



/* this is where the fun begins */
/* algorithms are fun! */
int main(int argc, char *argv[]) {
	
	DictionaryType dictionary;
	dictionary.numEntries = 0;
	ListType *sentence = createList();

	/* this IS where the fun begins */
	stageOne(dictionary.entries, &dictionary.numEntries);
	stageTwo(&dictionary);
	stageThree(sentence);
	stageFour(dictionary, *sentence);
	stageFive(dictionary, *sentence);

	/* I MADE IT THIS FAR */
	deleteList(sentence);
	return 0;
}

/* Stage 1: reading and outputting one dictionary entry */
void stageOne(DictEntryType *dictEntry, int *numEntries){

	printHeading(STAGE_NUM_ONE);
	
	/** Just read one entry from the dictionary */
	readDictionaryEntry(dictEntry);
	(*numEntries)++;
	
	/* Prints the dictionary entry */
	printEntry(dictEntry, 0, NUM_WORD_TYPES);
}

/* Stage 2: reading the rest of the dictionary and printing out statistics */
void stageTwo(DictionaryType *dictionary){
	
	printHeading(STAGE_NUM_TWO);

	/* Keeps adding entries to the dictionary until it fails. */
	DictEntryType newEntry;
	while(readDictionaryEntry(&newEntry)) {
		addToDictionary(dictionary, newEntry, DICTIONARY_SIZE);

	}

	printf("Number of words: %d\n", dictionary->numEntries);
	printf("Average number of characters per word: %.2f\n", 
		averageWordLength(dictionary));
}

/* Stage 3: reading the sentence */
void stageThree(ListType *sentence){
	printHeading(STAGE_NUM_THREE);
	sentence->itemCount = 0;
	readInputToList(sentence);
	printList(sentence);
}

/* Stage 4: looking up the dictionary */
void stageFour(DictionaryType dictionary, ListType sentence){
	printHeading(STAGE_NUM_FOUR);

	/* A string array containing all the possible word types */
	char *wordTypes[NUM_WORD_TYPES] = {
		WORD_TYPE_0,
		WORD_TYPE_1,
		WORD_TYPE_2
	};

	NodeType *word = sentence.head;
	int wordClassification[NUM_WORD_TYPES];
	while(word != NULL) {
		/* Tries to classify each of the words in the list and outputs them */
		
		classify(word->value, wordClassification, 
			&dictionary, NUM_WORD_TYPES);
		
		printWordTypes(word->value, wordClassification, 
			wordTypes, NUM_WORD_TYPES);
		word = word->next;
	}
}

/* Stage 5: making accurate classifications */
void stageFive(DictionaryType dictionary, ListType sentence){
	printHeading(STAGE_NUM_FIVE);
	/* 	A string array containing all the word types. 
		In this case: FIRST_NAME,LAST_NAME,NOT_NAME respectively*/
	char *wordTypes[NUM_WORD_TYPES] = {
		WORD_TYPE_0,
		WORD_TYPE_1,
		WORD_TYPE_2
	};

	NodeType *word = sentence.head;
	while (word != NULL){
		/* Tries to classify the words in the list and outputs them. */
		
		int type = smarterClassify(word, &dictionary, NUM_WORD_TYPES);
		printf("%-32s%s\n", word->value, wordTypes[type]);
		word = word->next;
	}
}


/* FUNCTIONS THAT READ USER INPUT */
int readDictionaryEntry(DictEntryType *dictEntry){

	/* Reads the dictionary entry from the input and stores them at
	dictEntry. */
	if (getchar() == ENTRY_START) {
		int i = 0;
		dictEntry->wordLength = 0;
		char c;
		while ((c = getchar()) != '\n') {
			(dictEntry->word)[i++] = c;
			(dictEntry->wordLength)++;
		}
		(dictEntry->word)[i] = '\0';
		readIntSequence(dictEntry->probabilities, NUM_WORD_TYPES);
		return SUCCESS;
	} else if (getchar() == END_OF_DICT){
		/* If it is the end of the dictionary, then just skip the entire line
		so the next getChar() will start at the nextline. */
		skipLine();
	}

	return FAILURE;
}


int readIntSequence(int *array, int dim){
	/* Reads a line of dim integers and stores them in array */
	int i;
	for(i = 0; i < dim + 1; i++) {
		if(scanf("%d", array + i) != 1) {
			return FAILURE;
		}
	}
	return SUCCESS;
}

void skipLine() {
	/* Skips the current input line, causing getchar() to continue reading from
	the next line the next time it is called */
	char c;
	while ((c = getchar())) {
		if (c == '\n' || c == EOF) {
			break;
		}
	}
}

int readInputToList(ListType *list) {
	/* Reads the input line and stores the space-separated entries in the given
	list */
	char c; 
	int i = 0;
	WordType word;
	while ( (c=getchar()) != EOF) {
		if (c == '\n') {
			break;
		}
		if (c == ' ') {
			word[i] = '\0';
			insertAtTail(list, word);
			i = 0;
		} else {
			word[i++] = c;
		}
	}
	word[i] = '\0';
	insertAtTail(list, word);
	return 1;
}


/* FUNCTIONS THAT DISPLAY OUTPUT */
void printHeading(int stagenum) {
	/* Prints the stage heading */

	if (stagenum > 1) printf("\n");
	printf("%sStage %d%s\n", HEADER_SIDE, stagenum, HEADER_SIDE);
}

void printEntry(DictEntryType dictionary[], int index, int dim) {
	/* Prints the current dictionary entry given by the position index */

	printf("Word %d: %s\n", index, dictionary[index].word);
	printf("Label probabilities: ");
	int i;
	for (i = 0; i < dim; i++) {
		printf("%d%%", dictionary[index].probabilities[i]);
		printf("%c", i == dim - 1 ? '\n' : ' ');
	}
}

void printList(ListType *list){
	/* Prints the contents of the list, one line per item. */
	NodeType *current = list->head;
	while (current != NULL) {
		printf("%s\n", current->value);
		current = current->next;
	}
}

void printWordTypes(WordType word, int *booleans, 
	char *wordTypes[NUM_WORD_TYPES], int numWordTypes) {

	/* Prints the given word and their determined classifications */ 
	printf("%-32s", word);
	int i;
	int one = 0;
	for (i = 0; i < numWordTypes; i++) {
		if (booleans[i]) {
			if (one) {
				printf(", ");
			}
			printf("%s", wordTypes[i]);
			one = 1;
		}
	}
	printf("\n");
}

/* FUNCTIONS THAT DO OTHER STUFF */
int addToDictionary(DictionaryType *dict, DictEntryType newEntry,
	int maxEntries) {

	/* Adds an entry to the dictionary */
	if (dict->numEntries >= maxEntries) {
		return FAILURE;
	}
	dict->entries[dict->numEntries] = newEntry;

	(dict->numEntries)++;
	return SUCCESS;	
}

void copyArray(int *src, int  *dest, int dims) {
	/* copies the address from the source address to the destination address. */
	int i;
	for (i = 0; i < dims; i++) {
		dest[i] = src[i];
	}
}

void classify(char *word, int *output, DictionaryType *dictionary,
	int numWordTypes) {
	/* 	Classifies the words by looking up the probabilities in the dictionary.
		Then outputs the result of classification to the output 'boolean' 
		vector */
	/* Looks for the word in the dictionary and find their probabilities */
	int pos = search(word, dictionary->entries, dictionary->numEntries); 

	/* 	The default output vector, assumes that the word is word type 2 
		(NOT_NAME) */
	int defaultOutput[NUM_WORD_TYPES] = DEFAULT_BOOL_VECTOR;

	if (pos >= 0) {
		int *probs = dictionary->entries[pos].probabilities;
		int i;
		/* Alters the output vectors if there are nonzero probabilities for 
			other word types that's not NOT_NAME */
		for (i = 0; i < DEFAULT_TYPE; i++) {
			if (probs[i] > 0) {
				defaultOutput[i] = probs[i] > 0;
				defaultOutput[DEFAULT_TYPE] = 0;
			}
		}
	} 

	/* Copies the array to the output vector */
	copyArray(defaultOutput, output, NUM_WORD_TYPES);
}

int smarterClassify(NodeType *word, DictionaryType *dictionary,
	int numWordTypes) {
	int pos = search(word->value, dictionary->entries, dictionary->numEntries); 
	int probabilities[NUM_WORD_TYPES] = DEFAULT_PROB_VECTOR;

	/* Copies the probabilities from the dictionary. */
	if (pos == SEARCH_NOT_FOUND) {
		return DEFAULT_TYPE;
	} else {
		copyArray(dictionary->entries[pos].probabilities, probabilities,
			NUM_WORD_TYPES);
	}

	int i;

	/* If one of the probabilities have value 100%, then return that word
	type. */
	for (i = 0; i < NUM_WORD_TYPES; i++) {
		if (probabilities[i] == MAX_PROBABILITY) {
			return i;
		}
	}

	/* Contextual matching, tries to classify the word according to the
	classification of succeeding words. */
	if (word->next != NULL){
		int nextWordType = smarterClassify(word->next, dictionary, 
			NUM_WORD_TYPES);
		if(nextWordType == LAST_NAME_TYPE) {
			if (probabilities[FIRST_NAME_TYPE] > 0) {
				return FIRST_NAME_TYPE;
			}
		} else if (nextWordType == FIRST_NAME_TYPE) {
			return DEFAULT_TYPE;
		}
	}

	/* When everything else fails, return the highest word type probabilities */
	int maxProbability = 0;
	int maxProbType;
	for (i = 0; i < NUM_WORD_TYPES; i++){
		if (probabilities[i] > maxProbability) {
			maxProbType = i;
			maxProbability = probabilities[i];
		}
	}
	return maxProbType;
}

int search(char *str, DictEntryType entries[], int itemCount) {
	/* Searches the string in the dictionary and returns its index in the
	dictionary (using binary search). */

	int mid = (itemCount-1)/2;
	int compare = strcmp(str,entries[mid].word);

	if (itemCount == 1 && compare != 0)
	{
		return SEARCH_NOT_FOUND;
	}

	int pos;
	if (compare == 0) {
		return mid;
	} else if (compare < 0) {
		pos = search(str, entries, mid);
		return pos == SEARCH_NOT_FOUND ? SEARCH_NOT_FOUND : pos;
	} else if (compare > 0) {
		pos = search(str, entries + mid + 1, itemCount - mid - 1);
		return pos == SEARCH_NOT_FOUND ? SEARCH_NOT_FOUND : mid + 1 + pos;
	}

	return SEARCH_NOT_FOUND;
}

double averageWordLength(DictionaryType *dict) {
	/* Calculates the average word length in a dictionary */
	if (!(dict->numEntries)) return 0;
	double total = 0;
	int i;
	for (i = 0; i < dict->numEntries; i++) {
		total += dict->entries[i].wordLength;
	}
	return total/((double)dict->numEntries);
}