SELECT accounts.id,
    accounts.first_name,
    accounts.middle_name,
    accounts.last_name,
    accounts.address_1,
    accounts.address_2,
    accounts.city,
    accounts.state,
    accounts.zip_code,
    accounts.username,
    accounts.password
FROM accounts
WHERE accounts.id = 1
LIMIT 1;