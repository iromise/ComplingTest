//definitions.cpp
#include <iostream>
#include <fstream>
#include "definitions.h"

using namespace std;


//char filename[100] = "13061181_test.txt";

int lineNumber = 0;
char ch = ' ';
symbol sym;
int errorAmount = 0;

int level = -1;
int complexLevel = 0;
int offset = 0;

char lsIdent[MaxRes + 1];
int lsNum;
char lsChar;
char lsStr[MaxStr + 1];


extern int symbolTable[NumRes] = { 0 };
extern char* symbolConst[NumRes] = {
    "null",     //1
    "ident", "num", "\"", "\'",     //4
    "const", "var", "array", "of", "integer", "char", "procedure", "function",  //8
    "if", "then", "else", "while", "do", "for", "to", "by",     //8
    "begin", "end", "read", "write",    //4
    "=", "<>", "<", "<=", ">", ">=",    //6
    "+", "-", "*", "/",     //4
    ",", ";", ":=", ":", ".",       //5
    "(", ")", "[", "]",      //4
    "case", "repeat", "until", "downto" //4
};


int identTable[4] = { 0 };
int dataTable[4] = { 0 };

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'A');
}

bool isLetterOrDigit(char ch) {
    return isLetter(ch) || isDigit(ch);
}

void transform(char* ch) {
    if (*ch >= 'A' && *ch <= 'Z') {
        *ch = *ch + ('a' - 'A');
    }
}

symbol adder(char c[]) {
    int rx = 3;
    while (rx < NumRes && strcmp(c, symbolConst[rx++]));
    if (rx >= NumRes) {
        symbolTable[0]++;
        return nil;
    }
    else {
        rx--;
        symbolTable[rx]++;
        return symbol(rx);
    }
}

symbol adder(char ch) {
    char c[2];
    c[0] = ch;
    c[1] = '\0';
    return adder(c);
}

void setSymbol(char c[]) {
    int rx = 3;
    while (rx < NumRes && strcmp(c, symbolConst[rx++]));
    if (rx > NumRes) {
        sym = nil;
    }
    else {
        rx--;
        sym = symbol(rx);
    }
}

void setSymbol(char ch) {
    char c[2];
    c[0] = ch;
    c[1] = '\0';
    setSymbol(c);
}
