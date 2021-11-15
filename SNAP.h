#ifndef _SNAP_h
#define _SNAP_h

#include <stdint.h>
#include "CSG.h"
#include "CDH.h"
#include "CR.h"

typedef struct SNAP* SNAPTUPLE;

typedef SNAPTUPLE SNAPTABLE[1009];

extern SNAPTUPLE new_SNAPTUPLE(char ID[5], char name[32], char addy[32], char phone[8]);

extern void SNAPInsert(SNAPTUPLE tuple, SNAPTABLE table);

extern void SNAPDelete(SNAPTUPLE tuple, SNAPTABLE table);

extern void SNAPdelete(SNAPTUPLE tuple, SNAPTABLE table, int hash);

extern void SNAPLookup(SNAPTUPLE tuple, SNAPTABLE table, SNAPTUPLE set[1009]);

extern void SNAPlookup(SNAPTUPLE tuple, SNAPTABLE table, int hash, SNAPTUPLE set[1009]);

extern void printSNAPInfo(SNAPTUPLE tuple);

extern void printSNAPTable(SNAPTABLE table);

extern void printSNAPLookup(SNAPTUPLE set[1009]);

extern int SNAPh(char x[32]);

extern char* idFinder(SNAPTABLE SNAPtable, CSGTABLE CSGtable, CDHTABLE CDHtable, CRTABLE CRtable, char name[32], char course[5], char hour[4], char day[2], int function);

#endif