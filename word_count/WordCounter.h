#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <map>

using namespace ::std;

/**
 * @brief Class for counting word occurrences in a user specified document and printing the values to console.
 */
class WordCounter {
private:
    std::map<string, int> wordData;     /** @brief Number of occurrences of specific words. */
    long fileSize;                      /** @brief Size of the file. */
    const string filename;              /** @brief Path to file. */

    /** @brief Parse file and print the progress. */
    void parseDoc();

    /**
     * @brief Print a progress bar.
     * @param progress - relative length of progress bar
     */
    void printProgress(float progress);

    /** @brief Prints table containing word occurrences. */
    void printTable();

    /**
     * @brief Gets size of file located at the location of filename.
     * @return Returns size of file if successful or 0 if failed.
     */
    long getFileSize();

    /**
     * @brief Swaps key and value wordData.
     * @return Returns multimap with <count, word>.
     */
    multimap<int, string> invertMap();

public:
    /**
     * @brief Constructs a WordCounter with a given filename.
     * @param filename - Absolute path to the filename.
     */
    explicit WordCounter(const string filename);

    /**
     * @brief Parses file and prints word occurrences.
     * @return 1 if successful, -1 if failed, 0 if file is empty.
     */
    short printWordData();
};

#endif