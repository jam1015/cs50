SELECT people.name
FROM movies 
JOIN stars on stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE (people.name != "Kevin Bacon" OR people.birth != 1958 ) AND movies.title IN(
SELECT movies.title
FROM movies 
JOIN stars on stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE (people.name = "Kevin Bacon" AND people.birth = 1958 )
);

