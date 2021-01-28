#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <sys/stat.h>
#include <windows.h>
#include <stdio.h>

#include "WordCounter.h"

//naredi class.h in .cpp posebej za class

using namespace std;

BOOL WINAPI consoleHandler(DWORD signal) {

    if (CTRL_C_EVENT == signal) {
    printf("\nVom Benutzer beendet.\n");
    exit(0);
    }

    return TRUE;
}

int main(int argc, char *argv[]) {
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
       cout << "\nERROR: Control Handler konnte nicht eingestellt werden." << endl;
        
        return 1;
    }
    if (1 == argc) {
        cout << "ERROR: Bitte datei speicherort als Argument eingeben." << endl;

        return 1;
    }
    else if (2 < argc) {
        cout << "ERROR: Ungültige Anzahl von Argumenten." << endl;

        return 1;
    }
    
    const string filename = argv[1];
    wordCounter doc(filename);
    doc.printWordData();
    cout << doc.fileSize;
    return 0;
}