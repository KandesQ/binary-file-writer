//
// Created by Fedor Kapranov on 08.04.2026.
//

#include <utility>
#include <fstream>
#include <ios>
#include <iostream>

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

    // 256 MB
    constexpr uint32_t BUFFER_LIMIT = 256 * 1024 * 1024;
    std::vector<char> buffer;
    buffer.reserve(BUFFER_LIMIT);

    buffer.insert(
        buffer.end(),
        reinterpret_cast<char*>(&list_length),
        reinterpret_cast<char*>(&list_length) + sizeof(list_length)
    );

    current_node = head;
    uint32_t node_index = 0;
    while (current_node) {
        size_t allowance = sizeof(uint16_t) + current_node->data.size() + sizeof(int);

        if (buffer.size() + allowance >= BUFFER_LIMIT) {
            std::cout << "[write_list]: Buffer reached limit. Flushing...";
            out.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
            std::cout << "[write_list]: Buffer flushed";
            buffer.clear();
        }

        uint16_t node_data_size = current_node->data.size();

        buffer.insert(
            buffer.end(),
            reinterpret_cast<char*>(&node_data_size),
            reinterpret_cast<char*>(&node_data_size) + sizeof(node_data_size)
        );

        buffer.insert(
            buffer.end(),
            current_node->data.begin(),
            current_node->data.end()
        );

        int rand_index = rand_index_match.at(node_index);
        buffer.insert(
            buffer.end(),
            reinterpret_cast<char*>(&rand_index),
            reinterpret_cast<char*>(&rand_index) + sizeof(rand_index)
        );

        current_node = current_node->next;
        ++node_index;
    }
    out.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
}

void BinaryFileWriter::set_filename(std::string new_filename) {
    this->filename = std::move(new_filename);
}

const std::string& BinaryFileWriter::get_filename() const {
    return this->filename;
}

