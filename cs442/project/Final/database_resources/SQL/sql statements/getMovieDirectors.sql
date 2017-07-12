SELECT people.id, people.first_name, people.last_name, people.gender
FROM movies
INNER JOIN movies_directors
	ON movies.id = movies_directors.movies_id
INNER JOIN people
	ON movies_directors.people_id = people.id
WHERE movies.id = 1904754;