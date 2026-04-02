//
// Created by Fedor Kapranov on 02.04.2026.
//

#include "BinaryFileWriter.h"

#include <codecvt>
#include <memory>
#include <ios>

#include "../ListNode.h"

BinaryFileWriter::BinaryFileWriter(std::string filename)
    : filename(std::move(filename)),
      output(this->filename, std::ios::out | std::ios::binary) {}

void BinaryFileWriter::writeList(const std::shared_ptr<ListNode>& head) {
    auto currentNode = head;

    // Count list length and save it to file
    std::uint32_t listLen = 0;
    while (currentNode) {
        listLen++;
        currentNode = currentNode->next;
    }
    output.write(reinterpret_cast<char*>(&listLen), sizeof(listLen));

    // Iterate for list. Save the size and data of each node
    currentNode = head;
    while (currentNode) {
        std::uint16_t dataLen = currentNode->data.size();

        output.write(reinterpret_cast<char*>(&dataLen), sizeof(dataLen));
        output.write(
            currentNode->data.data(),
            dataLen
        );

        currentNode = currentNode->next;
    }
}
