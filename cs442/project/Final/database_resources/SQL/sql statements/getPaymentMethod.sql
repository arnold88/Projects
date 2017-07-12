SELECT payment_methods.id,
    payment_methods.account_id,
    payment_methods.credit_card_types_id,
    payment_methods.credit_card_number,
    payment_methods.expiration_month,
    payment_methods.expiration_year,
    payment_methods.cvv,
    payment_methods.name_on_card,
    payment_methods.zip_code
FROM payment_methods
WHERE payment_methods.id = 1;