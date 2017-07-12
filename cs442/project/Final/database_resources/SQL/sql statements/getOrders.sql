SELECT orders.id,
    orders.payment_methods_id,
    orders.order_types_id,
    orders.accounts_id,
    orders.movies_id,
    orders.transaction_second,
    orders.transaction_minute,
    orders.transaction_hour,
    orders.transaction_day,
    orders.transaction_month,
    orders.transaction_year
FROM orders
WHERE orders.accounts_id = 1;