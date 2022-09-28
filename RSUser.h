#ifndef RSUSER_H
#define RSUSER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <set>
#include <utility>
#include "Movie.h"

/************ Constant Variables ************/

#define MAX_SCORE 10
#define MIN_SCORE 1
#define NAME "name: "
#define END_LINE "\n"

/************ Messages to the user ************/

#define BAD_SCORE_ERR "ERROR: bad score."

class RecommenderSystem; //forward declaration

/************ Typedefs ************/

typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;

class RSUser
{
 public:
  /**
   * Constructor
   */
  RSUser (std::string username, rank_map ranks,
          std::shared_ptr<RecommenderSystem> recommender_system);

  /**
   * a getter for the user's name
   * @return the username
   */
  std::string get_name () const;

  /**
   * function for adding a movie to the DB
   * @param name name of movie
   * @param year year it was made
   * @param features a vector of the movie's features
   * @param rate the user rate for this movie
   */
  void add_movie_to_rs (const std::string &name, int year,
                        const std::vector<double> &features,
                        double rate);

  /**
   * a getter for the ranks map
   * @return map of ranks
   */
  rank_map get_ranks () const;

  /**
   * returns a recommendation according to the movie's content
   * @return recommendation
   */
  sp_movie get_recommendation_by_content () const;

  /**
   * returns a recommendation according to the similarity recommendation method
   * @param k the number of the most similar movies to calculate by
   * @return recommendation
   */
  sp_movie get_recommendation_by_cf (int k) const;

  /**
   * predicts the score for a given movie
   * @param name the name of the movie
   * @param year the year the movie was created
   * @param k the parameter which represents the number of the most similar
   * movies to predict the score by
   * @return predicted score for the given movie
   */
  double
  get_prediction_score_for_movie (const std::string &name,
                                  int year, int k) const;

  /**
   * output stream operator
   * @param os the output stream
   * @param user the user
   * @return output stream
   */
  friend std::ostream &operator<< (std::ostream &os, const RSUser &user);

 private:
  std::string username_; //user's username
  rank_map ranks_; //map of user's rankings of movies
  std::shared_ptr<RecommenderSystem> recommender_system_; //ptr to system user belongs to
};

#endif //RSUSER_H