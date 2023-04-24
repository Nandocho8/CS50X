SELECT DISTINCT(p.name) FROM people as p, stars as s, movies as m on
p.id = s.person_id and s.movie_id = m.id
WHERE m.year = 2004
ORDER BY p.birth;