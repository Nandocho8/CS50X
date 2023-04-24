SELECT DISTINCT(p.name) FROM people as p, stars as s on
p.id = s.person_id
WHERE s.movie_id IN
(SELECT s.movie_id FROM people as p, stars as s on
p.id = s.person_id
WHERE s.person_id in (SELECT id FROM people as p where p.name = "Kevin Bacon" and p.birth = 1958) ) and p.name != "Kevin Bacon";
