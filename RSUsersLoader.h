#ifndef RSUSERS_LOADER_H
#define RSUSERS_LOADER_H

#include "RecommenderSystemLoader.h"

class RSUsersLoader
{
 private:

 public:
  RSUsersLoader () = delete;
  /**
   *
   * loads users by the given format with their movie's ranks
   * @param users_file_path a path to the file of the users and their movie
   * ranks
   * @param rs RecommendingSystem for the Users
   * @return vector of the users created according to the file
   */
  static std::vector<RSUser>
  create_users_from_file (const std::string &users_file_path,
                          sp_recommender_system rs) noexcept (false);

  /**
   * helper function, loads users into system
   * @param line line of txt
   * @param movies vector of pointers to Movie objects
   * @param stream istringstream
   * @param f ifstream
   * @param s_rs ptr to RecommenderSystem object
   * @return vector of loaded users
   */
  static std::vector<RSUser> get_users (std::string &line,
                                        std::vector<sp_movie> &movies,
                                        std::istringstream &stream,
                                        std::ifstream &f,
                                        std::shared_ptr<RecommenderSystem> &s_rs);
};

#endif //RSUSERS_LOADER_H