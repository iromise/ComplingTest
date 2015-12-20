//Lexer.cpp
/*Lexical analyzer �ʷ�������*/
/*
what to do :
a.��¼��ʶ������������ԣ���̬����+�ṹ��ʵ�ְɣ�try try��
����ʶ�����ͣ���ֵ���ͣ�level�㼶����������ָ�룩
typedef struct {
enum type

b.�������Խṹ�壨�����˵�ľ����� -> ���飩

*/


//#include <string>
#include <iostream>
#include <iomanip>
#include "definitions.h"
using namespace std;

//extern char ch;
//extern int lineNumber;
//extern char* resConst[NumRes];
//extern int symbolTable[NumRes];
ifstream fpin;

//extern void error(int, int);

int getSym();
char getch();

char line[MaxStr + 1] = "";
int index;

void initLexer(string filename) {
    if (fpin.is_open()) {
        fpin.close();
    }
    fpin.open(filename.c_str());
    index = -1;
    strcpy_s(line, "");
    ch = getch();
    ch = getch();
}



int getSym() {
    //char ch;
    symbol r;
    //ch = getch();
    while (ch == ' ' || ch == '\t') {
        ch = getch();
    }
    transform(&ch);
    if (isLetter(ch)) { //��ĸ��ͷ����ʶ����������
        char wd[MaxRes];
        int x = 0;
        wd[x++] = ch;
        while (x < MaxRes && isLetterOrDigit(ch = getch())) {
            wd[x++] = ch;
        }
        wd[x] = '\0';
        if (x >= MaxRes) {
            //error(1, lineNumber);   //��ʶ�������������ƣ�MaxRes����
            while (!isLetterOrDigit(ch = getch()));
        }
        int rx;
        for (rx = 4; rx<NumRes && strcmp(wd, symbolConst[rx]); rx++);      //���ұ����ֱ�
        if (rx > NumRes - 1) {            //������Ϊ��ʶ��
            sym = ident;
            r = ident;
            sprintf_s(lsStr, MaxRes, "%s", wd);
        }
        else {      //δ������������
            strcpy_s(lsStr, symbolConst[rx]);
            r = symbol(rx);
            sym = symbol(rx);
        }
    }
    else if (isDigit(ch)) { //���ֿ�ͷ����ֵ
        int x = 0;
        lsStr[x++] = ch;
        while (x < MaxNum && isDigit(ch = getch())) {
            lsStr[x++] = ch;
        }
        lsStr[x] = '\0';
        if (isDigit(ch)) {
            while (!isDigit(ch = getch()));
        }
        r = num;
        sym = num;
    }
    else {  //���ſ�ͷ�������ţ�Բ/������
        switch (ch) {
            case ':':
                ch = getch();
                if (ch == '=') {
                    char c[3] = ":=";
                    strcpy_s(lsStr, c);
                    ch = getch();
                    setSymbol(c);
                }
                else {
                    setSymbol(':');
                    lsStr[0] = ':';
                    lsStr[1] = '\0';
                }
                break;
            case '<':
                ch = getch();
                if (ch == '=') {
                    char c[3] = "<=";
                    strcpy_s(lsStr, c);
                    ch = getch();
                    setSymbol(c);
                }
                else if (ch == '>') {
                    char c[3] = "<>";
                    strcpy_s(lsStr, c);
                    ch = getch();
                    setSymbol(c);
                }
                else {
                    setSymbol('<');
                    lsStr[0] = '<';
                    lsStr[1] = '\0';
                }
                break;
            case '>':
                ch = getch();
                if (ch == '=') {
                    char c[3] = ">=";
                    strcpy_s(lsStr, c);
                    ch = getch();
                    setSymbol(c);
                }
                else {
                    setSymbol('>');
                    lsStr[0] = '>';
                    lsStr[1] = '\0';
                }
                break;
            case '\"':
            {
                         //char str[MaxStr + 1];
                         //cout << lineNumber << ", ";
                         int x = 0;
                         lsStr[x++] = '\"';
                         while (x < MaxStr - 1 && (ch = getch()) != '\"') {
                             if (ch >= 32 && ch <= 126) {
                                 lsStr[x++] = ch;
                             }
                             else {
                                 //error(6, lineNumber);       //�ַ������зǷ��ַ�
                                 x = -1;
                                 break;
                             }
                         }
                         lsStr[x++] = '\"';
                         if (x < 0) {
                             lsStr[0] = '\0';
                             while (getch() != '\"');    //ȥ���ַ���ʣ�µĲ���
                         }
                         else {
                             lsStr[x] = '\0';
                             if (x>MaxStr) {     //�ַ�����������
                                 while (getch() != '\"');    //ȥ���ַ���ʣ�µĲ���
                             }
                         }
                         adder('\"');
                         setSymbol('\"');
                         ch = getch();
            }
                break;
            case '\'':
                lsStr[0] = '\'';
                ch = getch();
                lsStr[1] = ch;
                if (ch != '\'') {
                    ch = getch();
                    if (ch != '\'') {
                        //error(5, lineNumber);   //�ַ�ֻ����һ�����ֻ���ĸ���
                        while ((ch = getch()) != '\'');
                    }
                }
                lsStr[2] = '\'';
                lsStr[3] = '\0';
                setSymbol('\'');
                ch = getch();
                break;
            case '=':
            case '+':
            case '-':
            case '*':
            case '/':
            case ',':
            case ';':
            case '.':
            case '(':
            case ')':
            case '[':
            case ']':
                lsStr[0] = ch;
                lsStr[1] = '\0';
                setSymbol(ch);
                ch = getch();
                break;
            case '\0':
                ch = getch();
                sym = nil;
                return 0;
                //return getSym();
                break;
            case -1:
                return -1;
            default:
                symbolTable[nil]++;
                //cout << ch;
                ch = getch();
                break;
        }
    }
    return r;
}

char getch() {
    ++index;
    if (line[index] == '\0') {
        lineNumber++; 
        if (fpin.eof()) {
            //error(-1, lineNumber);      //���������ļ�β��
            return -1;
        }
        fpin.getline(line, MaxStr);
        while (!fpin.eof() && line[0] == '\0')
            fpin.getline(line, MaxStr);
        index = -1;
        return '\0';
    }
    transform(&line[index]);
    return line[index];
}
