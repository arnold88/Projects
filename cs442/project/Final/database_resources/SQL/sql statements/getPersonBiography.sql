SELECT people_info.info AS biography
FROM people
INNER JOIN people_info
	ON people.id = people_info.people_id
INNER JOIN info_type 
	ON people_info.info_type_id = info_type.id
WHERE people.id = 215
	AND (info_type.info = 'mini biography');