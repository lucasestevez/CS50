SELECT title
	FROM movies m
	JOIN stars s
	ON s.movie_id = m.id
	JOIN people p
	ON s.person_id = p.id
	JOIN ratings r
	ON r.movie_id = m.id
	WHERE p.name = "Chadwick Boseman"
	ORDER by r.rating  DESC
	LIMIT 5;