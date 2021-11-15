#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CP.h"

int CPcounter = 0;

struct CP
{
    char* pre;
    char* course;
    CPTUPLE next;
};

CPTUPLE new_CPTUPLE(char course[5], char pre[5])
{
    CPTUPLE newTuple = (CPTUPLE) malloc(sizeof(struct CP));

    newTuple->pre = pre;
    newTuple->course = course;
    newTuple->next = NULL;

    return newTuple;
}


int CPh(char x[32])
{
    int i, sum;
    sum = 0;
    for (i = 0; x[i] != '\0'; i++) { sum += x[i]; }
    return sum % 1009;
}

void CPInsert(CPTUPLE tuple, CPTABLE table)
{
    int hash = CPh(tuple->course);
    // printf("inserting course: ");
    // printCPInfo(tuple);
    // printf("\n");

    if(table[hash] == NULL)
    {
        table[hash] = tuple;
    }
    else
    {
        int bool = 0;
        CPTUPLE curr = table[hash];

        if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->pre, curr->pre) == 0)
        {
            bool = 1;
        }
        while(curr->next != NULL)
        {
            if(strcmp(tuple->course, curr->course) == 0 && strcmp(tuple->pre, curr->pre) == 0)
            {
                bool = 1;
            }
            curr = curr->next;
        }
        if(bool == 0) { curr->next = tuple; }
    }
    // printf("successfully added course: ");
    // printCPInfo(tuple);
    // printf("\n");
}

void CPDelete(CPTUPLE tuple, CPTABLE table)
{
    if(strcmp(tuple->course, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CPdelete(tuple, table, i);
        }
    }
    else
    {
        int hash = CPh(tuple->course);
        CPdelete(tuple, table, hash);
    }
    //printf("finished deletion.\n");
}

void CPdelete(CPTUPLE tuple, CPTABLE table, int hash)
{
    if(table[hash] != NULL)
    {
        CPTUPLE before = NULL;
        CPTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->pre, curr->pre) == 0 || strcmp(tuple->pre, "*") == 0))
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

void CPLookup(CPTUPLE tuple, CPTABLE table, CPTUPLE set[1009])
{
    CPcounter = 0;
    if(strcmp(tuple->course, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            CPlookup(tuple, table, i, set);
        }
    }
    else
    {
        int hash = CPh(tuple->course);
        CPlookup(tuple, table, hash, set);
    }
    //printf("finished lookup.\n");
}

void CPlookup(CPTUPLE tuple, CPTABLE table, int hash, CPTUPLE set[1009])
{
    if(table[hash] != NULL)
    {
        CPTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->course, curr->course) == 0 || strcmp(tuple->course, "*") == 0) && (strcmp(tuple->pre, curr->pre) == 0 || strcmp(tuple->pre, "*") == 0))
            {
                set[CPcounter] = curr;
                CPcounter++;
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

void printCPInfo(CPTUPLE tuple)
{
    if(tuple != NULL) { printf("course: %s, pre: %s", tuple->course, tuple->pre); }
    else { printf("tuple is null"); }
}

void printCPTable(CPTABLE table)
{
    for(int i = 0; i < 1009; i++)
    {
        if(table[i] != NULL)
        {
            CPTUPLE curr = table[i];
            while(curr != NULL)
            {
                printCPInfo(curr);
                curr = curr->next;
                printf("  ->  ");
            }
            printf("\n");
        }
    }
}

void printCPLookup(CPTUPLE set[1009])
{
    int bool = 0;
    for(int i = 0; i < 1009; i++)
    {
        if(set[i] != NULL)
        {
            printCPInfo(set[i]);
            printf("\n");
            bool = 1;
        }
    }
    if(bool == 0)
    {
        printf("could not find matching tuple in set.\n");
    }
}