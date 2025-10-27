/*
 * File: ItemTracker.cpp
 * Author: Thuong Hai Vo
 * Date: 2025-10
 * Notes:
 *   Implements ItemTracker. Emphasizes clear error handling (cerr),
 *   initialized variables, and consistent formatting with std::setw.
 */

#include "ItemTracker.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

void ItemTracker::LoadFromFile(const std::string& inputPath) {
    std::ifstream inFile(inputPath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Error: cannot open input file: " + inputPath);
    }

    freq_.clear(); // Clear any previous data
    std::string token; // Holds each item token read from file

    // Read whitespace-delimited tokens; supports one-per-line or spaced.
    while (inFile >> token) {
        token = Trim(token);
        if (!token.empty()) {
            ++freq_[token]; // Increment count for this item
        }
    }

    if (inFile.bad()) {
        throw std::runtime_error("Error: I/O error while reading: " + inputPath);
    }
}

void ItemTracker::WriteBackup(const std::string& outPath) const {
    std::ofstream outFile(outPath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Error: cannot create backup file: " + outPath);
    }

    for (const auto& kv : freq_) {
        outFile << kv.first << ' ' << kv.second << '\n';
    }

    if (!outFile) {
        throw std::runtime_error("Error: I/O error while writing: " + outPath);
    }
}

int ItemTracker::GetFrequency(const std::string& item) const {
    auto it = freq_.find(item);
    return (it == freq_.end()) ? 0 : it->second;
}

void ItemTracker::PrintAllFrequencies() const {
    if (freq_.empty()) {
        std::cout << "(No data loaded)\n";
        return;
    }

    // Compute a simple padding width for aligned columns (min 12).
    std::size_t maxLen = 12; // required width for item column
    for (const auto& kv : freq_) {
        if (kv.first.size() > maxLen) maxLen = kv.first.size();
    }
    const int colWidth = static_cast<int>(maxLen + 2); // +2 spacing

    for (const auto& kv : freq_) {
        std::cout << std::left << std::setw(colWidth) << kv.first
            << kv.second << '\n';
    }
}

void ItemTracker::PrintHistogram(char symbol) const {
    if (freq_.empty()) {
        std::cout << "(No data loaded)\n";
        return;
    }

    std::size_t maxLen = 12;
    for (const auto& kv : freq_) {
        if (kv.first.size() > maxLen) maxLen = kv.first.size();
    }
    const int colWidth = static_cast<int>(maxLen + 2);

    for (const auto& kv : freq_) {
        std::cout << std::left << std::setw(colWidth) << kv.first;
        for (int i = 0; i < kv.second; ++i) {
            std::cout << symbol;
        }
        std::cout << '\n';
    }
}

std::string ItemTracker::Trim(const std::string& s) {
    if (s.empty()) return s;
    std::size_t start = 0; // first non-space index
    std::size_t end = s.size(); // one past last non-space
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}
