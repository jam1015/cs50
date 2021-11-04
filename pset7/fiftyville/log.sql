-- took place july 28 2020, on chamberlin st
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- from the above we learned that it took place at 10:15 am; all interviews about this mention courthouse
-- getting the interviews from the courthouse
SELECT * FROM interviews WHERE transcript LIKE "%courthouse%" AND year = 2020 AND month = 7 AND day = 28;


-- from Ruth: want to get the cars around 7 28 2020, within ten minutes of  10:15 am
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- Eugene recognized the thief; atm withdrawals from fifer street on 7 28 2020, before 10:15 am (early in the morning); used this sql query to join those txions to bank acct and the respective people.
SELECT * FROM atm_transactions JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number JOIN people ON people.id = bank_accounts.person_id WHERE atm_location = 'Fifer Street' AND year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw";

-- joined the above on the license plates seen by the courthouse that morning:
SELECT * FROM atm_transactions JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number JOIN people ON people.id = bank_accounts.person_id WHERE atm_location = 'Fifer Street' AND year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 and minute <= 25);

-- Raymond saw thief call someone for less than a minute. he plans to take earliest flight out on 7 29. The person on the other end of the call took bought the tickets. So we can filter for people who made a fall for less than a minute on 2020_7_28, and then filter passengers on the earliest flight out of town from that list, and if that query yields one person, that is the perp;
-- the query that selects phone calls of less than a minute from people who also withdrew from the atm on fifer street on that day and whose license plate was seen outside the courthouse within ten minutes of 7:15
SELECT * FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60 AND people.name IN (
	SELECT name FROM atm_transactions
	JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
	JOIN people ON people.id = bank_accounts.person_id
	WHERE atm_location = 'Fifer Street'
	AND year = 2020
	AND month = 7
	AND day = 28
	AND transaction_type = "withdraw"
	AND people.license_plate IN (
		SELECT license_plate FROM courthouse_security_logs
		WHERE year = 2020
		AND month = 7
		AND day = 28
		AND hour = 10
		AND minute >= 15
		AND minute <= 25)
);

-- The above narrows it down to two people for the perp. We can also use this query to find candidates for the accomplice.

-- now we can filter this for people who were on the earliest flight out of town who could be the perp

SELECT * FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN
	(SELECT flights.id FROM flights
	JOIN airports on airports.id = flights.origin_airport_id 
	WHERE year = 2020
	AND month = 7
	AND day = 29
	AND abbreviation = "CSF"
	ORDER BY ((hour * 60) + minute) LIMIT 1)
    AND
	passengers.passport_number IN (
SELECT people.passport_number FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60 AND people.name IN (
	SELECT name FROM atm_transactions
	JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
	JOIN people ON people.id = bank_accounts.person_id
	WHERE atm_location = 'Fifer Street'
	AND year = 2020
	AND month = 7
	AND day = 28
	AND transaction_type = "withdraw"
	AND people.license_plate IN (
		SELECT license_plate FROM courthouse_security_logs
		WHERE year = 2020
		AND month = 7
		AND day = 28
		AND hour = 10
		AND minute >= 15
		AND minute <= 25)
)
	);

-- We see that the guy was ernest now we have to find where that flight was going
SELECT * FROM airports WHERE id IN (SELECT destination_airport_id FROM flights
        JOIN airports on airports.id
        WHERE year = 2020
        AND month = 7
        AND day = 29
        AND abbreviation = "CSF"
        ORDER BY ((hour * 60) + minute) LIMIT 1);

-- It was heathrow

-- To find the identity of the accomplice we can look at who the perp called
SELECT * FROM phone_calls
JOIN people ON people.phone_number = phone_calls.receiver
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60 AND phone_calls.caller IN (
SELECT phone_number FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN
	(SELECT flights.id FROM flights
	JOIN airports on airports.id = flights.origin_airport_id 
	WHERE year = 2020
	AND month = 7
	AND day = 29
	AND abbreviation = "CSF"
	ORDER BY ((hour * 60) + minute) LIMIT 1)
    AND
	passengers.passport_number IN (
SELECT people.passport_number FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60 AND people.name IN (
	SELECT name FROM atm_transactions
	JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
	JOIN people ON people.id = bank_accounts.person_id
	WHERE atm_location = 'Fifer Street'
	AND year = 2020
	AND month = 7
	AND day = 28
	AND transaction_type = "withdraw"
	AND people.license_plate IN (
		SELECT license_plate FROM courthouse_security_logs
		WHERE year = 2020
		AND month = 7
		AND day = 28
		AND hour = 10
		AND minute >= 15
		AND minute <= 25)
)
	)
);


-- shwing the accomplice was berthold

