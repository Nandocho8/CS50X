SELECT m.title FROM people as p, stars as s, movies as m , RATINGS as r  on
p.id = s.person_id and s.movie_id = m.id and m.id = r.movie_id
WHERE p.name = "Chadwick Boseman"
ORDER BY r.rating DESC
LIMIT 5;