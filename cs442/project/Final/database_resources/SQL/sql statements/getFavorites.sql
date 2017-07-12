SELECT movies.id,
    movies.title,
    movies.production_year,
    movies.episode_of_id,
    movies.season_nr,
    movies.episode_nr,
    movies.series_years
FROM movies
INNER JOIN favorites
	ON movies.id = favorites.movies_id
WHERE favorites.accounts_id = 1;
