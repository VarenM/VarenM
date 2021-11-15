#include <stdio.h>
#include "CSG.h"
#include "SNAP.h"
#include "CP.h"
#include "CDH.h"
#include "CR.h"

void loadDatabase(CSGTABLE CSGtable, SNAPTABLE SNAPtable, CPTABLE CPtable, CDHTABLE CDHtable, CRTABLE CRtable)
{
    for(int i = 0; i < 1009; i++)
    {
        CSGtable[i] = NULL;
        SNAPtable[i] = NULL;
        CPtable[i] = NULL;
        CDHtable[i] = NULL;
        CRtable[i] = NULL;
    }

    //CREATION OF Course-StudentID-Grade RELATION:
    CSGTUPLE CSGTuple = new_CSGTUPLE("CS101", "12345", "A");
    CSGTUPLE CSGTuple2 = new_CSGTUPLE("CS101", "67890", "B");
    CSGTUPLE CSGTuple3 = new_CSGTUPLE("EE200", "12345", "C");
    CSGTUPLE CSGTuple4 = new_CSGTUPLE("EE200", "22222", "B+");
    CSGTUPLE CSGTuple5 = new_CSGTUPLE("CS101", "33333", "A-");
    CSGTUPLE CSGTuple6 = new_CSGTUPLE("PH100", "67890", "C+");

    CSGInsert(CSGTuple, CSGtable);
    CSGInsert(CSGTuple2, CSGtable);
    CSGInsert(CSGTuple3, CSGtable);
    CSGInsert(CSGTuple4, CSGtable);
    CSGInsert(CSGTuple5, CSGtable);
    CSGInsert(CSGTuple6, CSGtable);

    printf("CSG Relations:\n");
    printCSGTable(CSGtable);
    printf("\n");


    //CREATION OF StudentID-Name-Address-Phone# RELATION:
    SNAPTUPLE SNAPTuple = new_SNAPTUPLE("12345", "C. Brown", "12 Apple St.", "555-1234");
    SNAPTUPLE SNAPTuple2 = new_SNAPTUPLE("67890", "L. Van Pelt", "34 Pear Ave.", "555-5678");
    SNAPTUPLE SNAPTuple3 = new_SNAPTUPLE("22222", "P. Patty", "56 Grape Blvd.", "555-9999");

    SNAPInsert(SNAPTuple, SNAPtable);
    SNAPInsert(SNAPTuple2, SNAPtable);
    SNAPInsert(SNAPTuple3, SNAPtable);

    printf("SNAP Relations:\n");
    printSNAPTable(SNAPtable);
    printf("\n");


    //CREATION OF Course-PreReq RELATION:
    CPTUPLE CPTuple = new_CPTUPLE("CS101", "CS100");
    CPTUPLE CPTuple2 = new_CPTUPLE("EE200", "EE005");
    CPTUPLE CPTuple3 = new_CPTUPLE("EE200", "CS100");
    CPTUPLE CPTuple4 = new_CPTUPLE("CS120", "CS101");
    CPTUPLE CPTuple5 = new_CPTUPLE("CS121", "CS120");
    CPTUPLE CPTuple6 = new_CPTUPLE("CS205", "CS101");
    CPTUPLE CPTuple7 = new_CPTUPLE("CS206", "CS121");
    CPTUPLE CPTuple8 = new_CPTUPLE("CS206", "CS205");

    CPInsert(CPTuple, CPtable);
    CPInsert(CPTuple2, CPtable);
    CPInsert(CPTuple3, CPtable);
    CPInsert(CPTuple4, CPtable);
    CPInsert(CPTuple5, CPtable);
    CPInsert(CPTuple6, CPtable);
    CPInsert(CPTuple7, CPtable);
    CPInsert(CPTuple8, CPtable);

    printf("CP Relations:\n");
    printCPTable(CPtable);
    printf("\n");


    //CREATION OF Course-Day-Hour RELATION:
    CDHTUPLE CDHTuple = new_CDHTUPLE("CS101", "M", "9AM");
    CDHTUPLE CDHTuple2 = new_CDHTUPLE("CS101", "W", "9AM");
    CDHTUPLE CDHTuple3 = new_CDHTUPLE("CS101", "F", "9AM");
    CDHTUPLE CDHTuple4 = new_CDHTUPLE("EE200", "Tu", "10AM");
    CDHTUPLE CDHTuple5 = new_CDHTUPLE("EE200", "W", "1PM");
    CDHTUPLE CDHTuple6 = new_CDHTUPLE("EE200", "Th", "10AM");

    CDHInsert(CDHTuple, CDHtable);
    CDHInsert(CDHTuple2, CDHtable);
    CDHInsert(CDHTuple3, CDHtable);
    CDHInsert(CDHTuple4, CDHtable);
    CDHInsert(CDHTuple5, CDHtable);
    CDHInsert(CDHTuple6, CDHtable);

    printf("CDH Relations:\n");
    printCDHTable(CDHtable);
    printf("\n");


    //CREATION OF Course-Room RELATION:
    CRTUPLE CRTuple = new_CRTUPLE("CS101", "Turing Aud.");
    CRTUPLE CRTuple2 = new_CRTUPLE("EE200", "25 Ohm Hall");
    CRTUPLE CRTuple3 = new_CRTUPLE("PH100", "Newton Lab");

    CRInsert(CRTuple, CRtable);
    CRInsert(CRTuple2, CRtable);
    CRInsert(CRTuple3, CRtable);

    printf("CR Relations:\n");
    printCRTable(CRtable);
    printf("\n");
}

int main(int argc, char* argv[])
{
    CSGTABLE CSGtable;
    SNAPTABLE SNAPtable;
    CPTABLE CPtable;
    CDHTABLE CDHtable;
    CRTABLE CRtable;

    loadDatabase(CSGtable, SNAPtable, CPtable, CDHtable, CRtable);


    //Basic Operations from Book (Example 8.2 pg. 409)
    CSGTUPLE lookupCSGTuple = new_CSGTUPLE("CS101", "12345", "*");
    CSGTUPLE CSGLookupSet[1009];
    CSGLookup(lookupCSGTuple, CSGtable, CSGLookupSet);
    printf("searching for studentID 12345's grade in class CS101...\n");
    printCSGLookup(CSGLookupSet);
    printf("\n");

    CPTUPLE lookupCPTuple = new_CPTUPLE("CS205", "CS120");
    CPTUPLE CPLookupSet[1009];
    CPLookup(lookupCPTuple, CPtable, CPLookupSet);
    printf("searching for tuple class CS205 with pre-req CS120 in Course-PreReq relation...\n");
    printCPLookup(CPLookupSet);
    printf("\n");

    printf("before deletion of CS101 in the Course-Room relation:\n");
    printCRTable(CRtable);
    CRTUPLE deleteCRTuple = new_CRTUPLE("CS101", "*");
    CRDelete(deleteCRTuple, CRtable);
    printf("after deletion of CS101 in the Course-Room relation:\n");
    printCRTable(CRtable);
    printf("\n");

    printf("before insertion of CS205 with pre-req CS120 in the Course-PreReq relation:\n");
    printCPTable(CPtable);
    CPTUPLE insertCPTuple = new_CPTUPLE("CS205", "CS120");
    CPInsert(insertCPTuple, CPtable);
    printf("after insertion of CS205 with pre-req CS120 in the Course-PreReq relation:\n");
    printCPTable(CPtable);
    printf("\n");

    printf("before insertion of CS205 with pre-req CS101 in the Course-PreReq relation:\n");
    printCPTable(CPtable);
    CPTUPLE insertCPTuple2 = new_CPTUPLE("CS205", "CS101");
    CPInsert(insertCPTuple2, CPtable);
    printf("after insertion of CS205 with pre-req CS101 in the Course-PreReq relation:\n");
    printCPTable(CPtable);
    printf("\n");

    printf("END OF PART 1\n\n");

    loadDatabase(CSGtable, SNAPtable, CPtable, CDHtable, CRtable);

    char* gradeName = "C. Brown";
    char* gradeCourse = "EE200";

    char* whereName = "P. Patty";
    char* whereHour = "10AM";
    char* whereDay = "Tu";

    printf("starting up grade finder...\n");

    // printf("Enter a course: ");
    // scanf("%s", course);

    // printf("Enter a name: ");
    // scanf(" %[^\n]s", name);

    if(idFinder(SNAPtable, CSGtable, CDHtable, CRtable, gradeName, gradeCourse, whereHour, whereDay, 0) != NULL)
    {
        printf("%s's grade in %s is: %s\n", gradeName, gradeCourse, idFinder(SNAPtable, CSGtable, CDHtable, CRtable, gradeName, gradeCourse, whereHour, whereDay, 0));
    }
    else
    {
        printf("could not find %s's grade in %s...\n", gradeName, gradeCourse);
    }

    if(idFinder(SNAPtable, CSGtable, CDHtable, CRtable, whereName, gradeCourse, whereHour, whereDay, 1) != NULL)
    {
        printf("%s is in %s at %s on %s\n", whereName, idFinder(SNAPtable, CSGtable, CDHtable, CRtable, whereName, gradeCourse, whereHour, whereDay, 1), whereHour, whereDay);
    }
    else
    {
        printf("could not find where %s is at %s on %s...\n", whereName, whereHour, whereDay);
    }


    printf("\nEND OF PART 2\n\n");


    printf("done.");
}
