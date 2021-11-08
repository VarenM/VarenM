#ifndef _CSG_h
#define _CSG_h

#include <stdint.h>

typedef char ETYPE[32];

typedef struct CSG* CSGTUPLE;

typedef CSGTUPLE IDTABLE[1009];
typedef CSGTUPLE COURSETABLE[1009];
typedef CSGTUPLE GRADETABLE[1009];

extern CSGTUPLE new_CSGTUPLE(char ID[5], char course[5], char grade[2]);

extern void CSGInsert(CSGTUPLE tuple, IDTABLE IDTable, COURSETABLE courseTable, GRADETABLE gradeTable);

extern void testInsert(CSGTUPLE tuple, IDTABLE IDTable);

extern void printInfo(IDTABLE table);

extern void printInfo2(IDTABLE table);

#endif