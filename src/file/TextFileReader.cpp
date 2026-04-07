//
// Created by Fedor Kapranov on 06.04.2026.
//

#include "TextFileReader.h"

#include <utility>
#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> split_line(const std::string& line, const char delimiter) {
    std::vector<std::string> parts;
    std::string part;
    std::istringstream ss(line);

    while (std::getline(ss, part, delimiter)) {
        parts.push_back(std::move(part));
    }

    return parts;
}

TextFileReader::TextFileReader(std::string filename)
    : filename(std::move(filename))
{}

ListNode* TextFileReader::read_list() {
    std::ifstream input(this->filename, std::ios::in);
    if (!input.is_open()) {
        throw std::runtime_error(
            "Couldn't open file \"" + this->filename + "\". "
            "Check if the provided file exists"
            );
    }

    uint32_t node_index = 0;
    std::string line;
    std::unordered_map<uint32_t, int> node_index_to_rand_node_index;
    std::vector<ListNode*> node_ptrs;
    while (std::getline(input, line)) {
        std::vector<std::string> parts = std::move(split_line(line, ';'));

        ListNode* node_ptr = new ListNode;
        node_ptr->data = std::move(parts[0]);

        node_index_to_rand_node_index[node_index] = std::stoi(parts[1]);
        node_ptrs.push_back(node_ptr);

        ++node_index;
    }

    if (node_ptrs.empty()) {
        std::cout << "File \" " << filename << "\" is empty. Nothing to read" << std::endl;
        return nullptr;
    }

    for (int i = 0; i < node_ptrs.size(); ++i) {
        ListNode* node_ptr = node_ptrs[i];

        // Prev
        node_ptr->prev = i != 0 ? node_ptrs[i - 1]: nullptr;

        // Next
        node_ptr->next = i != node_ptrs.size() - 1 ? node_ptrs[i + 1]: nullptr;

        // Rand
        const int rand_index = node_index_to_rand_node_index[i];
        // Safe cast because there's a restriction that total nodes <= 10**6
        if (rand_index >= static_cast<int>(node_ptrs.size())) {
            std::cout << "Rand node with idx="
                      << rand_index << " doesn't exist for node with idx="
                      << i << std::endl;
            return nullptr;
        }

        if (rand_index <= -1) {
            if (rand_index < -1) {
                std::cout << "Node " << i << ": rand index doesn't match -1 or any positive number."
                           " Proceed as if it doesn't have a rand node (rand index equals to -1)"
                          << std::endl;
            }
            node_ptr->rand = nullptr;
        } else {
            node_ptr->rand = node_ptrs[rand_index];
        }
    }

    return node_ptrs[0];
}

void TextFileReader::set_filename(std::string new_filename) {
    this->filename = std::move(new_filename);
}

const std::string& TextFileReader::get_filename() const {
    return this->filename;
}
