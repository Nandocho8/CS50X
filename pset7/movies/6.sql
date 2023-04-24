SELECT AVG(r.rating) FROM movies as m join ratings as r on r.movie_id = m.id where m.year = 2012;
