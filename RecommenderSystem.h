#ifndef RECOMMENDER_SYSTEM_H
#define RECOMMENDER_SYSTEM_H

#include <map>
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <complex>
#include <functional>
#include "RSUser.h"

/************ Constant Variables ************/

#define MIN_MOVIE_LIST_SIZE 1
#define DEF_PREF_VEC {0, 0, 0, 0}
#define SPACE ' '
#define DASH '-'
#define NA "NA"

/************ Messages to the user ************/

#define MOVIE_NOT_FOUND_ERR "ERROR: movie not found."
#define BAD_FILE_ERR "ERROR: problem with accessing file."

/************ Typedefs ************/

typedef std::unique_ptr<RecommenderSystem> sp_recommender_system;


class RecommenderSystem
{
 public:

  explicit RecommenderSystem ();

  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie
  add_movie (const std::string &name, int year,
             const std::vector<double> &features);

  /**
   * a function that calculates the movie with highest score based on movie
   * features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const RSUser &user);

  /**
   * a function that calculates the movie with highest predicted score based on
   * ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k how many movies to look at
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const RSUser &user, int k);

  /**
   * Predict a user rating for a movie given argument using item cf procedure
   * with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k: how many movies to look at
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const RSUser &user, const sp_movie &movie,
                              int k);

  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie (const std::string &name, int year) const;

  /**
   * operator << overload for RecommenderSystem
   * @param os output stream
   * @param rs RecommenderSystem
   * @return output stream
   */
  friend std::ostream &operator<< (std::ostream &os,
                                   const RecommenderSystem &rs);

 private:
  // map of movies & set of Movies
  std::unordered_map<sp_movie, std::vector<double>, hash_func, equal_func>
      movie_list_;

  std::set<Movie> set_movies_;

  /************ Helper functions ************/

  /**
   * gets average ranking of movies in map
   * @param ranks map of movies
   * @return average
   */
  double get_avg (const rank_map &ranks) const;

  /**
   * gets norm of vector
   * @param vec vector of doubles
   * @return norm
   */
  double get_norm (const std::vector<double> &vec) const;

  /**
   * gets similarity between two features vectors as follows:
   * (vec A*vec B)/(norm(vec A) * norm(vec B))
   * @param a first features vec
   * @param b second features vec
   * @return similarity
   */
  double get_similarity (const std::vector<double> &a,
                         const std::vector<double> &b) const;

  /**
   * gets a map of movies not ranked by user ordered by similarity value as key
   * @param user RSUser
   * @param pref_vec preferences vector
   * @return map as described
   */
  std::map<double, sp_movie, std::greater<>> get_similarities_map2
      (const RSUser &user, const std::vector<double> &pref_vec) const;

  /**
   * gets a map of movies ranked by user ordered by similarity value as key
   * @param user RSUser
   * @param pref_vec preferences vector
   * @returnmap as described
   */
  std::map<double, sp_movie, std::greater<>>
  get_similarities_map (const RSUser &user,
                        const std::vector<double> &pref_vec) const;
};

#endif //RECOMMENDER_SYSTEM_H