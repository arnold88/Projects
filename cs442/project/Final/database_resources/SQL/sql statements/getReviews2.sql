SELECT reviews.id,
    reviews.accounts_id,
    reviews.movies_id,
    reviews.review,
    reviews.rating
FROM reviews
WHERE reviews.accounts_id = 1;
