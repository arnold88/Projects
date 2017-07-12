USE imdb;
SELECT 
    title.title, name.name
FROM
    title
        JOIN
    cast_info ON title.id = cast_info.movie_id
        JOIN
    name ON name.id = cast_info.person_id;



-- This should deliver actors
-- role_type where role_type.id = 1;
CREATE TABLE movies_cast AS
SELECT 
    c.movie_id AS movies_id, c.person_id AS people_id
FROM
    cast_info AS c
WHERE
    c.person_role_id = 1
UNION
SELECT
    c.movie_id AS movies_id, c.person_id AS people_id
FROM
    cast_info AS c
WHERE
    c.person_role_id = 2;

-- This should deliver directors
-- role_type where role_type.id = 8;
CREATE TABLE movies_directors AS
SELECT 
    c.movie_id AS movies_id, c.person_id AS people_id
FROMSELECT n.id AS id, n.name AS name, aka.name AS nickname, n.gender AS gender
FROM name AS n LEFT JOIN aka_name AS aka ON n.id = aka.person_id
GROUP BY n.id, n.name;
    cast_info AS c
WHERE
    c.person_role_id = 8;

-- This should deliver writes
-- role_type = 4
CREATE TABLE movies_writers AS
SELECT 
    c.movie_id AS movies_id, c.person_id AS people_id
FROM
    cast_info AS c
WHERE
    c.person_role_id = 4 OR c.person_role_id = 9;

-- This should deliver producers
-- role_type = 3
CREATE TABLE movies_producers AS
SELECT 
    c.movie_id AS movies_id, c.person_id AS people_id
FROM
    cast_info AS c
WHERE
    c.person_role_id = 3;

-- This should set up movies
SELECT t.id AS id, t.title AS title, t.production_year AS release_year
FROM 
	title AS t
WHERE 
	kind_id = 2;

-- This should set up movie_data
CREATE TABLE movie_data AS
SELECT t.id AS movies_id, t.md5sum AS datum
FROM 
	title AS t
WHERE 
	kind_id = 2;

SELECT n.id AS id, n.name AS name, n.gender AS gender
FROM name AS n;
