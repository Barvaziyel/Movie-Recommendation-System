#include "RecommenderSystem.h"

RecommenderSystem::RecommenderSystem ()
    : movie_list_ (MIN_MOVIE_LIST_SIZE, sp_movie_hash, sp_movie_equal)
{}

sp_movie RecommenderSystem::add_movie (const std::string &name, int year,
                                       const std::vector<double> &features)
{
  for (auto i: features)
  {
    if (std::floor (i) != i || i > MAX_SCORE || i < MIN_SCORE)
    {
      throw std::runtime_error (BAD_SCORE_ERR);
    }
  }
  sp_movie movie = std::make_shared<Movie> (Movie (name, year));
  if (set_movies_.find (*movie) != set_movies_.end ())
  {
    return get_movie (name, year);
  }
  movie_list_[movie] = features;
  set_movies_.insert (*movie);
  return movie;
}

double RecommenderSystem::get_avg (const rank_map &ranks) const
{
  double sum = 0;
  for (const auto &i: ranks)
  {
    sum += i.second;
  }
  return sum / (double) ranks.size ();
}

double RecommenderSystem::get_norm (const std::vector<double> &vec) const
{
  return std::sqrt (inner_product (vec.begin (), vec.end (), vec.begin (),
                                   0.0));
}

double RecommenderSystem::get_similarity (const std::vector<double> &a,
                                          const std::vector<double> &b) const
{
  double similarity = 0;
  for (size_t i = 0; i < b.size (); i++)
  {
    similarity += (a[i] * b[i]);
  }
  return similarity / (get_norm (a) * get_norm (b));
}

std::map<double, sp_movie, std::greater<>>
RecommenderSystem::get_similarities_map
    (const RSUser &user, const std::vector<double> &pref_vec) const
{
  std::map<double, sp_movie, std::greater<>> similarities;
  for (const auto &i: movie_list_)
  {
    if (user.get_ranks ().find (i.first) != user.get_ranks ().end ())
    {
      similarities[get_similarity (pref_vec, i.second)] = i.first;
    }
  }
  return similarities;
}

std::map<double, sp_movie, std::greater<>>
RecommenderSystem::get_similarities_map2
    (const RSUser &user, const std::vector<double> &pref_vec) const
{
  std::map<double, sp_movie, std::greater<>> similarities;
  for (const auto &i: movie_list_)
  {
    if (user.get_ranks ().find (i.first) == user.get_ranks ().end ())
    {
      similarities[get_similarity (pref_vec, i.second)] = i.first;
    }
  }
  return similarities;
}

sp_movie RecommenderSystem::recommend_by_content (const RSUser &user)
{
  double n = get_avg (user.get_ranks ());
  rank_map normalized_ranks = user.get_ranks ();
  for (auto &normalized_rank: normalized_ranks)
  {
    normalized_rank.second -= n;
  }
  std::vector<double> pref_vec = DEF_PREF_VEC;
  std::vector<double> features;
  for (const auto &i: normalized_ranks)
  {
    auto it = pref_vec.begin ();
    for (auto j: movie_list_.find (i.first)->second)
    {
      *it += (i.second * j);
      it++;
    }
    features.clear ();
  }
  std::map<double, sp_movie, std::greater<>>
      similarities = get_similarities_map2 (user, pref_vec);
  return similarities.begin ()->second;
}

sp_movie RecommenderSystem::recommend_by_cf (const RSUser &user, int k)
{
  std::map<double, sp_movie, std::greater<>> predictions;
  for (const auto &i: movie_list_)
  {
    if (user.get_ranks ().find (i.first) == user.get_ranks ().end ())
    {
      predictions[predict_movie_score (user, i.first, k)] = i.first;
    }
  }
  return predictions.begin ()->second;
}

double RecommenderSystem::predict_movie_score (const RSUser &user,
                                               const sp_movie &movie, int k)
{
  if (!movie)
  {
    throw std::runtime_error (MOVIE_NOT_FOUND_ERR);
  }
  std::map<double, sp_movie, std::greater<>> similarities =
      get_similarities_map (user, movie_list_.find (movie)->second);
  auto i = similarities.begin ();
  double numerator = 0;
  double denominator = 0;
  for (int j = 0; j < k; j++)
  {
    numerator += (i->first) * (user.get_ranks ().find (i->second)->second);
    denominator += (i->first);
    i++;
    if (i == similarities.end ())
    {
      break;
    }
  }
  return numerator / denominator;
}

sp_movie RecommenderSystem::get_movie (const std::string &name,
                                       int year) const
{
  sp_movie movie = std::make_shared<Movie> (Movie (name, year));
  auto found_movie = movie_list_.find (movie);
  if (found_movie == movie_list_.end ())
  {
    return nullptr;
  }
  return found_movie->first;
}

std::ostream &operator<< (std::ostream &os, const RecommenderSystem &rs)
{
  for (const auto &i: rs.set_movies_)
  {
    os << i;
  }
  return os;
}