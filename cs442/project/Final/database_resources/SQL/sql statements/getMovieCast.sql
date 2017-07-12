SELECT people.id, people.first_name, people.last_name, people.gender
FROM movies
INNER JOIN movies_cast
	ON movies.id = movies_cast.movies_id
INNER JOIN people
	ON movies_cast.people_id = people.id
WHERE movies.id = 1904754;