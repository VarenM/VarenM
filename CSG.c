#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CSG.h"

struct CSG
{
    char* studentID;
    char* course;
    char* grade;
    CSGTUPLE nextID;
    CSGTUPLE nextCourse;
    CSGTUPLE nextGrade;
};

CSGTUPLE new_CSGTUPLE(char ID[5], char course[5], char grade[2])
{
    CSGTUPLE newTuple = (CSGTUPLE) malloc(sizeof(CSGTUPLE));

    newTuple->studentID = ID;
    newTuple->course = course;
    newTuple->grade = grade;
    newTuple->nextID = NULL;
    newTuple->nextCourse = NULL;
    newTuple->nextGrade = NULL;

    return newTuple;
}

int h(ETYPE x)
{
    int i, sum;
    sum = 0;
    for (i = 0; x[i] != '\0'; i++) { sum += x[i]; }
    return sum % 1009;
}

void CSGInsert(CSGTUPLE tuple, IDTABLE IDTable, COURSETABLE courseTable, GRADETABLE gradeTable)
{
    int IDhash = h(tuple->studentID);
    int courseHash = h(tuple->course);
    printf("inserting student: %s\n", tuple->studentID);

    if(IDTable[IDhash] == NULL)
    {
        IDTable[IDhash] = tuple;
    }
    else
    {
        printf("table entry was full for student: %s\n", tuple->studentID);
        CSGTUPLE curr = IDTable[IDhash];
        printf("current entry: %s\n", curr->studentID);
        while(curr != NULL)
        {
            curr = curr->nextID;
            if(curr == NULL) { printf("curr is NULL\n"); }
            else { printf("current entry: %s\n", curr->studentID); }
        }
        curr = tuple;
    }

    if(courseTable[courseHash] == NULL)
    {
        courseTable[courseHash] = IDTable[IDhash];
    }
    else
    {
        printf("table entry was full for student: %s\n", tuple->studentID);
        CSGTUPLE curr = courseTable[courseHash];
        printf("current entry: %s\n", curr->studentID);
        while(curr != NULL)
        {
            curr = curr->nextID;
            if(curr == NULL) { printf("curr is NULL\n"); }
            else { printf("current entry: %s\n", curr->studentID); }
        }
        curr = tuple;
    }
}

void testInsert(CSGTUPLE tuple, IDTABLE IDTable)
{
    int IDhash = h(tuple->studentID);
    printf("inserting student: %s\n", tuple->studentID);

    if(IDTable[IDhash]->nextID == NULL)
    {
        IDTable[IDhash]->nextID = tuple;
    }
    else
    {
        printf("table entry was full for student: %s\n", tuple->studentID);
        CSGTUPLE curr = IDTable[IDhash];
        printf("current entry: %s\n", curr->studentID);
        while(curr != NULL)
        {
            curr = curr->nextID;
            if(curr == NULL) { printf("curr is NULL\n"); }
            else { printf("current entry: %s\n", curr->studentID); }
        }
        curr = tuple;
    }
}

void printInfo(IDTABLE table)
{
    printf("id: %s, course: %s, grade: %s\n", table[h("919")]->nextID->studentID, table[h("919")]->nextID->course, table[h("919")]->nextID->grade);
}

void printInfo2(IDTABLE table)
{
    printf("id: %s, course: %s, grade: %s\n", table[h("1928")]->studentID, table[h("919")]->course, table[h("919")]->grade);
}