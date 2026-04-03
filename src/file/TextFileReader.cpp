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
    std::vector<std::shared_ptr<ListNode>> nodes;

    // Construct nodes
    while (auto lineOpt = readLine()) {
        std::vector<std::string> parts = splitLine(lineOpt.value(), ';');

        const auto node = std::make_shared<ListNode>();
        node->data = std::move(parts[0]);;

        nodeIndexToRandomNodeIndex[nodeIndex] = static_cast<int>(std::stoul(parts[1]));;
        nodes.push_back(node);

        nodeIndex++;
    }

    // Handles empty file
    if (nodes.empty()) {
        std::cout << "File \" " << filename << "\" is empty. Nothing to read" << std::endl;
        return std::nullopt;
    }

    for (int i = 0; i < nodes.size(); i++) {
        const auto& node = nodes[i];

        // Prev
        node->prev = i != 0 ? nodes[i - 1]: nullptr;

        // Next
        node->next = i != nodes.size() - 1 ? nodes[i + 1]: nullptr;

        // Random
        const auto randIndex = nodeIndexToRandomNodeIndex[i];
        // Safe cast because there's a restriction that total nodes <= 10**6
        if (randIndex >= static_cast<int>(nodes.size())) {
            std::cout << "Rand node with idx="
                      << randIndex << " doesn't exist for node with idx="
                      << i << std::endl;
            return std::nullopt;
        }
        node->rand = randIndex != -1 ? nodes[randIndex]: nullptr;
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
