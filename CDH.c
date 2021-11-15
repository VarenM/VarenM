#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CDH.h"

int CDHcounter = 0;

struct CDH
{
    char* course;
    char* day;
    char* hour;
    CDHTUPLE next;
};

CDHTUPLE new_CDHTUPLE(char course[5], char day[2], char hour[4])
{
    CDHTUPLE newTuple = (CDHTUPLE) malloc(sizeof(struct CDH));

    newTuple->course = course;
    newTuple->day = day;
    newTuple->hour = hour;
    newTuple->next = NULL;

    return newTuple;
}

int CDHh(char x[32])
{
    int i, sum;
    sum = 0;
    for (i = 0; x[i] != '\0'; i++) { sum += x[i]; }
    return sum % 1009;
}

void CDHInsert(CDHTUPLE tuple, CDHTABLE table)
{
    int hash = CDHh(tuple->course);
    // printf("inserting course: ");
    // printCDHInfo(tuple);
    // printf("\n");

    if(table[hash] == NULL)
    {
        table[hash] = tuple;
    }
    else
    {
        int bool = 0;
        CDHTUPLE curr = table[hash];

        if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->day, curr->day) == 0 && strcmp(tuple->hour, curr->hour) == 0)
        {
            bool = 1;
        }
        while(curr->next != NULL)
        {
            if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->day, curr->day) == 0 && strcmp(tuple->hour, curr->hour) == 0)
            {
                bool = 1;
            }
            curr = curr->next;
        }
        if(bool == 0) { curr->next = tuple; }
    }
    // printf("successfully added course: ");
    // printCDHInfo(tuple);
    // printf("\n");
}

void CDHDelete(CDHTUPLE tuple, CDHTABLE table)
{
    if(strcmp(tuple->course, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CDHdelete(tuple, table, i);
        }
    }
    else
    {
        int hash = CDHh(tuple->course);
        CDHdelete(tuple, table, hash);
    }
    //printf("finished deletion.\n");
}

void CDHdelete(CDHTUPLE tuple, CDHTABLE table, int hash)
{
    if(table[hash] != NULL)
    {
        CDHTUPLE before = NULL;
        CDHTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->day, curr->day) == 0 || 
            strcmp(tuple->day, "*") == 0) && (strcmp(tuple->hour, curr->hour) == 0 || strcmp(tuple->hour, "*") == 0))
            {
                if(before == NULL)
                {
                    table[hash] = curr->next;
                    //CDHTUPLE temp = curr;
                    curr = curr->next;
                    //free(temp);
                }
                else
                {
                    before->next = curr->next;

                    //CDHTUPLE temp = curr;
                    curr = curr->next;
                    //free(temp);
                }
            }
            else
            {
                before = curr;
                //CDHTUPLE temp = curr;
                curr = curr->next;
                //free(temp);
            }
        }
    }
}

void CDHLookup(CDHTUPLE tuple, CDHTABLE table, CDHTUPLE set[1009])
{
    CDHcounter = 0;
    if(strcmp(tuple->course, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CDHlookup(tuple, table, i, set);
        }
    }
    else
    {
        int hash = CDHh(tuple->course);
        CDHlookup(tuple, table, hash, set);
    }
    //printf("finished lookup.\n");
}

void CDHlookup(CDHTUPLE tuple, CDHTABLE table, int hash, CDHTUPLE set[1009])
{
    if(table[hash] != NULL)
    {
        CDHTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->day, curr->day) == 0 || 
            strcmp(tuple->day, "*") == 0) && (strcmp(tuple->hour, curr->hour) == 0 || strcmp(tuple->hour, "*") == 0))
            {
                set[CDHcounter] = curr;
                CDHcounter++;
                curr = curr->next;
            }
            else
            {
                //CDHTUPLE temp = curr;
                curr = curr->next;
                //free(temp);
            }
        }
    }
}

void printCDHInfo(CDHTUPLE tuple)
{
    if(tuple != NULL) { printf("course: %s, day: %s, hour: %s", tuple->course, tuple->day, tuple->hour); }
    else { printf("tuple is null"); }
}

void printCDHTable(CDHTABLE table)
{
    for(int i = 0; i < 1009; i++)
    {
        if(table[i] != NULL)
        {            
            CDHTUPLE curr = table[i];
            while(curr != NULL)
            {
                printCDHInfo(curr);
                curr = curr->next;
                printf("  ->  ");
            }
            printf("\n");
        }
    }
}

void printCDHLookup(CDHTUPLE set[1009])
{
    int bool = 0;
    for(int i = 0; i < 1009; i++)
    {
        if(set[i] != NULL)
        {            
            printCDHInfo(set[i]);
            printf("\n");
            bool = 1;
        }
    }
    if(bool == 0)
    {
        printf("could not find matching tuple in set.\n");
    }
}

char* CDHcourseFinder(CDHTABLE CDHtable, CRTABLE CRtable, char* courseList[50], char hour[4], char day[2])
{
    for(int i = 0; i < 50; i++)
    {
        if(CDHtable[CDHh(courseList[i])] != NULL)
        {
            CDHTUPLE curr = CDHtable[CDHh(courseList[i])];
            while(curr != NULL)
            {
                if(strcmp(curr->hour, hour) == 0 && strcmp(curr->day, day) == 0)
                {
                    return roomFinder(CRtable, curr->course);
                }
                else
                {
                    curr = curr->next;
                }
            }
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}