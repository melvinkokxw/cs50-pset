SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars where person_id in (SELECT id FROM people WHERE name=="Johnny Depp" OR name=="Helena Bonham Carter") GROUP BY movie_id HAVING COUNT(movie_id)==2);
