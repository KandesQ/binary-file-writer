//
// Created by Fedor Kapranov on 28.03.2026.
//

#ifndef BINARY_FILE_WRITER_LISTNODE_H
#define BINARY_FILE_WRITER_LISTNODE_H

#include <string>
#include <memory>

struct ListNode {
    // Note: I changed raw ptr to RAII to bring memory safe approach
    std::shared_ptr<ListNode> prev = nullptr;
    std::shared_ptr<ListNode> next = nullptr;
    std::shared_ptr<ListNode> rand = nullptr;
    std::string data;
};

#endif //BINARY_FILE_WRITER_LISTNODE_H
