#include "RSUsersLoader.h"

std::vector<RSUser> RSUsersLoader::get_users
    (std::string &line, std::vector<sp_movie> &movies,
     std::istringstream &stream, std::ifstream &f,
     std::shared_ptr<RecommenderSystem> &s_rs)
{
  std::vector<RSUser> users;
  double score_num;
  std::string username;
  std::string score;
  rank_map user_rank_map (1, sp_movie_hash, sp_movie_equal);
  while (std::getline (f, line))
  {
    user_rank_map.clear ();
    auto it = movies.begin ();
    stream.clear ();
    stream.str (line);
    stream >> username;
    while (stream >> score)
    {
      if (score != NA)
      {
        score_num = std::stod (score);
        if (floor (score_num) != score_num ||
            score_num > MAX_SCORE || score_num < MIN_SCORE)
        {
          throw std::runtime_error (BAD_SCORE_ERR);
        }
        user_rank_map[*it] = score_num;
      }
      it++;
    }

    users.emplace_back (RSUser (username, user_rank_map, s_rs));
  }
  return users;
}

std::vector<RSUser> RSUsersLoader::create_users_from_file
    (const std::string &users_file_path,
     sp_recommender_system rs) noexcept (false)
{
  std::string line;
  size_t pos;
  std::string movie;
  std::string name;
  int year;
  std::vector<sp_movie> movies;
  std::istringstream stream;
  std::ifstream f (users_file_path);
  if (!f)
  {
    throw std::runtime_error (BAD_FILE_ERR);
  }
  std::getline (f, line);
  stream.str (line);
  while (stream >> movie)
  {
    pos = movie.find (DASH);
    name = movie.substr (0, pos);
    movie.erase (0, pos + 1);
    year = stoi (movie);
    movies.push_back (rs->get_movie (name, year));
  }
  std::shared_ptr<RecommenderSystem> s_rs = std::move (rs);
  return get_users (line, movies, stream, f, s_rs);
}
