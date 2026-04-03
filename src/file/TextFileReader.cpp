//
// Created by Fedor Kapranov on 27.03.2026.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <ios>
#include <stdexcept>
#include <optional>
#include <memory>

#include "TextFileReader.h"

TextFileReader::TextFileReader(std::string filename)
    : filename(std::move(filename)),
      input(this->filename, std::ios::in) {

    if (!input.is_open()) {
        throw std::runtime_error(
            "Couldn't open file \"" + this->filename + "\". "
            "Check if provided file exists"
            );
    }
}

std::optional<std::shared_ptr<ListNode>> TextFileReader::readList() {
    int nodeIndex = 0;
    std::unordered_map<int, int> nodeIndexToRandomNodeIndex;
    std::unordered_map<int, std::shared_ptr<ListNode>> nodes;

    // Construct nodes
    while (auto lineOpt = readLine()) {
        std::vector<std::string> parts = splitLine(lineOpt.value(), ';');

        const auto node = std::make_shared<ListNode>();
        node->data = std::move(parts[0]);;

        nodeIndexToRandomNodeIndex[nodeIndex] = static_cast<int>(std::stoul(parts[1]));;
        nodes[nodeIndex] = node;

        nodeIndex++;
    }

    // Handles empty file
    if (nodes.empty()) {
        std::cout << "File \" " << filename << "\" is empty. Nothing to read" << std::endl;
        return std::nullopt;
    }

    // Assign prev next and random
    for (auto& [index, node]: nodes) {
        // Prev
        node->prev = nodes.contains(index - 1) ? nodes[index - 1]: nullptr;

        // Next
        node->next = nodes.contains(index + 1) ? nodes[index + 1]: nullptr;

        // Random
        // Remain nullptr if rand points none
        if (nodeIndexToRandomNodeIndex[index] == -1) continue;

        // End reading if random node doesn't exist in provided file
        if (!nodes.contains(nodeIndexToRandomNodeIndex[index])) {
            std::cout << "Node with index=" << index << " have index of random node that doesn't exist" << std::endl;
            return std::nullopt;
        }

        node->rand = nodes[nodeIndexToRandomNodeIndex[index]];
    }

    // Return the head
    return nodes[0];
}

std::optional<std::string> TextFileReader::readLine() {
    std::string line;
    if (std::getline(input, line)) {
        return line;
    }
    return std::nullopt;
}

std::vector<std::string> TextFileReader::splitLine(const std::string &line, char delimiter) {
    std::vector<std::string> parts;
    std::string part;
    std::istringstream ss(line);

    while (std::getline(ss, part, delimiter)) {
        parts.push_back(std::move(part));
    }

    return parts;
}
