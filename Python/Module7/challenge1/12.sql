SELECT movies.title
	FROM people p
	JOIN stars s
	ON p.id = s.person_id
	JOIN movies m
	ON s.movie_id = m.id
WHERE people.name = "Johnny Depp"
AND movies.title
IN(
SELECT movies.title
	FROM people p
	JOIN stars s
	ON p.id = s.person_id
	JOIN movies m
	ON s.movie_id = m.id
WHERE people.name = "Helena Bonham Carter")