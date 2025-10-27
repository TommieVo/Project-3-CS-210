/*
 * File: main.cpp
 * Author: Thuong Hai Vo
 * Date: 2025-10
 * Program: Corner Grocer (Project Three)
 * Summary:
 *   Loads a daily log of purchased items, builds a frequency map, writes a
 *   backup file (frequency.dat), and provides a menu to query, list, and
 *   visualize data as a histogram.
 * Standards Applied:
 *   - Avoid while(true) loops; use a clear exit condition
 *   - Initialize variables and comment their purpose
 *   - Use cerr for errors and EXIT_FAILURE on fatal issues
 *   - Keep main() small via helper functions
 */

#include "ItemTracker.h"
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>   // EXIT_SUCCESS / EXIT_FAILURE

 // --- Helper prototypes ---
int  GetMenuChoice(); // Validates and returns [1..4]
void HandleChoice(int choice, ItemTracker& tracker);
std::string PromptItemName(); // Reads a non-empty line from stdin

int main() {
    const std::string kInputFile = "CS210_Project_Three_Input_File.txt"; // Input path
    const std::string kBackupFile = "frequency.dat"; // Backup path

    ItemTracker tracker; // Core worker object that holds the frequency map

    // Load and back up data at startup; exit if we cannot read/write files.
    try {
        tracker.LoadFromFile(kInputFile);
        tracker.WriteBackup(kBackupFile);
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        std::cerr << "Tip: place \"" << kInputFile
            << "\" in the project's working directory.\n";
        return EXIT_FAILURE;
    }

    bool running = true; // Controls main program loop (clear exit condition)
    while (running) {
        const int choice = GetMenuChoice();
        if (choice == 4) {
            running = false;
            std::cout << "Goodbye.\n";
        }
        else {
            HandleChoice(choice, tracker);
        }
    }

    return EXIT_SUCCESS;
}

// Display menu, validate input, and return a choice in [1..4]
int GetMenuChoice() {
    int choice = 0; // Stores user menu selection

    std::cout << "\n====== Corner Grocer Item Tracker ======\n"
        << "1. Look up frequency of a specific item\n"
        << "2. Print all items with frequencies\n"
        << "3. Print histogram of item frequencies\n"
        << "4. Exit\n"
        << "Select an option (1-4): ";

    // Input validation for integer range [1..4]
    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cout << "Invalid choice. Enter a number from 1 to 4: ";
        std::cin.clear(); // clear failbit
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush line
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume newline
    return choice;
}

// Handle the three actionable menu items
void HandleChoice(int choice, ItemTracker& tracker) {
    switch (choice) {
    case 1: {
        const std::string query = PromptItemName(); // Item to search
        const int count = tracker.GetFrequency(query); // Frequency result
        std::cout << query << ' ' << count << '\n';
        break;
    }
    case 2:
        tracker.PrintAllFrequencies();
        break;
    case 3:
        tracker.PrintHistogram('*');
        break;
    default:
        // Should never occur due to validation
        std::cerr << "Unexpected menu option.\n";
        break;
    }
}

// Prompt for a non-empty item name from stdin
std::string PromptItemName() {
    std::string line; // Holds the user-entered item name
    std::cout << "Enter item name to search: ";
    std::getline(std::cin, line);
    while (line.empty()) {
        std::cout << "Input cannot be empty. Try again: ";
        std::getline(std::cin, line);
    }
    return line;
}
