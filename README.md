# Movie-Recommendation-System

A system for storing a movie database (name, year, 4 features of the movie), movie rankings of users, and recommending appropriate movies to users according to their rankings.

## Usage
Create new Recommendation System by using the RecommenderSystemLoader class:
```
RecommenderSystemLoader creates system and adds movies from input txt file in the following format:
<Movie1 name>-<Movie1 year> <feature1 score> <feature2 score> <feature3 score> <feature4 score>
<Movie2 name>-<Movie2 year> <feature1 score> <feature2 score> <feature3 score> <feature4 score>
<Movie3 name>-<Movie3 year> <feature1 score> <feature2 score> <feature3 score> <feature4 score>
...
```

Load users to the system by using the RSUsersLoader class:
```
RSUsersLoader creates users from input txt file and unique_ptr to RecommenderSystem in the following format:
<Movie1 name>-<Movie1 year> <Movie2 name>-<Movie2 year> <Movie3 name>-<Movie3 year> <Movie4 name>-<Movie4 year> ...
<RSUser1 username> <Movie1 ranking> <Movie2 ranking> <Movie3 ranking> <Movie4 ranking> ...
<RSUser2 username> <Movie1 ranking> <Movie2 ranking> <Movie3 ranking> <Movie4 ranking> ...
...
```

Example input files are included.
