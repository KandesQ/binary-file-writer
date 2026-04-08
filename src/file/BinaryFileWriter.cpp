//
// Created by Fedor Kapranov on 08.04.2026.
//

#include <utility>
#include <fstream>
#include <ios>

#include "BinaryFileWriter.h"

BinaryFileWriter::BinaryFileWriter(std::string filename)
    : filename(std::move(filename))
{}

void BinaryFileWriter::write_list(
    const List::ListNode* const head,
    const std::unordered_map<uint32_t, int>& rand_index_match
    ) const {

    std::ofstream out{this->filename, std::ios::out | std::ios::binary};
    if (!out.is_open()) {
        throw std::runtime_error("Could not open " + this->filename + " file for writing");
    }

    const List::ListNode* current_node = head;

    uint32_t list_length = 0;
    while (current_node) {
        ++list_length;
        current_node = current_node->next;
    }
    out.write(reinterpret_cast<char*>(&list_length), sizeof(list_length));

    current_node = head;
    uint32_t node_index = 0;
    while (current_node) {
        uint16_t node_data_size = current_node->data.size();

        out.write(reinterpret_cast<char*>(&node_data_size), sizeof(node_data_size));
        out.write(
            current_node->data.data(),
            node_data_size
        );

        int rand_node_index = rand_index_match.at(node_index);
        out.write(
            reinterpret_cast<char*>(&rand_node_index), sizeof(rand_node_index)
        );

        current_node = current_node->next;
        ++node_index;
    }
}

void BinaryFileWriter::set_filename(std::string new_filename) {
    this->filename = std::move(new_filename);
}

const std::string& BinaryFileWriter::get_filename() const {
    return this->filename;
}

