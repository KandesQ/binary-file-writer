//
// Created by Fedor Kapranov on 27.03.2026.
//

#ifndef BINARY_FILE_WRITER_TEXTFILEREADER_H
#define BINARY_FILE_WRITER_TEXTFILEREADER_H

#include <fstream>
#include <string>
#include <optional>
#include <memory>

#include "../ListNode.h"

class TextFileReader {
    const std::string filename;
    std::ifstream input;
public:
    explicit TextFileReader(std::string filename);

    /**
     * Reads data from the text file and constructs a doubly linked list of ListNode objects
     *
     * Each line in the file should contain two parts separated by a semicolon
     * File data format: data;randNodeIndex
     *
     * If the file is empty or an error occurs (e.g., invalid random index), the function returns std::nullopt.
     *
     * @return std::optional<std::shared_ptr<ListNode>>
     *         The head of the constructed linked list wrapped in std::optional.
     *         Returns `std::nullopt` if the list could not be constructed.
     */
    std::optional<std::shared_ptr<ListNode>> readList();
private:
    /**
     * Reads a line from the file.
     *
     * @return std::optional<std::string> containing the line. std::nullopt if all lines were read.
     */
    std::optional<std::string> readLine();

    /**
     * Splits a string into parts based on a given delimiter
     *
     * Example:
     *   splitLine("apple;banana;cherry", ';')
     *   returns {"apple", "banana", "cherry"}.
     *
     * @param line The input string to be split
     * @param delimiter The character used to separate the string into parts
     * @return A vector of substrings resulting from splitting line by delimiter
     */
    static std::vector<std::string> splitLine(const std::string& line, char delimiter);
};



#endif //BINARY_FILE_WRITER_TEXTFILEREADER_H
