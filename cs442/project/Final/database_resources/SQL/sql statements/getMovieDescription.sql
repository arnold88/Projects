

SELECT info_type.info AS info_name, movies_info.info AS info_data
FROM movies
	INNER JOIN movies_info
		ON movies.id = movies_info.movies_id
	INNER JOIN info_type
		ON info_type.id = movies_info.info_type_id
WHERE movies.id = 2266712
	AND (info_type.info = 'plot')
LIMIT 1;