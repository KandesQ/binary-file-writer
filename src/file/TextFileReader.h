//
// Created by Fedor Kapranov on 06.04.2026.
//

#ifndef BINARY_FILE_WRITER_TEXTFILEREADER_H
#define BINARY_FILE_WRITER_TEXTFILEREADER_H

#include <string>

#include "../ListNode.h"

class TextFileReader
{
    std::string filename;
public:
    explicit TextFileReader(std::string filename);

    ListNode* read_list();

    void set_filename(std::string new_filename);

    const std::string& get_filename() const;
};



#endif //BINARY_FILE_WRITER_TEXTFILEREADER_H
