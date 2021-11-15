#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SNAP.h"

int SNAPcounter = 0;

struct SNAP
{
    char* studentID;
    char* name;
    char* addy;
    char* phone;
    SNAPTUPLE next;
};

SNAPTUPLE new_SNAPTUPLE(char ID[5], char name[32], char addy[32], char phone[8])
{
    SNAPTUPLE newTuple = (SNAPTUPLE) malloc(sizeof(struct SNAP));

    newTuple->studentID = ID;
    newTuple->name = name;
    newTuple->addy = addy;
    newTuple->phone = phone;
    newTuple->next = NULL;

    return newTuple;
}

int SNAPh(char x[32])
{
    int i, sum;
    sum = 0;
    for (i = 0; x[i] != '\0'; i++) { sum += x[i]; }
    return sum % 1009;
}

void SNAPInsert(SNAPTUPLE tuple, SNAPTABLE table)
{
    int hash = SNAPh(tuple->studentID);
    // printf("inserting student: ");
    // printSNAPInfo(tuple);
    // printf("\n");

    if(table[hash] == NULL)
    {
        table[hash] = tuple;
    }
    else
    {
        int bool = 0;
        SNAPTUPLE curr = table[hash];

        if(strcmp(tuple->studentID, curr->studentID) == 0 && strcmp(tuple->name, curr->name) == 0 && strcmp(tuple->addy, curr->addy) == 0 && 
        strcmp(tuple->phone, curr->phone) == 0)
        {
            bool = 1;
        }
        while(curr->next != NULL)
        {
            if(strcmp(tuple->studentID, curr->studentID) == 0 && strcmp(tuple->name, curr->name) == 0 && strcmp(tuple->addy, curr->addy) == 0 && 
            strcmp(tuple->phone, curr->phone) == 0)
            {
                bool = 1;
            }
            curr = curr->next;
        }
        if(bool == 0) { curr->next = tuple; }
    }
    // printf("successfully added student: ");
    // printSNAPInfo(tuple);
    // printf("\n");
}

void SNAPDelete(SNAPTUPLE tuple, SNAPTABLE table)
{
    if(strcmp(tuple->studentID, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            SNAPdelete(tuple, table, i);
        }
    }
    else
    {
        int hash = SNAPh(tuple->studentID);
        SNAPdelete(tuple, table, hash);
    }
    //printf("finished deletion.\n");
}

void SNAPdelete(SNAPTUPLE tuple, SNAPTABLE table, int hash)
{
    if(table[hash] != NULL)
    {
        SNAPTUPLE before = NULL;
        SNAPTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->studentID, curr->studentID) == 0 || strcmp(tuple->studentID, "*") == 0) && (strcmp(tuple->name, curr->name) == 0 || 
            strcmp(tuple->name, "*") == 0) && (strcmp(tuple->addy, curr->addy) == 0 || strcmp(tuple->addy, "*") == 0) && (strcmp(tuple->phone, curr->phone) == 0 || strcmp(tuple->phone, "*") == 0))
            {
                if(before == NULL)
                {
                    table[hash] = curr->next;
                    //SNAPTUPLE temp = curr;
                    curr = curr->next;
                    //free(temp);
                }
                else
                {
                    before->next = curr->next;

                    //SNAPTUPLE temp = curr;
                    curr = curr->next;
                    //free(temp);
                }
            }
            else
            {
                before = curr;
                //SNAPTUPLE temp = curr;
                curr = curr->next;
                //free(temp);
            }
        }
    }
}

void SNAPLookup(SNAPTUPLE tuple, SNAPTABLE table, SNAPTUPLE set[1009])
{
    SNAPcounter = 0;
    if(strcmp(tuple->studentID, "*") == 0)
    {
        for(int i = 0; i < 1009; i++)
        {
            SNAPlookup(tuple, table, i, set);
        }
    }
    else
    {
        int hash = SNAPh(tuple->studentID);
        SNAPlookup(tuple, table, hash, set);
    }
    //printf("finished lookup.\n");
}

void SNAPlookup(SNAPTUPLE tuple, SNAPTABLE table, int hash, SNAPTUPLE set[1009])
{
    if(table[hash] != NULL)
    {
        SNAPTUPLE curr = table[hash];
        while(curr != NULL)
        {
            if((strcmp(tuple->studentID, curr->studentID) == 0 || strcmp(tuple->studentID, "*") == 0) && (strcmp(tuple->name, curr->name) == 0 || 
            strcmp(tuple->name, "*") == 0) && (strcmp(tuple->addy, curr->addy) == 0 || strcmp(tuple->addy, "*") == 0) && (strcmp(tuple->phone, curr->phone) == 0 || strcmp(tuple->phone, "*") == 0))
            {
                set[SNAPcounter] = curr;
                SNAPcounter++;
                curr = curr->next;
            }
            else
            {
                //SNAPTUPLE temp = curr;
                curr = curr->next;
                //free(temp);
            }
        }
    }
}

void printSNAPInfo(SNAPTUPLE tuple)
{
    if(tuple != NULL) { printf("id: %s, name: %s, address: %s, phone: %s", tuple->studentID, tuple->name, tuple->addy, tuple->phone); }
    else { printf("tuple is null"); }
}

void printSNAPTable(SNAPTABLE table)
{
    for(int i = 0; i < 1009; i++)
    {
        if(table[i] != NULL)
        {            
            SNAPTUPLE curr = table[i];
            while(curr != NULL)
            {
                printSNAPInfo(curr);
                curr = curr->next;
                printf("  ->  ");
            }
            printf("\n");
        }
    }
}

void printSNAPLookup(SNAPTUPLE set[1009])
{
    int bool = 0;
    for(int i = 0; i < 1009; i++)
    {
        if(set[i] != NULL)
        {            
            printSNAPInfo(set[i]);
            printf("\n");
            bool = 1;
        }
    }
    if(bool == 0)
    {
        printf("could not find matching tuple in set.\n");
    }
}

char* idFinder(SNAPTABLE SNAPtable, CSGTABLE CSGtable, CDHTABLE CDHtable, CRTABLE CRtable, char name[32], char course[5], char hour[4], char day[2], int function)
{
    for(int i = 0; i < 1009; i++)
    {
        if(SNAPtable[i] != NULL)
        {
            if(strcmp(SNAPtable[i]->name, name) == 0)
            {
                char* id = SNAPtable[i]->studentID;
                if(function == 0) { return gradeFinder(CSGtable, id, course); }
                else if(function == 1) { return CSGcourseFinder(CSGtable, CDHtable, CRtable, hour, day, id); }
            }
        }
    }
    return NULL;
}