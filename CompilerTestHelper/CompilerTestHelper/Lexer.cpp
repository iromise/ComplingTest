//Lexer.cpp
/*Lexical analyzer 词法分析器*/
/*
what to do :
a.记录标识符及其相关属性（动态数组+结构体实现吧，try try）
（标识符类型，数值类型，level层级，复杂属性指针）
typedef struct {
enum type

b.复杂属性结构体（妈个鸡说的就是你 -> 数组）

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
    if (isLetter(ch)) { //字母开头，标识符，保留字
        char wd[MaxRes];
        int x = 0;
        wd[x++] = ch;
        while (x < MaxRes && isLetterOrDigit(ch = getch())) {
            wd[x++] = ch;
        }
        wd[x] = '\0';
        if (x >= MaxRes) {
            //error(1, lineNumber);   //标识符超出长度限制（MaxRes个）
            while (!isLetterOrDigit(ch = getch()));
        }
        int rx;
        for (rx = 4; rx<NumRes && strcmp(wd, symbolConst[rx]); rx++);      //查找保留字表
        if (rx > NumRes - 1) {            //超出，为标识符
            sym = ident;
            r = ident;
            sprintf_s(lsStr, MaxRes, "%s", wd);
        }
        else {      //未超出，保留字
            strcpy_s(lsStr, symbolConst[rx]);
            r = symbol(rx);
            sym = symbol(rx);
        }
    }
    else if (isDigit(ch)) { //数字开头，数值
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
    else {  //符号开头，标点符号，圆/方括号
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
                                 //error(6, lineNumber);       //字符串含有非法字符
                                 x = -1;
                                 break;
                             }
                         }
                         lsStr[x++] = '\"';
                         if (x < 0) {
                             lsStr[0] = '\0';
                             while (getch() != '\"');    //去掉字符串剩下的部分
                         }
                         else {
                             lsStr[x] = '\0';
                             if (x>MaxStr) {     //字符串超出长度
                                 while (getch() != '\"');    //去掉字符串剩下的部分
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
                        //error(5, lineNumber);   //字符只能由一个数字或字母组成
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
            //error(-1, lineNumber);      //意外遇到文件尾。
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
