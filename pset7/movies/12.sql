

SELECT (m.title) FROM people as p, stars as s, movies as m on
p.id = s.person_id and s.movie_id = m.id
Where p.name = "Johnny Depp"


INTERSECT

SELECT (m.title) FROM people as p, stars as s , movies as m on
p.id = s.person_id and s.movie_id = m.id
Where p.name = "Helena Bonham Carter"
ORDER BY m.title;