//main.cpp
#include <iostream>
#include <sstream>
#include "FileScan.h"
#include "definitions.h"

int main() {
    int hasWhile = 1, hasCase = 0, hasRepeat = 0, hasStep = 1, hasParenthesis = 1;
    bool errorFlag;
    string dir, exe_dir;
    cout << "Ϲд�Ĳ����ù��ߣ�����³���ԣ���ҪϹ��=��=" << endl
        << "֧�ֶԲ�֧�ֵ��ķ�����ɾ�����ӵ����Գ���" << endl
        << "֧�ֶ�forѭ��������downto��ת��" << endl
        << "֧�ֹ���/�����޲�ʱ���������ŵ�ת��" << endl
        << " ���Ϲ���ȫ��δ������ O.O" << endl
        << "�����ÿ�������鷳���뵽main.cpp��8,20-39�н���Ӧ����ֱ�Ӹ�ֵ����ɾ��cin��cout��" << endl
        << "���齫�������������Console����ѡ��ģʽ2��" << endl
        << "ף��Ҳ�������~(��������)��))*������*)o" << endl << endl
        << "��������Գ���Ŀ¼��ĩβ����\'\\\'�� : " << endl;
    cin >> dir;
    cout << "�����������exe��ַ��������·��,������Ҫ�����������������ĸn�� : " << endl;
    cin >> exe_dir;
    cout << "֧��while�𣿣�1��֧�֣�0����֧�֣�" << endl;
    cin >> hasWhile;
    cout << "֧��case�𣿣�1��֧�֣�0����֧�֣�" << endl;
    cin >> hasWhile;
    cout << "֧��repeat�𣿣�1��֧�֣�0����֧�֣�" << endl;
    cin >> hasWhile;
    cout << "Forѭ��֧���Զ��岽���𣿣�1��֧�֣�0����֧�֣�" << endl;
    cin >> hasWhile;
    cout << "����/�����޲�ʱ��Ҫ�����𣿣�1����Ҫ��0������Ҫ��" << endl;
    cin >> hasWhile;
    int mode;
    if (strcmp(exe_dir.c_str(), "n")) {
        cout << "��ѡ��������������ʽ : " << endl
            << "1 : ����������������ļ�����������������" << endl
            << "2 : ������������������Ļ�����������targetCode�ļ����£���" << endl;
        cin >> mode;
    }
    
    find(dir,".txt");
    system(("md " + dir + "\\output").c_str());
    string filename;
    ifstream fpin;
    ostringstream ss;
    //filename = get();
    cout << "�ķ�ת����" << endl;
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

    cout << endl << "���룺" << endl;
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