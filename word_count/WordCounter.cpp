#include "WordCount.h"

void WordCounter::parseDoc(const string filename) {		//ffunkcije v class vidijo class memberje
	ifstream input(filename);
	if (!input)
	{
		cout << "Fehler beim Öffnen der Datei " << filename << "\n";
		exit(1);
	}

	float progress;
	int progressLast = 0;
	long byteCount = 0;

	cout << "Ven zie den Vorgang stoppen möchten drücken Sie CTRL + C!" << endl;
	cout << "Die datai \"" << filename << "\" wird verarbeitet:" << endl;

//        map<string, int> wordData;
	string word;
	while (input >> word) {
		byteCount = byteCount + word.length() + 1;
		progress = ((float)byteCount / fileSize);
		if(progressLast != (int)(progress*100)) {
			printProgress(progress);
			progressLast = progress*100;
		}
		if (wordData.find(word) != wordData.end()) {
			wordData[word]++;
		}
		else {
			wordData[word] = 1;
		}
	}
	printProgress(1);
}

void printProgress(float progress) {
	if (1 >= progress) {
		const int barWidth = 70;
		cout << "\r[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {				//oklepaji
			if (i < pos) cout << "=";
			else if (i == pos) cout << ">";
			else cout << " ";
		}
		cout << "] " << int(progress * 100.0) << "% \r";
		cout.flush();
	}
}

void printTable(map<string, int> wordData) {
	cout << "\n";
	cout.width(20);
	cout << left << "Wort";
	cout << left << "Anzahl\n";

	multimap<int, string> newmap = invertMap(wordData);

	for (auto const& [key, val] : newmap) {
		cout.width(20);
		cout << left << val;
		cout << left << key << endl;
	}
}

long getFileSize(string filename) {
	struct stat statBuf;
	int rc = !stat(filename.c_str(), &statBuf) ? statBuf.st_size : -1;
	if (1 > rc ) {
		cout << "ERROR: Datei existiert nicht oder ungültige Dateigröße.";
		exit(1);
	}
	return statBuf.st_size;
}

//multimap elements can have the same keys

multimap<int, string> invertMap(map<string, int> &map) {
	multimap<int, string> multiMap;

	for (auto const& [key, val] : map) {
		multiMap.insert(make_pair(val, key));
	}

	return multiMap;
}

wordCounter::wordCounter(const string filename):
	this.filename(filename)
 {}
	
void printWordData() { 
	fileSize = getFileSize(filename);
	parseDoc(filename);
	printTable(wordData);
	}