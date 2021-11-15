#ifndef _CSG_h
#define _CSG_h

#include <stdint.h>
#include "CDH.h"
#include "CR.h"

typedef struct CSG* CSGTUPLE;

typedef CSGTUPLE CSGTABLE[1009];

extern CSGTUPLE new_CSGTUPLE(char course[5], char ID[5], char grade[2]);

extern void CSGInsert(CSGTUPLE tuple, CSGTABLE table);

extern void CSGDelete(CSGTUPLE tuple, CSGTABLE table);

extern void CSGdelete(CSGTUPLE tuple, CSGTABLE table, int hash);

extern void CSGLookup(CSGTUPLE tuple, CSGTABLE table, CSGTUPLE set[1009]);

extern void CSGlookup(CSGTUPLE tuple, CSGTABLE table, int hash, CSGTUPLE set[1009]);

extern void printCSGInfo(CSGTUPLE tuple);

extern void printCSGTable(CSGTABLE table);

extern void printCSGLookup(CSGTUPLE set[1009]);

extern int CSGh(char x[32]);

extern char* gradeFinder(CSGTABLE table, char name[32], char course[5]);

extern char* CSGcourseFinder(CSGTABLE table, CDHTABLE CDHtable, CRTABLE CRtable, char hour[4], char day[2], char id[5]);

#endif
