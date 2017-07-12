SELECT people.id, people.first_name, people.last_name, people.gender
FROM movies
INNER JOIN movies_writers
	ON movies.id = movies_writers.movies_id
INNER JOIN people
	ON movies_writers.people_id = people.id
WHERE movies.id = 1728392;