#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <sys/stat.h>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <set>

using namespace std;

BOOL WINAPI consoleHandler(DWORD signal) {

    if (signal == CTRL_C_EVENT) {
    printf("\nVom Benutzer beendet.\n"); // do cleanup
    exit(0);
    }

    return TRUE;
}

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void printProgress (float progress)
{
    if (progress <= 1.0) {
        int barWidth = 70;
        cout << "\r[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << int(progress * 100.0) << "% \r";
        cout.flush();
    }
}

multimap<int, string> invert(map<string, int> & mymap)
{
    multimap<int, string> multiMap;

    map<string, int> :: iterator it;
    for (it=mymap.begin(); it!=mymap.end(); it++)
    {
        multiMap.insert(make_pair(it->second, it->first));
    }

    return multiMap;
}

int main()
{
    //running = TRUE;
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        printf("\nERROR: Could not set control handler");
        return 1;
    }
    vector<pair<string, int>> vec;
    static char filename[] = "";
    cout << "Datei speicherort eingeben: ";
    cin >> filename;
    long fileSize = GetFileSize(filename);
    float progress = 0;
    int progressLast = 0;
    //cout << fileSize << endl;

    long byteCount = 0;
    ifstream input(filename);
    if (!input)
    {
        cout << "Fehler beim Öffnen der Datendatei " << filename << "\n";
        return 1;
    }
    cout << "Ven zie den Vorgang stoppen möchten drücken Sie CTRL + C!" << endl;
    cout << "Die datai \"" << filename << "\" wird verarbeitet:" << endl;
    map<string, int> word_data;
    string word;
    // d:\_seltron\my_data1.txt
    while (input >> word)
    {
        byteCount = byteCount + word.length() + 1;
        progress = ((float)byteCount / fileSize);
        if(progressLast != (int)(progress*100)) {
            printProgress(progress);
            progressLast = progress*100;
        }

        if (word_data.find(word) != word_data.end())
        {
            word_data[word]++;
        }
        else
        {
            word_data[word] = 1;
        }
    }
    printProgress(1);
    cout << "\n";
    cout.width(20);
    cout << left << "Wort";
    cout << left << "Anzahl\n";

    multimap<int, string> newmap = invert(word_data);
    multimap<int, string> :: iterator iter;
    for (iter=newmap.begin(); iter!=newmap.end(); iter++)
    {
        // printing the second value first because the
        // order of (key,value) is reversed in the multimap
        cout.width(20);
        cout << left << iter->second;
        cout << left << iter->first << endl;
    }
//    map<string, unsigned int>::iterator iter;
//    for (iter = word_data.begin(); iter != word_data.end(); ++iter)
//    {
//        cout << iter->first << "\t\t\t" << iter->second << "\n";
//    }
    cin >> filename;
    return 0;
}
