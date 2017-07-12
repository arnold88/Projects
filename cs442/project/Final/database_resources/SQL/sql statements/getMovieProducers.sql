SELECT people.id, people.first_name, people.last_name, people.gender
FROM movies
INNER JOIN movies_producers
	ON movies.id = movies_producers.movies_id
INNER JOIN people
	ON movies_producers.people_id = people.id
WHERE movies.id = 1904754;