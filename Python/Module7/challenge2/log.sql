-- Keep a log of any SQL queries you execute as you solve the mystery.
--Scene crime:
  SELECT * FROM crime_scene_reports
	    WHERE street = "Humphrey Street";

--  Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--  Interviews were conducted today with three witnesses
--  who were present at the time – each of their interview transcripts mentions the bakery.

----------------------------------------------------------------------------------------------------------------------

--Interviews:
 SELECT * FROM interviews
	W HERE transcript like "%bakery%";

--  Ruth - bakery footage:
      SELECT *
	        FROM bakery_security_logs bsl
	        JOIN people p
	        ON bsl.license_plate = p.license_plate
	        WHERE day = 28
	        AND month = 7
	        AND year = 2023
	        AND hour = 10
	        AND minute BETWEEN 15 AND 25;

--  Eugene - ATM, Leggett Street:
      SELECT *
          FROM atm_transactions
	        WHERE day = 28
	        AND month = 7
	        AND year = 2023
	        AND atm_location = "Leggett Street"
	        AND transaction_type = "withdraw";

--  Raymond - short phone, flight ticket:
--      Phone:
          SELECT *
	            FROM people p
	            JOIN phone_calls pc
	            ON p.phone_number = pc.caller
	            WHERE day = 28
	            AND month = 7
	            AND year = 2023
	            AND duration < 60;

--      Ticket:
            SELECT f.*, origin.full_name AS origin_airport, destination.full_name AS destination_airport
                FROM flights f
                JOIN airports origin
                ON f.origin_airport_id = origin.id
                JOIN airports destination
                ON f.destination_airport_id = destination.id
                WHERE origin.id = 8
                AND f.year = 2023
                and f.month = 7
                and f.day = 29
                ORDER by f.hour, f.minute;
----------------------------------------------------------------------------------------------------------------------

--Combine info from all three testimonies:
    SELECT p.name
        FROM bakery_security_logs bsl
        JOIN people p
        ON p.license_plate = bsl.license_plate
        JOIN bank_accounts ba
        ON ba.person_id = p.id
        JOIN atm_transactions atr
        ON atr.account_number = ba.account_number
        JOIN phone_calls pc
        ON pc.caller = p.phone_number
        WHERE bsl.year = 2023 AND bsl.month = 7 AND bsl.day = 28 AND bsl.hour = 10
        AND bsl.minute BETWEEN 15 and 25 AND atr.atm_location = "Leggett Street"
        AND atr.year = 2023 AND atr.month = 7 AND atr.day = 28 AND atr.transaction_type = "withdraw"
        AND pc.year = 2023 AND pc.month = 7 and pc.day = 28 = pc.duration < 60;
        GROUP by p.id;
----------------------------------------------------------------------------------------------------------------------

--Narrow down from Bruce/Daina/Amon/Luca who is on flight:
    SELECT p.name
        FROM people p
        JOIN passengers ps
        ON ps.passport_number = p.passport_number
        WHERE ps.flight_id = 36
        AND p.name IN("Bruce", "Daina", "Amon", "Luca");

