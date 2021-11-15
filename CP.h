#ifndef _CP_h
#define _CP_h

#include <stdio.h>

typedef struct CP* CPTUPLE;

typedef CPTUPLE CPTABLE[1009];

extern CPTUPLE new_CPTUPLE(char course[5], char pre[5]);

extern void CPInsert(CPTUPLE tuple, CPTABLE Table);

extern void CPDelete(CPTUPLE tuple, CPTABLE Table);

extern void CPdelete(CPTUPLE tuple, CPTABLE table, int hash);

extern void CPLookup(CPTUPLE tuple, CPTABLE table, CPTUPLE set[1009]);

extern void CPlookup(CPTUPLE tuple, CPTABLE table, int hash, CPTUPLE set[1009]);

extern void printCPLookup(CPTUPLE set[1009]);

extern void printCPTable(CPTABLE table);

extern void printCPInfo(CPTUPLE tuple);

extern int CPh(char x[32]);

#endif