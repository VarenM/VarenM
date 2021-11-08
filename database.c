#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CSG.c"

// void testInsert(CSGTUPLE tuple, IDTABLE IDTable)
// {
//     int IDhash = h(tuple->studentID);
//     printf("inserting student: %s\n", tuple->studentID);

//     if(IDTable[IDhash] == NULL)
//     {
//         IDTable[IDhash] = tuple;
//     }
//     else
//     {
//         printf("table entry was full for student: %s\n", tuple->studentID);
//         CSGTUPLE curr = IDTable[IDhash];
//         printf("current entry: %s\n", curr->studentID);
//         while(curr != NULL)
//         {
//             curr = curr->nextID;
//             if(curr == NULL) { printf("curr is NULL\n"); }
//             else { printf("current entry: %s\n", curr->studentID); }
//         }
//         curr = tuple;
//     }
// }

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
    IDTABLE idTable;
    for(int i = 0; i < 1009; i++)
    {
        idTable[i] = NULL;
    }
    //COURSETABLE courseTable;
    //GRADETABLE gradeTable;

    CSGTUPLE testTuple = new_CSGTUPLE("919", "GB101", "A+");
    //CSGTUPLE testTuple2 = new_CSGTUPLE("1928", "GB102", "A-");

    //printf("%d", hash(19));
    //CSGInsert(testTuple, idTable, courseTable, gradeTable);

    testInsert(testTuple, idTable);
    printInfo(idTable);
    //testInsert(testTuple2, idTable);
    //printInfo2(idTable);

    //CSGInsert(testTuple2, idTable, courseTable, gradeTable);
    printf("done");
    //printf("%d\n", testTable[hash(1928)]->studentID);
}
