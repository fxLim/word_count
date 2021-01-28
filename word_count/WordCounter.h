#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

class WordCounter {					// z veliko
private:
	map<string, int> wordData;						//getter setter
    long fileSize;
	const string filename;
	
    void parseDoc();
	void printProgress(float progress);
	void printTable();
	long getFileSize(string filename);
	multimap<int, string> invertMap();

public:
    wordCounter(const string filename);
    void printWordData();
};

#endif