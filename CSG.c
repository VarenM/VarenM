#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CSG.h"

int CSGcounter = 0;

struct CSG
{
    char* studentID;
    char* course;
    char* grade;
    CSGTUPLE next;
};

CSGTUPLE new_CSGTUPLE(char course[5], char ID[5], char grade[2])
{
    CSGTUPLE newTuple = (CSGTUPLE) malloc(sizeof(struct CSG));

    newTuple->studentID = ID;
    newTuple->course = course;
    newTuple->grade = grade;
    newTuple->next = NULL;

    return newTuple;
}

int CSGh(char x[32])
{
    int i, sum;
    sum = 0;
    for (i = 0; x[i] != '\0'; i++) { sum += x[i]; }
    return sum % 1009;
}

void CSGInsert(CSGTUPLE tuple, CSGTABLE table)
{
    int hash = CSGh(tuple->studentID);
    // printf("inserting student: ");
    // printCSGInfo(tuple);
    // printf("\n");

    if(table[hash] == NULL)
    {
        table[hash] = tuple;
    }
    else
    {
        int bool = 0;
        CSGTUPLE curr = table[hash];

        if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->studentID, curr->studentID) == 0 && strcmp(tuple->grade, curr->grade) == 0)
        {
            bool = 1;
        }
        while(curr->next != NULL)
        {
            if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->studentID, curr->studentID) == 0 && strcmp(tuple->grade, curr->grade) == 0)
            {
                bool = 1;
            }
            curr = curr->next;
        }
        if(bool == 0) { curr->next = tuple; }
    }
    // printf("successfully added student: ");
    // printCSGInfo(tuple);
    // printf("\n");
}

void CSGDelete(CSGTUPLE tuple, CSGTABLE table)
{
    if(strcmp(tuple->studentID, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CSGdelete(tuple, table, i);
        }
    }
    else
    {
        int hash = CSGh(tuple->studentID);
        CSGdelete(tuple, table, hash);
    }
    //printf("finished deletion.\n");
}

void CSGdelete(CSGTUPLE tuple, CSGTABLE table, int hash)
{
    if(table[hash] != NULL)
    {
        CSGTUPLE before = NULL;
        CSGTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->studentID, curr->studentID) == 0 || 
            strcmp(tuple->studentID, "*") == 0) && (strcmp(tuple->grade, curr->grade) == 0 || strcmp(tuple->grade, "*") == 0))
            {
                if(before == NULL)
                {
                    table[hash] = curr->next;
                    //CSGTUPLE temp = curr;
                    curr = curr->next;
                    //free(temp);
                }
                else
                {
                    before->next = curr->next;

                    //CSGTUPLE temp = curr;
                    curr = curr->next;
                    //free(temp);
                }
            }
            else
            {
                before = curr;
                //CSGTUPLE temp = curr;
                curr = curr->next;
                //free(temp);
            }
        }
    }
}

void CSGLookup(CSGTUPLE tuple, CSGTABLE table, CSGTUPLE set[1009])
{
    CSGcounter = 0;
    if(strcmp(tuple->studentID, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CSGlookup(tuple, table, i, set);
        }
    }
    else
    {
        int hash = CSGh(tuple->studentID);
        CSGlookup(tuple, table, hash, set);
    }
    //printf("finished lookup.\n");
}

void CSGlookup(CSGTUPLE tuple, CSGTABLE table, int hash, CSGTUPLE set[1009])
{
    if(table[hash] != NULL)
    {
        CSGTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->studentID, curr->studentID) == 0 || strcmp(tuple->studentID, "*") == 0) && (strcmp(tuple->grade, curr->grade) == 0 || strcmp(tuple->grade, "*") == 0))
            {
                set[CSGcounter] = curr;
                CSGcounter++;
                curr = curr->next;
            }
            else
            {
                //CSGTUPLE temp = curr;
                curr = curr->next;
                //free(temp);
            }
        }
    }
}

void printCSGInfo(CSGTUPLE tuple)
{
    if(tuple != NULL) { printf("course: %s, id: %s, grade: %s", tuple->course, tuple->studentID, tuple->grade); }
    else { printf("tuple is null"); }
}

void printCSGTable(CSGTABLE table)
{
    for(int i = 0; i < 1009; i++)
    {
        if(table[i] != NULL)
        {            
            CSGTUPLE curr = table[i];
            while(curr != NULL)
            {
                printCSGInfo(curr);
                curr = curr->next;
                printf("  ->  ");
            }
            printf("\n");
        }
    }
}

void printCSGLookup(CSGTUPLE set[1009])
{
    int bool = 0;
    for(int i = 0; i < 1009; i++)
    {
        if(set[i] != NULL)
        {            
            printCSGInfo(set[i]);
            printf("\n");
            bool = 1;
        }
    }
    if(bool == 0)
    {
        printf("could not find matching tuple in set.\n");
    }
}

char* gradeFinder(CSGTABLE table, char id[5], char course[5])
{
    if(table[CSGh(id)] != NULL)
    {
        CSGTUPLE curr = table[CSGh(id)];
        while(curr != NULL)
        {
            if(strcmp(curr->course, course) == 0 && strcmp(curr->studentID, id) == 0)
            {
                return curr->grade;
            }
            else
            {
                curr = curr->next;
            }
        }
    }
    return NULL;
}

char* CSGcourseFinder(CSGTABLE table, CDHTABLE CDHtable, CRTABLE CRtable, char hour[4], char day[2], char id[5])
{
    char* courseList[50];
    int counter = 0;
    if(table[CSGh(id)] != NULL)
    {
        CSGTUPLE curr = table[CSGh(id)];
        while(curr != NULL)
        {
            courseList[counter] = curr->course;
            counter++;
            curr = curr->next;
        }
        return CDHcourseFinder(CDHtable, CRtable, courseList, hour, day);
    }
    return NULL;
}
