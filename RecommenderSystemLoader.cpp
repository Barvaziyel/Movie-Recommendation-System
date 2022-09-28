#include "RecommenderSystemLoader.h"

std::unique_ptr<RecommenderSystem>
RecommenderSystemLoader::create_rs_from_movies_file
    (const std::string &movies_file_path) noexcept (false)
{
  sp_recommender_system rs =
      std::make_unique<RecommenderSystem> (RecommenderSystem ());
  std::string line;
  size_t pos;
  std::string name;
  int year;
  double features_score;
  std::vector<double> features;
  std::istringstream features_stream;
  std::ifstream f (movies_file_path);
  if (!f)
  {
    throw std::runtime_error (BAD_FILE_ERR);
  }
  while (std::getline (f, line))
  {
    pos = line.find (DASH);
    name = line.substr (0, pos);
    line.erase (0, pos + 1);
    pos = line.find (SPACE);
    year = stoi (line.substr (0, pos));
    line.erase (0, pos + 1);
    features_stream.clear ();
    features.clear ();
    features_stream.str (line);
    while (features_stream >> features_score)
    {
      if (std::floor (features_score) != features_score ||
          features_score > MAX_SCORE || features_score < MIN_SCORE)
      {
        throw std::runtime_error (BAD_SCORE_ERR);
      }
      features.push_back (features_score);
    }
    rs->add_movie (name, year, features);
  }
  return rs;
}