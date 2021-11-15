#ifndef _CR_h
#define _CR_h

#include <stdio.h>

typedef struct CR* CRTUPLE;

typedef CRTUPLE CRTABLE[1009];

extern CRTUPLE new_CRTUPLE(char course[5], char room[32]);

extern void CRInsert(CRTUPLE tuple, CRTABLE Table);

extern void CRDelete(CRTUPLE tuple, CRTABLE Table);

extern void CRdelete(CRTUPLE tuple, CRTABLE table, int hash);

extern void CRLookup(CRTUPLE tuple, CRTABLE table, CRTUPLE set[1009]);

extern void CRlookup(CRTUPLE tuple, CRTABLE table, int hash, CRTUPLE set[1009]);

extern void printCRLookup(CRTUPLE set[1009]);

extern void printCRTable(CRTABLE table);

extern void printCRInfo(CRTUPLE tuple);

extern int CRh(char x[32]);

extern char* roomFinder(CRTABLE table, char* course);

#endif