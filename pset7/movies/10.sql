SELECT DISTINCT(p.name) FROM people as p, directors as d, movies as m , RATINGS as r  on
p.id = d.person_id and d.movie_id = m.id and m.id = r.movie_id
WHERE r.rating >= 9.0
ORDER BY r.rating DESC , m.title ASC;