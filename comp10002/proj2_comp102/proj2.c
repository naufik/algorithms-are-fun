/* =========================================================
	COMP10002 FOUNDATIONS OF ALGORITHMS
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
#define ALGORITHMS "FUN"

#define MAX_NAME_LENGTH 50
#define DICTIONARY_SIZE 100
#define NUM_WORD_TYPES 3
#define WORD_TYPE_0	"FIRST_NAME"
#define WORD_TYPE_1 "LAST_NAME"
#define WORD_TYPE_2 "NOT_NAME"

#define TRUE 1
#define FALSE 0

#define SUCCESS 1
#define FAILURE 0

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
NodeType *nodeOffset(NodeType *node, int offset);
NodeType *getItem(ListType *list, int pos);
void popHead(ListType *list);
void popTail(ListType *list);
void popItem(ListType *list, int pos);
void insertAtHead(ListType *list, WordType value);
void insertAtTail(ListType *list, WordType value);
void insertItem(ListType *list, WordType value, int pos);
void fuckThisList(ListType *list);



ListType *createList() {
	ListType *list;
	list = (ListType*)malloc(sizeof(*list));
	assert(list != NULL);
	list->head = list->tail = NULL;
	list->itemCount = 0;
	return list;
}

NodeType *nodeOffset(NodeType *node, int offset) {
	for (int i = 0; i < offset; i++) {
		if (node->next == NULL) {
			/** exception handling **/
		}
		node = node->next;
	}
	return node;
}

NodeType *getItem(ListType *list, int pos) {
	assert(pos >= 0 && pos < list->itemCount);
	NodeType *node = list->head;
	for (int i = 0; i < pos; i++){
		node = node->next;
	}
	return node;
}


void popHead(ListType *list) {
	NodeType *node = list->head;
	list->head = list->head->next;
	(list->itemCount)--;
	free(node);
}

void popTail(ListType *list) {
	NodeType *node = list->tail;
	list->tail = list->tail->next;
	(list->itemCount)--;
	free(node);
}

void popItem(ListType *list, int pos) {
	assert(pos >= 0 && pos < list->itemCount);
	if (pos == 0) {
		popHead(list);
	} else if (pos == list->itemCount - 1) {
		popTail(list);
	} else {
		NodeType *prev = getItem(list, pos-1);
		NodeType *node = prev->next;
		NodeType *nextNode = node->next;
		prev->next = nextNode;
		list->itemCount -= 1;
		free(node);
	}
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

void fuckThisList(ListType *list){
	NodeType *node, *prev;
	node = list->head;
	while (node) {
		prev = node;
		node = node->next;
		free(node);
	}
	free(list);
}


/* Program begins here. */


/* Custom defined types */
typedef struct {
	char word[MAX_NAME_LENGTH];
	int wordLength;
	int probabilities[NUM_WORD_TYPES];
} DictEntryType;

typedef struct {
	DictEntryType entries[MAX_NAME_LENGTH];
	int ordIndex[DICTIONARY_SIZE];
	int numEntries;
} DictionaryType;

/* Function Prototypes */
void stageOne(DictEntryType *dictEntry, int *numEntries);
void stageTwo(DictionaryType *dictionary);
void stageThree(ListType *sentence);
void stageFour(DictionaryType dictionary, ListType sentence);
void stageFive();

int readDictionaryEntry(DictEntryType *dictEntry);
int readIntSequence(int *array, int dim);
void skipLine();


void printHeading(int stagenum);
void printEntry(DictEntryType dictionary[], int index, int dim);
int addToDictionary(DictionaryType *dict, DictEntryType newEntry,
	int maxEntries);
int readInputToList(ListType *list);
void printList(ListType *list);




/* this is where the fun begins */
int main(int argc, char *argv[]) {
	
	DictionaryType dictionary;
	dictionary.numEntries = 0;
	ListType *sentence = createList();

	/* this IS where the fun begins */
	stageOne(dictionary.entries, &dictionary.numEntries);
	stageTwo(&dictionary);
	// stageThree(sentence);
	// stageFour(dictionary, *sentence);
	// stageFive();

	/* HOLY SHIT I MADE IT THIS FAR */
	return 0;
}

/* Stage 1: reading and outputting one dictionary entry */
void stageOne(DictEntryType *dictEntry, int *numEntries){

	printHeading(STAGE_NUM_ONE);
	readDictionaryEntry(dictEntry);
	(*numEntries)++;
	
	printEntry(dictEntry, 0, NUM_WORD_TYPES);
}

void stageTwo(DictionaryType *dictionary){
	
	printHeading(STAGE_NUM_TWO);


	DictEntryType newEntry;
	while(readDictionaryEntry(&newEntry)) {
		addToDictionary(dictionary, newEntry, DICTIONARY_SIZE);
	}

	if (DEBUG) {
		for (int i = 0; i < dictionary->numEntries; i++){
		printEntry(dictionary->entries, i, NUM_WORD_TYPES);
		}
	}

	printf("Number of words: %d\n", dictionary->numEntries);

	/* TODO: Delegate this later */
	int lengths[dictionary->numEntries];
	float total = 0;
	int i;
	for (i = 0; i < dictionary->numEntries; i++) {
		total += (float)dictionary->entries[i].wordLength;
	}

	printf("Average word length: %.2f\n",total/(dictionary->numEntries));
}


void stageThree(ListType *sentence){
	printHeading(STAGE_NUM_THREE);
	sentence->itemCount = 0;

	/* The line containing only %%%% is kind of meaningless so we'll just skip
	it */
	skipLine();
	readInputToList(sentence);
	printList(sentence);
}

void stageFour(DictionaryType dictionary, ListType sentence){
	printHeading(STAGE_NUM_FOUR);
	char *wordTypes[NUM_WORD_TYPES] = {
		WORD_TYPE_0,
		WORD_TYPE_1,
		WORD_TYPE_2
	};

	NodeType *word = sentence.head;
	int wordClassification[NUM_WORD_TYPES];
	while(word != NULL) {
		classify(word->value, wordClassification, 
			&dictionary, NUM_WORD_TYPES);
		printf(" %s \n %d %d %d \n", word->value,
			wordClassification[0],
			wordClassification[1],
			wordClassification[2]);
		word = word->next;
	}
}

void stageFive(){
	printHeading(STAGE_NUM_FIVE);
}


/* FUNCTIONS THAT READ USER INPUT */
int readDictionaryEntry(DictEntryType *dictEntry){
	if (getchar() == '#') {
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
	} else {
		return FAILURE;
	}
}


int readIntSequence(int *array, int dim){
	int i;
	for(i = 0; i < dim+ 1; i++) {
		if(scanf("%d", array + i) != 1) {
			return FAILURE;
		}
	}
	return SUCCESS;
}

void skipLine() {
	char c;
	while (c = getchar()) {
		if (c == '\n' || c == EOF) {
			break;
		}
	}
}

int readInputToList(ListType *list) {
	char c; 
	int i = 0;
	WordType word;
	while ( (c=getchar()) != EOF) {
		if (c == ' ') {
			word[i] = '\0';
			if (DEBUG) {
				printf("[DEBUG] READ: %s \n", word);
			}
			insertAtTail(list, word);
			i = 0;
		} else {
			word[i++] = c;
		}
	}
	insertAtTail(list, word);
	return 1;
}


/* FUNCTIONS THAT DISPLAY OUTPUT */
void printHeading(int stagenum) {
	if (stagenum > 1) printf("\n");
	printf("%s Stage %d %s\n", HEADER_SIDE, stagenum, HEADER_SIDE);
}

void printEntry(DictEntryType dictionary[], int index, int dim) {
	printf("Word %d: %s\n", index, dictionary[index].word);
	printf("Label probabilities: ");
	int i;
	for (i = 0; i < dim; i++) {
		printf("%d%%", dictionary[index].probabilities[i]);
		printf("%c", i == dim - 1 ? '\n' : ' ');
	}
}

void printList(ListType *list){
	NodeType *current = list->head;
	while (current != NULL) {
		printf("%s\n", current->value);
		current = current->next;
	}
}

/* FUNCTIONS THAT DO OTHER STUFF */
int addToDictionary(DictionaryType *dict, DictEntryType newEntry,
	int maxEntries) {
	if (dict->numEntries >= maxEntries) {
		return 0;
	}
	dict->entries[dict->numEntries] = newEntry;
	dict->ordIndex[dict->numEntries] = dict->numEntries;
	int i;
	for (i = dict->numEntries; i > 0; i--) {
		int j1 = dict->ordIndex[i-1];
		int j2 = dict->ordIndex[i];
		if (strcmp(dict->entries[j1].word, dict->entries[j2].word) < 0) {
			int temp;
			temp = dict->ordIndex[i-1];
			dict->ordIndex[i] = dict->ordIndex[i-1];
			dict->ordIndex[i-1] = temp;
		}
	}
	(dict->numEntries)++;
	return 1;	
}

void copyArray(int *src, int  *dest, int dims) {
	int i;
	for (i = 0; i < dims; i++) {
		dest[i] = src[i];
	}
}

void classify(char *word, int *output, DictionaryType *dictionary,
	int numWordTypes) {
	int pos = search(word, dictionary->entries, dictionary->numEntries); 

	if (pos >= 0) {
		copyArray(dictionary->entries->probabilities,
			output, NUM_WORD_TYPES);
	} else {

	}
}

int search(char *str, DictEntryType entries[], int itemCount) {
	/* TODO: CHANGE THIS TO BINARY SEARCH LATER */
	int i;
	for (i = 0; i < itemCount; i++) {
		if (strcmp(str, entries[i].word) == 0) {
			return i;
		}
	}
	return -1;
}

