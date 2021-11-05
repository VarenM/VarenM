#include <string.h>
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef char ETYPE[32];
typedef struct CSG *CSGTUPLE;
struct CSG
{
    int studentID;
    char* course;
    char* grade;
    CSGTUPLE next;
};
typedef CSGTUPLE CSGTABLE[1009];

CSGTUPLE new_CSGTUPLE(int ID, char course[5], char grade[2])
{
    CSGTUPLE newTuple = (CSGTUPLE) malloc(sizeof(CSGTUPLE));

    newTuple->studentID = ID;
    newTuple->course = course;
    newTuple->grade = grade;
    newTuple->next = NULL;

    return newTuple;
}

typedef struct SNAP *SNAPTUPLE;
struct SNAP
{
    int studentID;
    char name[30];
    char address[50];
    char phone[8];
    SNAPTUPLE next;
};
typedef SNAPTUPLE SNAPTABLE[1009];

// int h(ETYPE x)
// {
//     int i, sum;
//     sum = 0;
//     for (i = 0; x[i] != '\0'; i++) { sum += x[i]; }
//     return sum % 1009;
// }

int hash(int x)
{
    return x % 1009;
}

// void bucketInsert(ETYPE x, CSGTUPLE *pL)
// {
//     if ((*pL) == NULL)
//     {
//         (*pL) = (CSGTUPLE) malloc(sizeof(struct CSG));
//         strcpy((*pL)->studentID, x);
//         (*pL)->next = NULL;
//     }
//     else if (strcmp((*pL)->studentID, x)) /* x and element are different */
//     {
//         bucketInsert(x, &((*pL)->next));
//     }
// }

void CSGInsert(CSGTUPLE tuple, CSGTABLE table)
{
    int xHash = hash(tuple->studentID);
    printf("inserting student: %d\n", tuple->studentID);

    if(table[xHash] == NULL)
    {
        table[xHash] = tuple;
    }
    else
    {
        printf("table entry was full for student: %d\n", tuple->studentID);
        CSGTUPLE curr = table[xHash];
        printf("current entry: %d\n", curr->studentID);
        while(curr != NULL)
        {
            curr = curr->next;
            if(curr == NULL) { printf("curr is NULL\n"); }
            else { printf("current entry: %d\n", curr->studentID); }
        }
        curr = tuple;
    }
}

// void insert(ETYPE x, CSGTABLE H)
// {
//     bucketInsert(x, &(H[h(x)]));
// }

// int lookupBucket(ETYPE a, CSGTUPLE L)
// {
//     if (L == NULL) { return 0; }
//     if (!strcmp(a, L->studentID)) { return 1; }
//     else { return lookupBucket(a, L->next); }
// }
// int lookup(ETYPE a, CSGTABLE H)
// {
//     return lookupBucket(a, H[h(a)]);
// }

int main(int argc, char* argv[])
{
    CSGTABLE testTable;
    CSGTUPLE testTuple = new_CSGTUPLE(919, "GB101", "A+");
    CSGTUPLE testTuple2 = new_CSGTUPLE(1928, "GB102", "A-");

    //printf("%d", hash(19));

    CSGInsert(testTuple, testTable);
    printf("%d\n", testTable[hash(919)]->studentID);
    CSGInsert(testTuple2, testTable);
    printf("done");
    //printf("%d\n", testTable[hash(1928)]->studentID);
}