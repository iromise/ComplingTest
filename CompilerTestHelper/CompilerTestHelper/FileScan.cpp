//FileScan.cpp
#include <io.h>
#include "FileScan.h"

_finddata_t fileInfo;
long handle;
bool flag;

bool find(string dir, string suffix) {
    string filename = dir + "\\*" + suffix;
    handle = _findfirst(filename.c_str(), &fileInfo);
    if (handle == -1L) {
        cerr << "failed to transfer files." << endl;
        flag = false;
    }
    else {
        flag = true;
    }
    return flag;
}

string get() {
    if (flag) {
        string s = fileInfo.name;
        if (_findnext(handle, &fileInfo) != 0) {
            flag = false;
        }
        return s;
    }
    else {
        return "";
    }
}