//main.cpp
#include <iostream>
#include <sstream>
#include "FileScan.h"
#include "definitions.h"

int main() {
    int hasWhile = 1, hasCase = 0, hasRepeat = 0, hasStep = 1, hasParenthesis = 1;
    bool errorFlag;
    string dir, exe_dir;
    cout << "瞎写的测试用工具，毫无鲁棒性，不要瞎搞=。=" << endl
        << "支持对不支持的文法进行删除（扔掉测试程序）" << endl
        << "支持对for循环步长和downto的转换" << endl
        << "支持过程/函数无参时，有无括号的转换" << endl
        << " 以上功能全都未经测试 O.O" << endl
        << "如果嫌每次输入麻烦，请到main.cpp第8,20-39行将对应变量直接赋值，并删除cin和cout。" << endl
        << "建议将编译器输出调至Console，并选择模式2。" << endl
        << "祝大家测试愉悦~(～￣▽￣)→))*￣▽￣*)o" << endl << endl
        << "请输入测试程序目录（末尾不带\'\\\'） : " << endl;
    cin >> dir;
    cout << "请输入编译器exe地址（含完整路径,若不需要输出编译结果请输入字母n） : " << endl;
    cin >> exe_dir;
    cout << "支持while吗？（1：支持，0：不支持）" << endl;
    cin >> hasWhile;
    cout << "支持case吗？（1：支持，0：不支持）" << endl;
    cin >> hasWhile;
    cout << "支持repeat吗？（1：支持，0：不支持）" << endl;
    cin >> hasWhile;
    cout << "For循环支持自定义步长吗？（1：支持，0：不支持）" << endl;
    cin >> hasWhile;
    cout << "过程/函数无参时需要括号吗？（1：需要，0：不需要）" << endl;
    cin >> hasWhile;
    int mode;
    if (strcmp(exe_dir.c_str(), "n")) {
        cout << "请选择编译器的输出方式 : " << endl
            << "1 : 编译器自行输出到文件（本程序不做处理）。" << endl
            << "2 : 编译器将结果输出到屏幕（结果保存至targetCode文件夹下）。" << endl;
        cin >> mode;
    }
    
    find(dir,".txt");
    system(("md " + dir + "\\output").c_str());
    string filename;
    ifstream fpin;
    ostringstream ss;
    //filename = get();
    cout << "文法转换：" << endl;
    while ((filename = get()).length() != 0) {
        // todo : 
        string wholename = dir + "\\" + filename;
        cout << wholename << endl;
        errorFlag = false;
        //continue;
        initLexer(wholename);
        while (!errorFlag && getSym() != -1) {
            switch (sym) {
                case nil:
                    ss << endl;
                    break;
                case procsym:
                case funcsym:
                    ss << lsStr;
                    getSym();
                    ss << lsStr;
                    getSym();
                    if (hasParenthesis) {
                        if (sym != lparen) {
                            ss << "()";
                        }
                    }
                    else {
                        if (sym == lparen) {
                            getSym();
                            if (sym == rparen) {
                                getSym();
                            }
                            else {
                                ss << "(";
                            }
                        }
                    }
                    ss << lsStr;
                    break;
                case whilesym:
                    if (!hasWhile) {
                        errorFlag = true;
                    }
                    ss << lsStr;
                    break;
                case forsym:
                    ss << lsStr << " ";    getSym();
                    ss << lsStr << " ";    getSym();
                    ss << lsStr << " ";    getSym();
                    ss << lsStr << " ";    getSym();
                    if (hasStep) {
                        bool down = false;
                        if (sym == downtosym) {
                            down = true;
                        }
                        ss << "to ";
                        getSym();
                        ss << lsStr << " ";
                        getSym();
                        if (sym == bysym) {
                            ss << lsStr << " ";
                        }
                        else {
                            if (down) {
                                ss << "by -1 ";
                            }
                            else {
                                ss << "by 1 ";
                            }
                            ss << "do ";
                        }
                    }
                    //for i := 1 to/downto 2 do
                    //for i := 1 to 2 by 1 do
                    else {
                        char tmp1[MaxStr + 1];
                        char tmp2[MaxStr + 1];
                        strcpy_s(tmp1, lsStr);
                        getSym();
                        strcpy_s(tmp2, lsStr);
                        getSym();
                        if (sym == bysym) {
                            getSym();
                            if (sym == minussym) {
                                getSym();
                                ss << "downto " << tmp2 << " ";
                            }
                        }
                        else {
                            ss << tmp1 << " " << tmp2 << " " << lsStr;
                        }
                    }
                    break;
                case casesym:
                    if (!hasCase) {
                        errorFlag = true;
                    }
                    ss << lsStr;
                    break;
                case repeatsym:
                case untilsym:
                    if (!hasRepeat) {
                        errorFlag = true;
                    }
                    ss << lsStr;
                    break;
                default:
                    ss << lsStr << " ";
                    break;
            }
        }
        if (!errorFlag) {
            ofstream ofs;
            string t = dir + "\\output\\" + filename + ".out.txt";
            ofs.open(t.c_str());
            ofs << ss.str();
            ofs.close();
        }
        ss.str("");
    }

    cout << endl << "编译：" << endl;
    if (strcmp(exe_dir.c_str(), "n")) {
        system(("md " + dir + "\\targetCode").c_str());
        find(dir + "\\output", ".out.txt");
        
        while ((filename = get()).length() != 0) {
            string wholename = dir + "\\output\\" + filename;
            cout << wholename << endl;
            string t;
            if (mode == 2) {
                t = exe_dir + " " + wholename + " > " + dir + "\\targetCode\\" + filename + ".asm";
            }
            else {
                t = exe_dir + " " + wholename;
            }
            system(t.c_str());
        }
    }
    
    return 0;
}