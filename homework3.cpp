/* 
 * File:   homework3.cpp
 * Author: kestnemr
 *
 * Copyright (C) 2025 kestnemr@miamiOH.edu
 */

#include <unordered_map>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "Movie.h"

// A shortcut to a map of movies. The key for this map 
// is the movie's numeric ID.
using MovieMap = std::unordered_map<int, Movie>;


/**
 * Method to load movie entries from a given file into an 
 * unordered map.
 * 
 * @param filePath Path to the file from where data is to be read.
 * @return An unordered map containing the data.
 */
MovieMap load(const std::string& filePath) {
  // Create the entry for the file to be read.
  std::ifstream data(filePath);
  if (!data.good()) {
    throw std::runtime_error("Unable to read file " + filePath);
  }
  // Create the map to be populated and returned.
  MovieMap db;
  std::string line;

  while (std::getline(data, line)) {
    // Skip comment line.
    if (line[0] == '#') {
      continue;
    }
    std::istringstream iss(line);
    Movie movie;
    iss >> movie;
    db[movie.getID()] = movie;
  }
  // Return the map of the movies.
  return db;
}

void findMovie(const MovieMap& db, const int id) {
  if (db.find(id) != db.end()) {
    std::cout << db.at(id) << std::endl;
  } else {
    std::cout << "Movie with ID " << id << 
    " not found in database." << std::endl;
    // std::cout << "ID " << id << " not found!" << std::endl;
  }
}

void searchMovie(const MovieMap& db, std::string& value) {
  // Count how many movies the search found.
  int count = 0;
  for (const auto& movie : db) {
    std::string entry = to_string(movie.second);
    if (entry.find(value) != std::string::npos) {
      std::cout << entry << std::endl;
      count++;
    }
  }
  // Print the counter.
  std::cout << "Found " << count << " matche(s)" << std::endl;
}

int main(int argc, char** argv) {
  // Load the movie database from a given file.
  MovieMap db = load("./movies_db.txt");

  std::string command, line;

  while (true) {
    // Assign values to variables from the user input.
    std::cout << "Enter a command:" << std::endl;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    iss >> command;

    // Quit the program if the user wants to exit.
    if (command == "exit") { break; }

    std::string value;
    std::getline(iss, value);

    // Ignore any spaces in front of commands
    size_t first = value.find_first_not_of(' ');
    if (first != std::string::npos) {
      value = value.substr(first);
    } else { value = ""; }

    // Call helper methods to find movie IDs or search.
    if (command == "find") {
      findMovie(db, std::stoi(value));
    } else {
      searchMovie(db, value);
    }
  }
  return 0;
}
