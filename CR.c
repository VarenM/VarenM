#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CR.h"

int CRcounter = 0;

struct CR
{
    char* room;
    char* course;
    CRTUPLE next;
};

CRTUPLE new_CRTUPLE(char course[5], char room[32])
{
    CRTUPLE newTuple = (CRTUPLE) malloc(sizeof(struct CR));

    newTuple->room = room;
    newTuple->course = course;
    newTuple->next = NULL;

    return newTuple;
}


int CRh(char x[32])
{
    int i, sum;
    sum = 0;
    for (i = 0; x[i] != '\0'; i++) { sum += x[i]; }
    return sum % 1009;
}

void CRInsert(CRTUPLE tuple, CRTABLE table)
{
    int hash = CRh(tuple->course);
    // printf("inserting course: ");
    // printCRInfo(tuple);
    // printf("\n");

    if(table[hash] == NULL)
    {
        table[hash] = tuple;
    }
    else
    {
        int bool = 0;
        CRTUPLE curr = table[hash];

        if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->room, curr->room) == 0)
        {
            bool = 1;
        }
        while(curr->next != NULL)
        {
            if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->room, curr->room) == 0)
            {
                bool = 1;
            }
            curr = curr->next;
        }
        if(bool == 0) { curr->next = tuple; }
    }
    // printf("successfully added course: ");
    // printCRInfo(tuple);
    // printf("\n");
}

void CRDelete(CRTUPLE tuple, CRTABLE table)
{
    if(strcmp(tuple->course, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CRdelete(tuple, table, i);
        }
    }
    else
    {
        int hash = CRh(tuple->course);
        CRdelete(tuple, table, hash);
    }
    //printf("finished deletion.\n");
}

void CRdelete(CRTUPLE tuple, CRTABLE table, int hash)
{
    if(table[hash] != NULL)
    {
        CRTUPLE before = NULL;
        CRTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->room, curr->room) == 0 || strcmp(tuple->room, "*") == 0))
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

void CRLookup(CRTUPLE tuple, CRTABLE table, CRTUPLE set[1009])
{
    CRcounter = 0;
    if(strcmp(tuple->course, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CRlookup(tuple, table, i, set);
        }
    }
    else
    {
        int hash = CRh(tuple->course);
        CRlookup(tuple, table, hash, set);
    }
    //printf("finished lookup.\n");
}

void CRlookup(CRTUPLE tuple, CRTABLE table, int hash, CRTUPLE set[1009])
{
    if(table[hash] != NULL)
    {
        CRTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->room, curr->room) == 0 || strcmp(tuple->room, "*") == 0))
            {
                set[CRcounter] = curr;
                CRcounter++;
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

void printCRInfo(CRTUPLE tuple)
{
    if(tuple != NULL) { printf("course: %s, room: %s", tuple->course, tuple->room); }
    else { printf("tuple is null"); }
}

void printCRTable(CRTABLE table)
{
    for(int i = 0; i < 1009; i++)
    {
        if(table[i] != NULL)
        {
            CRTUPLE curr = table[i];
            while(curr != NULL)
            {
                printCRInfo(curr);
                curr = curr->next;
                printf("  ->  ");
            }
            printf("\n");
        }
    }
}

void printCRLookup(CRTUPLE set[1009])
{
    int bool = 0;
    for(int i = 0; i < 1009; i++)
    {
        if(set[i] != NULL)
        {
            printCRInfo(set[i]);
            printf("\n");
            bool = 1;
        }
    }
    if(bool == 0)
    {
        printf("could not find matching tuple in set.\n");
    }
}

char* roomFinder(CRTABLE table, char* course)
{
    if(table[CRh(course)] != NULL)
    {
        CRTUPLE curr = table[CRh(course)];
        while(curr != NULL)
        {
            if(strcmp(curr->course, course) == 0)
            {
                return curr->room;
            }
            else
            {
                curr = curr->next;
            }
        }
    }
    return NULL;
}