SELECT DISTINCT name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON movies.id = stars.movie_id WHERE movies.id IN
(
    SELECT movies.id FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE name = 'Kevin Bacon' AND birth = 1958
)
AND name != 'Kevin Bacon';
