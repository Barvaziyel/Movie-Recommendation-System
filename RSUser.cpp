#include "RSUser.h"
#include "RecommenderSystem.h"

// implement your cpp code here
RSUser::RSUser (std::string username, rank_map ranks,
                std::shared_ptr<RecommenderSystem> recommender_system)
    : username_ (std::move (username)), ranks_ (std::move (ranks)),
      recommender_system_ (std::move (recommender_system))
{}

std::string RSUser::get_name () const
{
  return username_;
}

void RSUser::add_movie_to_rs (const std::string &name, int year,
                              const std::vector<double> &features,
                              double rate)
{
  if (std::floor (rate) != rate || rate > MAX_SCORE || rate < MIN_SCORE)
  {
    throw std::runtime_error (BAD_SCORE_ERR);
  }
  ranks_[recommender_system_->add_movie (name, year, features)] = rate;
}

rank_map RSUser::get_ranks () const
{
  return ranks_;
}

sp_movie RSUser::get_recommendation_by_content () const
{
  return recommender_system_->recommend_by_content (*this);
}

sp_movie RSUser::get_recommendation_by_cf (int k) const
{
  return recommender_system_->recommend_by_cf (*this, k);
}

double
RSUser::get_prediction_score_for_movie (const std::string &name,
                                        int year, int k) const
{
  return recommender_system_->predict_movie_score
      (*this, recommender_system_->get_movie (name, year), k);
}

std::ostream &operator<< (std::ostream &os, const RSUser &user)
{
  os << NAME << user.get_name () << END_LINE << *user.recommender_system_
     << std::endl;
  return os;
}