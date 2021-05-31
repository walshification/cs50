/*
Write a SQL query to determine the average rating of all movies released in 2012.
Output a table with a single column and a single row (not including the header)
containing the average rating.
*/
SELECT AVG(rating)
FROM movies
JOIN ratings
  ON ratings.movie_id = movies.id
WHERE year = 2012;
