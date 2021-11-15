#ifndef _CDH_h
#define _CDH_h

#include <stdint.h>
#include "CR.h"

typedef struct CDH* CDHTUPLE;

typedef CDHTUPLE CDHTABLE[1009];

extern CDHTUPLE new_CDHTUPLE(char course[5], char day[2], char hour[4]);

extern void CDHInsert(CDHTUPLE tuple, CDHTABLE table);

extern void CDHDelete(CDHTUPLE tuple, CDHTABLE table);

extern void CDHdelete(CDHTUPLE tuple, CDHTABLE table, int hash);

extern void CDHLookup(CDHTUPLE tuple, CDHTABLE table, CDHTUPLE set[1009]);

extern void CDHlookup(CDHTUPLE tuple, CDHTABLE table, int hash, CDHTUPLE set[1009]);

extern void printCDHInfo(CDHTUPLE tuple);

extern void printCDHTable(CDHTABLE table);

extern void printCDHLookup(CDHTUPLE set[1009]);

extern int CDHh(char x[32]);

extern char* CDHcourseFinder(CDHTABLE CDHtable, CRTABLE CRtable, char* courseList[50], char hour[4], char day[2]);

#endif