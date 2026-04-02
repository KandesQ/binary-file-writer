#include <iostream>
#include <utility>

#include "src/file/TextFileReader.h"
#include "src//file/BinaryFileWriter.h"
#include "src/ListNode.h"

#define IN_FILE_NAME "inlet.in"
#define OUT_FILE_NAME "outlet.out"

void printListData(std::shared_ptr<ListNode> headNode) {
    auto currentNode = std::move(headNode);
    while (currentNode) {
        std::cout << currentNode->data << std::endl;
        currentNode = currentNode->next;
    }
}

int main() {
    auto textFileReader = TextFileReader(IN_FILE_NAME);
    const auto listHeadNodeOpt = textFileReader.readList();

    if (!listHeadNodeOpt) {
        return -1;
    }

    // Test: list is read successfully
    printListData(listHeadNodeOpt.value());

    auto binaryFileWriter = BinaryFileWriter(OUT_FILE_NAME);
    binaryFileWriter.writeList(listHeadNodeOpt.value());

    return 0;
}
