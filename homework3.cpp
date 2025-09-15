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

  Movie movie;
  while (data >> movie) {
    db[movie.getID()] = movie;
  }

  // Return the map of the movies.
  return db;
}

void findMovie(const MovieMap& db, int id) {
  if (db.find(id) != db.end()) {
    std::cout << db.at(id) << std::endl;
  } else {
    std::cout << "ID " << id << " not found!\n";
  }
}

void searchMovie(const MovieMap& db, std::string& keyword) {
  
}

int main(int argc, char** argv) {
  // Load the movie database from a given file.
  MovieMap db = load("./movies_db.txt");
  // Let the user search for a movie using a string or an integer.
  std::string keyword, value;
  int id;
  // std::cout << "Enter a command: " << std::endl;
  // std::cin >> keyword >> value;
  // std::stringstream ss(value);

  while (keyword != "exit") {
    std::cout << "Enter a command: " << std::endl;
    std::cin >> keyword >> value;
    std::stringstream ss(value);

    if (ss >> id && ss.eof()) {
      findMovie(db, id);
    } else {
      searchMovie(db, value);
    }
  }

  return 0;

  // if (keyword == "exit") {
  //   return 0;
  //   std::cout << "test";
  // } else if (ss >> id && ss.eof()) {
  //   findMovie(db, id);
  // } else {
  //   searchMovie(db, value);
  // }

}