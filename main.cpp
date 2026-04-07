#include <iostream>

#include "src/file/TextFileReader.h"

const std::string IN_FILENAME = "inlet.in";

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

void clear_list(ListNode* head) {
    if (!head) {
        std::cout << "[clear_list]: list doesn't exist" << std::endl;
        return;
    }

    ListNode *next = head->next;

    do {
        delete head;
        head = next;

        if (!next) {
            break;
        }

        next = next->next;
    } while (next);
}

int main() {
    TextFileReader reader(IN_FILENAME);
    ListNode *head{reader.read_list()};

    // Test: shows list
    print_list(head);

    clear_list(head);
    return 0;
}
