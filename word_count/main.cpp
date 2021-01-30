#include <algorithm>
#include <string>
#include <iostream>
#include <windows.h>
#include <stdio.h>

#include "WordCounter.h"

using namespace std;

BOOL WINAPI consoleHandler(DWORD signal) {

    if (CTRL_C_EVENT == signal) {
        printf("\nVom Benutzer beendet.\n");
        exit(0);
    }

    return TRUE;
}

int main(int argc, char *argv[]) {
    unsigned short exitStatus = 0;
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        cout << "\nERROR: Control Handler konnte nicht eingestellt werden." << endl;

        exitStatus = 1;
    }
    if (1 == argc) {
        cout << "ERROR: Bitte datei speicherort als Argument eingeben." << endl;

        exitStatus = 1;
    } else if (2 < argc) {
        cout << "ERROR: Ungültige Anzahl von Argumenten." << endl;

        exitStatus = 1;
    } else {
        const string filename = argv[1];
        WordCounter doc(filename);
        switch (doc.printWordData()) {
            case 0:
                cout << "Datei ist leer.";
                break;
            case -1:
                cout << "ERROR: Datei existiert nicht.";
                exitStatus = 1;
        }
    }

    return exitStatus;
}