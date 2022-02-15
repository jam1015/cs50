SELECT movies.title 
FROM movies 
JOIN ratings on ratings.movie_id = movies.id
JOIN stars on stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Chadwick Boseman" 
ORDER BY ratings.rating DESC LIMIT 5;
