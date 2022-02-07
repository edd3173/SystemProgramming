#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MEMLEN 1048576
#define MAX_LEN 128
#define MAX 128
#include <dirent.h>

unsigned char MM[MEMLEN] = { 0, };
int currentAddress = 0;
int programFlag = 1;
char cmd[20] = { '\0', };
int historyCount = 1;

typedef struct _HistoryNode {
	struct _HistoryNode* next;
	char command[20];
	int count;
}HistoryNode;

HistoryNode* Head = NULL;


char number[4] = { '\0', };
char command[8] = { '\0', };
char argvs[4] = { '\0', };
int collisionCount = 0;

typedef struct _HashNode {
	char* value; // since hex form
	char* key; // add, jeq 
	struct _HashNode* next;
}HashNode;

typedef HashNode* List;

typedef struct _HashTable {
	int TableSize;
	List* Table;
}HashTable;

HashTable* HT;


