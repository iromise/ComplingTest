//definitions.h
#include <fstream>
using namespace std;
#ifndef _definitions_h_
#define _definitions_h_


extern void error(int, int);

#define MaxRes 32
#define MaxNum 9
#define MaxStr 256

#define NumRes 48

#define null NULL
enum symbol {
    nil,                    //1
    ident, num, str, chr,    //4
    constsym, varsym, arraysym, ofsym, intsym, charsym, procsym, funcsym,  //8
    ifsym, thensym, elsesym, whilesym, dosym, forsym, tosym, bysym,     //8
    beginsym, endsym, readsym, writesym,    //4
    eql, neq, lss, leq, gtr, geq,   //6
    plussym, minussym, timessym, slashsym,  //4
    comma, semicolon, assign, colon, period,   //5
    lparen, rparen, lbracket, rbracket,    //4
    casesym, repeatsym, untilsym, downtosym            //3
};

//enum identtype {
//    vartype, consttype, proctype, functype, paramtype, paramvartype, errtype
//};
//
//enum datatype {
//    nul, chartype, inttype, chararrtype, intarrtype
//};
//
//enum exptype {
//    //变量或常量/数组项/数字/函数调用/算式
//    expConst, expVar, expArray, expNum, expFunc, expParamVar, expFormula
//};
//typedef struct expDataStruct {
//    exptype type;
//    char name[MaxRes + 1];
//    expDataStruct() {
//        type = expFormula;
//        name[0] = '\0';
//    }
//}expData;
//
//typedef union identdataUnion {
//    int* intd;
//    char* chard;
//    int* intarr;
//    char* chararr;
//}identdata;
//
//typedef struct identifierStruct {
//    char name[MaxRes + 1];
//    identtype identt;
//    datatype datat;
//    int lv;
//    int offset;
//    int length;
//    identdata* dataaddr;
//    struct identifierStruct* next;
//
//    identifierStruct() {
//        name[0] = '\0';
//        identt = errtype;
//        datat = nul;
//        lv = 0;
//        offset = 0;
//        length = 0;
//        dataaddr = null;
//        next = null;
//    }
//    ~identifierStruct() {
//        if (dataaddr != null)
//            free(dataaddr);
//    }
//}identifier;
//
//typedef struct _Mcode {
//    char cmd[10];
//    char op1[20];
//    char op2[20];
//    char op3[20];
//    struct _Mcode* next;
//    _Mcode() {
//        cmd[0] = '\0';
//        op1[0] = '\0';
//        op2[0] = '\0';
//        op3[0] = '\0';
//        next = null;
//    }
//}Mcode;
///*
//&int : identifier->dataaddr->intd;
//&char : identifier->dataaddr->chard;
//
//&intarr : identifier->dataaddr->intarr;
//&chararr : identifier->dataaddr->chararr;
//length of arr : identifier->length;
//*/
////extern char filename[100];

extern int lineNumber;
extern char ch;
extern char* symbolConst[NumRes];
extern int symbolTable[NumRes];
extern symbol sym;
extern int errorAmount;

extern int level;
extern int complexLevel;
extern int offset;

extern char lsIdent[MaxRes + 1];
extern int lsNum;
extern char lsChar;
extern char lsStr[MaxStr + 1];
//
//extern identifier *tableHead;
//extern Mcode *McodeHead, *pc;

int getSym();

void initLexer(string filename);

bool isDigit(char);
bool isLetter(char ch);
bool isLetterOrDigit(char ch);

void transform(char* ch);

symbol adder(char c[]);
symbol adder(char ch);
void setSymbol(char c[]);
void setSymbol(char ch);

#endif // !_definitions_h_
