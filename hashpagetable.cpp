#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#define MAXLINE 80 /* The maximum length command */
#define MAXARGS 20 /* The maximum number of arguments */

// Hash page table entry structure
struct hashPageTableEntry {
    int pageNumber;
    int frameNumber;
    struct hashPageTableEntry *next;
};

// Hash page table structure
struct hashPageTable {
    struct hashPageTableEntry *hashPageTableEntry[MAXARGS];
};

// Creating a hash page table entry
struct hashPageTableEntry *createHashPageTableEntry(int pageNumber, int frameNumber) {
    struct hashPageTableEntry *newHashPageTableEntry = (struct hashPageTableEntry *)malloc(sizeof(struct hashPageTableEntry));
    newHashPageTableEntry->pageNumber = pageNumber;
    newHashPageTableEntry->frameNumber = frameNumber;
    newHashPageTableEntry->next = NULL;
    return newHashPageTableEntry;
}

// Creating a hash page table
struct hashPageTable *createHashPageTable() {
    struct hashPageTable *newHashPageTable = (struct hashPageTable *)malloc(sizeof(struct hashPageTable));
    int i;
    for (i = 0; i < MAXARGS; i++) {
        newHashPageTable->hashPageTableEntry[i] = NULL;
    }
    return newHashPageTable;
}

// Inserting a hash page table entry into the hash page table
void insertHashPageTableEntry(struct hashPageTable *hashPageTable, int pageNumber, int frameNumber) {
    int hashIndex = pageNumber % MAXARGS;
    struct hashPageTableEntry *newHashPageTableEntry = createHashPageTableEntry(pageNumber, frameNumber);
    if (hashPageTable->hashPageTableEntry[hashIndex] == NULL) {
        hashPageTable->hashPageTableEntry[hashIndex] = newHashPageTableEntry;
    } else {
        struct hashPageTableEntry *currentHashPageTableEntry = hashPageTable->hashPageTableEntry[hashIndex];
        while (currentHashPageTableEntry->next != NULL) {
            currentHashPageTableEntry = currentHashPageTableEntry->next;
        }
        currentHashPageTableEntry->next = newHashPageTableEntry;
    }
}

// Searching for a hash page table entry in the hash page table
int searchHashPageTableEntry(struct hashPageTable *hashPageTable, int pageNumber) {
    int hashIndex = pageNumber % MAXARGS;
    struct hashPageTableEntry *currentHashPageTableEntry = hashPageTable->hashPageTableEntry[hashIndex];
    while (currentHashPageTableEntry != NULL) {
        if (currentHashPageTableEntry->pageNumber == pageNumber) {
            return currentHashPageTableEntry->frameNumber;
        }
        currentHashPageTableEntry = currentHashPageTableEntry->next;
    }
    return -1;
}

// Printing the hash page table
void printHashPageTable(struct hashPageTable *hashPageTable) {
    int i;
    for (i = 0; i < MAXARGS; i++) {
        if (hashPageTable->hashPageTableEntry[i] != NULL) {
            struct hashPageTableEntry *currentHashPageTableEntry = hashPageTable->hashPageTableEntry[i];
            while (currentHashPageTableEntry != NULL) {
                printf("Page number: %d, Frame number: %d -> ", currentHashPageTableEntry->pageNumber, currentHashPageTableEntry->frameNumber); 
                currentHashPageTableEntry = currentHashPageTableEntry->next;
            }
            printf("NULL");
            printf(" (Hash index: %d)", i);
            printf("\n");

        }

    }
}

int main(int argc, char *argv[]) {
    // Creating a hash page table
    struct hashPageTable *hashPageTable = createHashPageTable();

    // Insert hash page table entries into the hash page table
    insertHashPageTableEntry(hashPageTable, 40, 20);
    insertHashPageTableEntry(hashPageTable, 2, 2);
    insertHashPageTableEntry(hashPageTable, 15, 15);
    insertHashPageTableEntry(hashPageTable, 4, 4);
    insertHashPageTableEntry(hashPageTable, 5, 5);
    insertHashPageTableEntry(hashPageTable, 20, 20);
    insertHashPageTableEntry(hashPageTable, 7, 7);
    insertHashPageTableEntry(hashPageTable, 13, 8);
    insertHashPageTableEntry(hashPageTable, 9, 9);
    insertHashPageTableEntry(hashPageTable, 10, 10);

    // Print the hash page table
    printf("Hash page table: \n\n");
    printf("(Hash page table size: %d)", MAXARGS);
    printf("\n"); 
    printf("\n"); 
    printHashPageTable(hashPageTable);
    
    // Search for a hash page table entry in the hash page table
    int pageNumber = 3;
    int frameNumber = searchHashPageTableEntry(hashPageTable, pageNumber);
    if (frameNumber != -1) {
        printf("(Page number: %d, Frame number: %d)", pageNumber, frameNumber);
    } 
    else {
        printf("\n"); 
        printf("Frame number not found for page number: %d", pageNumber);
        printf("\n");
    }
    //printf(" (Hash index: %d)", pageNumber % MAXARGS);
    

    return 0;
}
