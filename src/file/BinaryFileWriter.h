//
// Created by Fedor Kapranov on 02.04.2026.
//

#ifndef BINARY_FILE_WRITER_BINARYFILEWRITER_H
#define BINARY_FILE_WRITER_BINARYFILEWRITER_H

#include <string>
#include <fstream>
#include <memory>

#include "../ListNode.h"

class BinaryFileWriter {
    const std::string filename;
    std::ofstream output;
public:
    explicit BinaryFileWriter(std::string filename);

    /**
     * Writes a linked list to the output file in binary format. Creates
     * a new file if provided with specified name doesn't exist
     *
     * Format:
     * - File begins with total of nodes
     *   [uint32_t nodeCount]...
     *
     *   Restrictions:
     *      1. Total nodes <= 10**6
     *
     * - Next follows node data size, data bytes, index of its random node
     *   [uint16_t dataSize][data bytes]
     *
     *   Restrictions:
     *      1. Data <= 1000 symbols
     *
     * @param head The head of a linked list
     *
     * @throws std::runtime_error Couldn't write the list
     */
    void writeList(const std::shared_ptr<ListNode>& head);
};



#endif //BINARY_FILE_WRITER_BINARYFILEWRITER_H
