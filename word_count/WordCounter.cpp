#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sys/stat.h>

#include "WordCounter.h"

using namespace ::std;

void WordCounter::parseDoc() {
    ifstream input(filename);
    float progress;
    int progressLast = 0;
    unsigned long byteCount = 0;

    cout << "Ven zie den Vorgang stoppen möchten drücken Sie CTRL + C!" << endl;
    cout << "Die datai \"" << filename << "\" wird verarbeitet:" << endl;

    string word;
    while (input >> word) {
        byteCount = byteCount + word.length() + 1;
        progress = ((float) byteCount / fileSize);
        if (progressLast != (int) (progress * 100)) {
            printProgress(progress);
            progressLast = progress * 100;
        }
        if (wordData.find(word) != wordData.end()) {
            wordData[word]++;
        } else {
            wordData[word] = 1;
        }
    }
    printProgress(1);
}

void WordCounter::printProgress(float progress) {
    if (1 >= progress) {
        const int barWidth = 70;
        cout << "\r[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) { cout << "="; }
            else if (i == pos) { cout << ">"; }
            else { cout << " "; }
        }
        cout << "] " << int(progress * 100.0) << "% \r";
        cout.flush();
    }
}

multimap<int, string> WordCounter::invertMap() {
    multimap<int, string> multiMap;

    for (auto const&[key, val] : wordData) {
        multiMap.insert(make_pair(val, key));
    }

    return multiMap;
}

void WordCounter::printTable() {
    cout << "\n";
    cout.width(20);
    cout << left << "Wort";
    cout << left << "Anzahl\n";

    multimap<int, string> sortedWordData = invertMap();

    for (auto const&[key, val] : sortedWordData) {
        cout.width(20);
        cout << left << val;
        cout << left << key << endl;
    }
}

long WordCounter::getFileSize() {
    struct stat statBuf;
    int rc = stat(filename.c_str(), &statBuf);

    return rc == 0 ? statBuf.st_size : -1;
}

WordCounter::WordCounter(const string filename)
: filename(filename)
{
}

short WordCounter::printWordData() {
    fileSize = getFileSize();
    if (0 != fileSize && -1 != fileSize) {
        parseDoc();
        printTable();
    }
    return fileSize > 0 ? 1 : fileSize;
}