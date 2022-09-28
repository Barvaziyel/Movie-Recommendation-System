#include "Movie.h"

Movie::Movie (std::string name, int year)
: name_ (std::move (name)), year_ (year)
{}

std::string Movie::get_name () const
{
  return name_;
}

int Movie::get_year () const
{
  return year_;
}

bool Movie::operator< (const Movie &rhs) const
{
  if (year_ < rhs.year_)
  {
    return true;
  }
  else if (year_ > rhs.year_)
  {
    return false;
  }
  else
  {
    return (name_ < rhs.name_);
  }
}

std::ostream &operator<< (std::ostream &os, const Movie &movie)
{
  os << movie.get_name () << OPEN_PRNTHS << movie.get_year () << CLOSE_PRNTHS;
  return os;
}

std::size_t sp_movie_hash (const sp_movie &movie)
{
  std::size_t res = HASH_START;
  res = res * RES_MULT + std::hash<std::string> () (movie->get_name ());
  res = res * RES_MULT + std::hash<int> () (movie->get_year ());
  return res;
}

bool sp_movie_equal (const sp_movie &m1, const sp_movie &m2)
{
  return !(*m1 < *m2) && !(*m2 < *m1);
}
