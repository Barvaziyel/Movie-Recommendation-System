#ifndef MOVIE_H
#define MOVIE_H

#include <utility>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

/************ Constant Variables ************/

#define HASH_START 17
#define HASH_START 17
#define RES_MULT 31
#define OPEN_PRNTHS " ("
#define CLOSE_PRNTHS ")\n"

class Movie; //forward declaration

/************ Typedefs ************/

typedef std::shared_ptr<Movie> sp_movie;
typedef std::size_t (*hash_func) (const sp_movie &movie);
typedef bool (*equal_func) (const sp_movie &m1, const sp_movie &m2);

/**
 * hash function used for a unordered_map
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash (const sp_movie &movie);

/**
 * equal function used for an unordered_map
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal (const sp_movie &m1, const sp_movie &m2);

class Movie
{
 public:
  /**
   * constructor
   * @param name: name of movie
   * @param year: year it was made
   */
  Movie (std::string name, int year);

  /**
   * returns the name of the movie
   * @return const ref to name of movie
   */
  std::string get_name () const;

  /**
   * returns the year the movie was made
   * @return year movie was made
   */
  int get_year () const;

  /**
   * operator< overload for two movies
   * @param rhs: right hand side
   * @param lhs: left hand side
   * @return returns true if (lhs.year) < rhs.year or
   * (rhs.year == lhs.year & lhs.name < rhs.name) else return false
   */
  bool operator< (const Movie &rhs) const;

  /**
   * operator<< overload for movie
   * @param os ostream to output info with
   * @param movie movie to output
   * @return output stream
   */
  friend std::ostream &operator<< (std::ostream &os, const Movie &movie);

 private:
  std::string name_; //movie name
  int year_; //movie year

};

#endif //MOVIE_H