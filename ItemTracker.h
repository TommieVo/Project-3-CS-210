#pragma once
/*
 * File: ItemTracker.h
 * Author: Thuong Hai Vo
 * Date: 2025-10
 * Purpose:
 *   Corner Grocer frequency tracker. Encapsulates file I/O, counting,
 *   and display helpers. Uses std::map for deterministic alphabetical output.
 */

#ifndef ITEM_TRACKER_H
#define ITEM_TRACKER_H

#include <map>
#include <string>

class ItemTracker {
public:
    // Load items from a whitespace-delimited text file; throws on error.
    void LoadFromFile(const std::string& inputPath);

    // Write backup file "item count" per line; throws on error.
    void WriteBackup(const std::string& outPath = "frequency.dat") const;

    // Return frequency of a specific item (exact match); 0 if not found.
    int GetFrequency(const std::string& item) const;

    // Print all items and counts (aligned columns).
    void PrintAllFrequencies() const;

    // Print a histogram using the given symbol (default '*').
    void PrintHistogram(char symbol = '*') const;

    // True if no data loaded.
    bool Empty() const { return freq_.empty(); }

private:
    // Frequency map — key: item name, value: count.
    std::map<std::string, int> freq_;

    // Trim leading/trailing whitespace.
    static std::string Trim(const std::string& s);
};

#endif // ITEM_TRACKER_H
