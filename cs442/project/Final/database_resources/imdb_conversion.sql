use imdb;

CREATE TABLE movies AS
SELECT id, title, production_year, episode_of_id, season_nr, episode_nr, series_years
FROM title;

CREATE TABLE movie_data AS
SELECT id, md5sum
FROM title;

CREATE TABLE movies_cast AS
SELECT id, person_id, movie_id, note
FROM cast_info
WHERE person_role_id = 1 OR person_role_id = 2;

CREATE TABLE movies_directors AS
SELECT id, person_id, movie_id, note
FROM cast_info
WHERE person_role_id = 8;

CREATE TABLE movies_writers AS
SELECT id, person_id, movie_id, note
FROM cast_info
WHERE person_role_id = 4 OR person_role_id = 9;

CREATE TABLE movies_producers AS
SELECT id, person_id, movie_id, note
FROM cast_info
WHERE person_role_id = 3;

CREATE TABLE people AS
SELECT id, TRIM(SUBSTRING_INDEX(name, ',', -1)) AS first_name, TRIM(SUBSTRING_INDEX(name, ',', 1)) AS last_name, gender
FROM name;

CREATE TABLE biographies AS 
SELECT id, person_id, info_type_id, info
FROM person_info;

