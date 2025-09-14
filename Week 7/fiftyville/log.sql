-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year = 2024 and month = 7 and day = 28;
SELECT * FROM interviews WHERE year = 2024 and month = 7 and day = 28;
SELECT * FROM bakery_security_logs WHERE year = 2024 and month = 7 and day = 28;
SELECT * FROM atm_transactions WHERE year = 2024 and month = 7 and day = 28 and atm_location = 'Leggett Street';
SELECT * FROM phone_Calls WHERE year = 2024 and month = 7 and day = 28 and duration < 60;
SELECT * FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2024 AND duration < 60);
SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2024 AND duration < 60);
SELECT * FROM bank_accounts WHERE person_id IN (398010, 514354, 560886, 686048);
SELECT * FROM flights WHERE month = 7 AND day = 29 AND year = 2024;
SELECT * FROM airports WHERE id IN (6, 11, 4, 1, 9);
SELECT * FROM passengers WHERE flight_id = 36 AND passport_number IN (5773159633, 3592750733);
