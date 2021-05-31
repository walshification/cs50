-- Keep a log of any SQL queries you execute as you solve the mystery.

.tables
-- airports                  crime_scene_reports       people
-- atm_transactions          flights                   phone_calls
-- bank_accounts             interviews
-- courthouse_security_logs  passengers

.schema crime_scene_reports
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );

SELECT description
FROM crime_scene_reports
WHERE year = 2020
  AND month = 7
  AND day = 28
  AND street LIKE "Chamberlin%";
/*
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present at the time
— each of their interview transcripts mentions the courthouse.
*/

.schema courthouse_security_logs
-- CREATE TABLE courthouse_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

SELECT license_plate, activity
FROM courthouse_security_logs
WHERE year = 2020
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute = 15;
-- nothing.

.schema interviews
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );

-- Get the witness statements.
SELECT name, transcript
FROM interviews
WHERE year = 2020
  AND month = 7
  AND day = 28
  AND transcript LIKE "%courthouse%";
-- name | transcript
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the
--       courthouse parking lot and drive away. If you have security footage from the
--       courthouse parking lot, you might want to look for cars that left the parking
--       lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this
--          morning, before I arrived at the courthouse, I was walking by the ATM on Fifer
--          Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to
--           them for less than a minute. In the call, I heard the thief say that they
--           were planning to take the earliest flight out of Fiftyville tomorrow. The
--           thief then asked the person on the other end of the phone to purchase the
--           flight ticket.

-- See if it's obvious from the security logs at the time.
SELECT license_plate
FROM courthouse_security_logs
WHERE year = 2020
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute > 15 <= 25
  AND activity = "exit";
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55
-- 1106N58

.schema atm_transactions
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );

.schema bank_accounts
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );

.schema phone_calls
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );

.schema flights
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );

.schema people
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

.schema airports
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );

.schema flights
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );

.schema passengers
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );

-- Use the witness statements as subqueries to get the name of the thief.
SELECT name
FROM people
WHERE license_plate IN (
  -- Narrow the license plates down to the ones that left the courthouse at the
  -- time of the crime.
  SELECT license_plate
  FROM courthouse_security_logs
  WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25
    AND activity = "exit"
)
  AND people.id IN (
  -- Narrow IDs down to those for people who made withdrawals on Fifer Street on the
  -- day of the crime.
  SELECT person_id
  FROM bank_accounts
  JOIN atm_transactions
    ON atm_transactions.account_number = bank_accounts.account_number
  WHERE year = 2020
    AND month = 7
    AND day = 28
    AND transaction_type = "withdraw"
    AND atm_location = "Fifer Street"
)
  AND phone_number IN (
  -- Narrow the phone numbers down to those of people who made calls on the day of the
  -- crime that lasted less than 60 seconds.
  SELECT caller
  FROM phone_calls
  WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60
)
  AND passport_number IN (
  -- Narrow the passports down to those for passengers on the first flight out of town
  -- the day after the crime.
  SELECT passport_number
  FROM passengers
  WHERE passengers.flight_id IN (
    SELECT flights.id
    FROM flights
    JOIN airports
      ON airports.id = flights.origin_airport_id
    WHERE airports.city = "Fiftyville"
      AND year = 2020
      AND month = 7
      AND day = 29
    ORDER BY hour, minute
    ASC
    LIMIT 1
  )
);
-- name
-- Ernest

-- Given the name of the thief, who did he call on the day of the crime for a call
-- that lasted less than 60 seconds.
SELECT name
FROM people
WHERE phone_number IN (
  SELECT receiver
  FROM phone_calls
  WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (
    SELECT phone_number
    FROM people
    WHERE name = "Ernest"
  )
);
-- name
-- Berthold

-- What is the destination of the first flight out of Fiftyville the day after the crime?
SELECT city
FROM flights
JOIN airports
  ON airports.id = flights.destination_airport_id
WHERE year = 2020
  AND month = 7
  AND day = 29
ORDER BY hour, minute
ASC
LIMIT 1;
-- city
-- London
