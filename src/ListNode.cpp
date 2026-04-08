//
// Created by Fedor Kapranov on 08.04.2026.
//

#include <iostream>

#include "ListNode.h"

namespace List {
    void clear_list(ListNode*& head) {
        if (!head) {
            std::cout << "[clear_list]: list doesn't exist" << std::endl;
            return;
        }

        while (head) {
            ListNode* next = head->next;
            delete head;
            head = next;
        }

        std::cout << "List cleared" << std::endl;
    }

    void print_list(const ListNode* const head) {
        if (!head) {
            std::cout << "[print_list]: list doesn't exist" << std::endl;
            return;
        }

        for (
            const ListNode* current = head;
            current;
            current = current->next
        ) {
            std::cout << "\ndata: " << current->data
                << "\nprevious data: " << (current->prev ? current->prev->data: "-")
                << "\nrandom data: " << (current->rand ? current->rand->data: "-")
                << "\nnext data: " << (current->next ? current->next->data: "-")
                << std::endl << std::endl;
        }
    }
}