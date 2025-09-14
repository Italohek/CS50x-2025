SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name IN ('Bradley Cooper', 'Jennifer Lawrence')
GROUP BY movies.title HAVING COUNT(DISTINCT people.name) = 2;
