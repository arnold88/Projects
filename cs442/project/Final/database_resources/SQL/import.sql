------------------------------
-- CREATE TABLES
------------------------------
CREATE TABLE config 
	(attribute VARCHAR(255) PRIMARY KEY, 
	 value VARCHAR(255));

CREATE TABLE credit_card_types
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	 name VARCHAR(20));

CREATE TABLE accounts
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	first_name VARCHAR(255) NOT NULL,
	middle_name VARCHAR(255),
	last_name VARCHAR(255) NOT NULL,
	address_1 VARCHAR(255) NOT NULL,
	address_2 VARCHAR(255),
	city VARCHAR(255) NOT NULL,
	state VARCHAR(255) NOT NULL,
	zip_code VARCHAR(255) NOT NULL,
	username CHAR(20) NOT NULL,
	password CHAR(20) NOT NULL);

CREATE TABLE payment_methods
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	 account_id INT NOT NULL REFERENCES accounts,
	 credit_card_types_id INT NOT NULL REFERENCES credit_card_types,
	 credit_card_number CHAR(16) NOT NULL,
	 expiration_month INT NOT NULL,
	 expiration_year INT NOT NULL,
	 cvv INT,
	 name_on_card CHAR(31) NOT NULL,
	 zip_code CHAR(10) NOT NULL);

CREATE TABLE currency_types
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	name CHAR(20) NOT NULL);

CREATE TABLE order_types
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	name CHAR(20) NOT NULL);
	
CREATE TABLE orders
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	payment_methods_id INT NOT NULL REFERENCES payment_methods,
	order_types_id INT NOT NULL REFERENCES order_types,
	accounts_id INT NOT NULL REFERENCES accounts,
	movies_id INT NOT NULL REFERENCES movies,
	transaction_second INT NOT NULL,
	transaction_minute INT NOT NULL,
	transaction_hour INT NOT NULL,
	transaction_day INT NOT NULL,
	transaction_month INT NOT NULL,
	transaction_year INT NOT NULL);

CREATE TABLE favorites
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	movies_id INT NOT NULL REFERENCES movies,
	accounts_id INT NOT NULL REFERENCES accounts);

-- A user can has to leave a rating, but review is optional
CREATE TABLE reviews
	(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
	accounts_id INT NOT NULL REFERENCES accounts,
	movies_id INT NOT NULL REFERENCES movies,
	review VARCHAR(2048),
	rating INT NOT NULL);

-- Create indexes
ALTER TABLE movie_data 
ADD PRIMARY KEY (id);

ALTER TABLE movies 
ADD PRIMARY KEY (id);

ALTER TABLE movies_cast 
ADD PRIMARY KEY (id);

ALTER TABLE movies_directors 
ADD PRIMARY KEY (id);

ALTER TABLE movies_producers 
ADD PRIMARY KEY (id);

ALTER TABLE movies_writers 
ADD PRIMARY KEY (id);

ALTER TABLE people 
ADD PRIMARY KEY (id);

ALTER TABLE people_info 
ADD PRIMARY KEY (id); 

ALTER TABLE favorites 
ADD CONSTRAINT `movies_id_to_id`
FOREIGN KEY (movies_id) 
REFERENCES movies (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE favorites 
ADD CONSTRAINT `accounts_id_to_id`
FOREIGN KEY (accounts_id) 
REFERENCES accounts (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movie_data
ADD CONSTRAINT `id_to_id`
FOREIGN KEY (id)
REFERENCES movies (id)
ON DELETE CASCADE
ON UPDATE CASCADE;

ALTER TABLE movies_cast CHANGE movie_id movies_id INT;

ALTER TABLE movies_cast CHANGE person_id people_id INT;

ALTER TABLE movies_cast
ADD CONSTRAINT `mc_movies_id_to_id`
FOREIGN KEY (movies_id) 
REFERENCES movies (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_cast
ADD CONSTRAINT `mc_people_id_to_id`
FOREIGN KEY (people_id) 
REFERENCES people (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_directors CHANGE movie_id movies_id INT;

ALTER TABLE movies_directors CHANGE person_id people_id INT;

ALTER TABLE movies_directors
ADD CONSTRAINT `md_movies_id_to_id`
FOREIGN KEY (movies_id) 
REFERENCES movies (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_directors
ADD CONSTRAINT `md_people_id_to_id`
FOREIGN KEY (people_id) 
REFERENCES people (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_info CHANGE movie_id movies_id INT;

ALTER TABLE movies_info
ADD CONSTRAINT `mi_movie_id_to_id`
FOREIGN KEY (movies_id) 
REFERENCES movies (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_producers CHANGE movie_id movies_id INT;

ALTER TABLE movies_producers CHANGE person_id people_id INT;

ALTER TABLE movies_producers
ADD CONSTRAINT `mp_movies_id_to_id`
FOREIGN KEY (movies_id) 
REFERENCES movies (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_producers
ADD CONSTRAINT `mp_people_id_to_id`
FOREIGN KEY (people_id) 
REFERENCES people (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_writers CHANGE movie_id movies_id INT;

ALTER TABLE movies_writers CHANGE person_id people_id INT;

ALTER TABLE movies_writers
ADD CONSTRAINT `mw_movies_id_to_id`
FOREIGN KEY (movies_id) 
REFERENCES movies (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE movies_writers
ADD CONSTRAINT `mw_people_id_to_id`
FOREIGN KEY (people_id) 
REFERENCES people (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

ALTER TABLE people_info CHANGE person_id people_id INT;

ALTER TABLE people_info
ADD CONSTRAINT `pi_people_id_to_id`
FOREIGN KEY (people_id) 
REFERENCES people (id) 
ON DELETE CASCADE 
ON UPDATE CASCADE;

CREATE INDEX title 
ON title(title);

CREATE INDEX name
ON people(first_name, last_name);

CREATE INDEX first_name
ON people(first_name);

CREATE INDEX last_name
ON people(last_name);

