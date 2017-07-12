SELECT reviews.id,
    reviews.accounts_id,
    reviews.movies_id,
    reviews.review,
    reviews.rating
FROM reviews
WHERE reviews.movies_id = 2091077;
