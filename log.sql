-- Keep a log of any SQL queries you execute as you solve the mystery.

-- the theft took place on July 28, 2021
-- on Humphrey Street.

-- execute .table to see all tables in database
-- airports
-- atm_transactions
-- bakery_security_logs
-- bank_accounts
-- crime_scene_reports
-- flights
-- interviews
-- passengers
-- people
-- phone_calls

-- execute .schema

-- select description of crime_scene_reports that occured on july 28, 2021 on humphrey street
SELECT description FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND street = "Humphrey Street"
AND day = 28;
-- This is the description:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted
-- today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- now, we know the theft happened at 10:15am at the bakery, so we will learn more about the activities at the bakery
-- select activity from bakery_security_logs at the time the theft happened to learn more about what happened
SELECT activity FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute = 15;
-- this query didn't help because it only says "entrance" or "exit"
-- and for some reason it doesn't output anything when I include "minute = 15"
-- so i'm going to query about the license plate instead
SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10;
-- this also doesn't help much. I need more background information

-- i'm going to look at the interview transcripts now for that information
SELECT transcript FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;
-- these are the transcripts:

-- Sometime within ten minutes of the theft, I saw the thief get into a car
-- in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in that time frame.                                                          |

-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking
-- by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |

-- As the thief was leaving the bakery, they called someone who talked to them
-- for less than a minute. In the call, I heard the thief say that they were planning
-- to take the earliest flight out of Fiftyville tomorrow. The thief then asked the
-- person on the other end of the phone to purchase the flight ticket.

-- find lincense plate of the car that left within ten mintues of the theft
SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25;
-- this still gives me a lot of plates, so i need to combine different tables together

-- Use the fact that the ATM on Leggett Street was used
SELECT account_number FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = "Leggett Street";
-- this outputs a lot of account numbers

SELECT bakery_security_logs.license_plate FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute > 15
AND bakery_security_logs.minute < 25;
-- got it down to these four license plates:
-- 94KL13X
-- 322W7JE
-- L93JTIZ
-- 4328GD8

-- find info on the earliest flight out of fiftyville
SELECT flights.id FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.city = "Fiftyville"
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute;
-- these are the flight IDs, and the earliest one is flight 36
-- 36
-- 43
-- 23
-- 53
-- 18

-- use all info to find the name of the thief
SELECT people.name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute > 15
AND bakery_security_logs.minute < 25
AND flights.id = 36;
-- results in two suspects:
-- bruce
-- luca

-- use phone_calls to find the theif
SELECT phone_calls.caller FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
AND people.name = "Bruce";
-- query results in nothing when the person's name is luca, so luca is not the theif
-- query results in the phone number (367) 555-5533 when Burce is the name, so burce is the theif

-- find name of accomplice
SELECT people.name FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
AND phone_calls.caller = "(367) 555-5533";
-- accomplice is Robin

-- find flight destination
SELECT airports.city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE flights.id = 36;
-- Thief escaped to NYC