SELECT name
	FROM people p
	JOIN directors d
	ON p.id = d.person_id
	JOIN movies m
	ON d.movie_id = m.id
	JOIN ratings r
	ON r.movie_id = m.id
	WHERE r.rating >= 9.0
	GROUP by d.person_id;