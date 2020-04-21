SELECT AVG(rating) FROM ratings WHERE movie_id in (SELECT id FROM movies WHERE year==2012);
