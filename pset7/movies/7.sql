SELECT m.title, r.rating FROM movies as m , RATINGS as r on
m.id = r.movie_id
WHERE m.year = 2010
ORDER BY r.rating DESC , m.title ASC;