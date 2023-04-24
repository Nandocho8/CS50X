-- Keep a log of any SQL queries you execute as you solve the mystery.
-- find info the theft
/*
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 07 AND day = 28 AND street = "Humphrey Street";
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| 297 | 2021 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/
-- find interviews
/*SELECT TRANSCRIPT FROM INTERVIEWS
WHERE year = 2021 AND month = 07 AND day = 28;
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                                     transcript                                                                                                                                                      |
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- find ATM on Leggett SStreet and flight of 7/29
SELECT p.name, p.passport_number , p. phone_number FROM atm_transactions as a, bank_accounts as b, people as p
ON
a.account_number = b.account_number and b.person_id = p.id

WHERE a.year = 2021 AND a.month = 07 AND a.day = 28 and a.atm_location = "Leggett Street" and a.transaction_type = "withdraw";

+---------+-----------------+----------------+
|  name   | passport_number |  phone_number  |
+---------+-----------------+----------------+
| Bruce   | 5773159633      | (367) 555-5533 |
| Diana   | 3592750733      | (770) 555-1861 |
| Brooke  | 4408372428      | (122) 555-4581 |
| Kenny   | 9878712108      | (826) 555-1652 |
| Iman    | 7049073643      | (829) 555-5269 |
| Luca    | 8496433585      | (389) 555-5198 |
| Taylor  | 1988161715      | (286) 555-6063 |
| Benista | 9586786673      | (338) 555-6650 |
+---------+-----------------+----------------+
*/

SELECT p.name FROM atm_transactions as a, bank_accounts as b, people as p
ON
a.account_number = b.account_number and b.person_id = p.id

WHERE a.year = 2021 AND a.month = 07 AND a.day = 28 and a.atm_location = "Leggett Street" and a.transaction_type = "withdraw"

/*
+---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+
*/

INTERSECt

SELECT pe.name FROM passengers as p, flights as f, airports as a , people as pe ON
p.flight_id = f.id and a.id = f.origin_airport_id and p.passport_number = pe.passport_number
WHERE f.day = 29 and f.month = 07 and f.year = 2021 AND F. hour < 12 and f.origin_airport_id = (select id from airports where city = "Fiftyville")
/*
+---------+------------------------+
|  name   | destination_airport_id |
+---------+------------------------+
| Doris   | 4                      |
| Sofia   | 4                      |
| Bruce   | 4                      |
| Edward  | 4                      |
| Kelsey  | 4                      |
| Taylor  | 4                      |
| Kenny   | 4                      |
| Luca    | 4                      |
| Daniel  | 1                      |
| Carol   | 1                      |
| Rebecca | 1                      |
| Sophia  | 1                      |
| Heather | 1                      |
| Marilyn | 1                      |
+---------+------------------------+
*/
INTERSECT

SELECT p.name FROM PHONE_CALLS as c, people as p on
c.caller = p.phone_number
 WHERE YEAR = 2021 AND MONTH=07 AND DAY = 28 AND DURATION < 60
/*
+---------+----------------+----------------+
|  name   |     caller     |    receiver    |
+---------+----------------+----------------+
| Sofia   | (130) 555-0289 | (996) 555-8899 |
| Kelsey  | (499) 555-9472 | (892) 555-8872 |
| Bruce   | (367) 555-5533 | (375) 555-8161 |
| Kelsey  | (499) 555-9472 | (717) 555-1342 |
| Taylor  | (286) 555-6063 | (676) 555-6554 |
| Diana   | (770) 555-1861 | (725) 555-3243 |
| Carina  | (031) 555-6622 | (910) 555-3251 |
| Kenny   | (826) 555-1652 | (066) 555-9701 |
| Benista | (338) 555-6650 | (704) 555-2131 |
+---------+----------------+----------------+
*/
intersect

select p.name from bakery_security_logs as l, people as p
on p.license_plate = l.license_plate
 where l.day = 28 and l.month = 7 and l.activity = "exit" and l.hour = 10 and l.minute > 15 and l.minute < 35;

/*+---------+
|  name   |
+---------+
| Vanessa |
| Bruce   |
| Barry   |
| Luca    |
| Sofia   |
| Iman    |
| Diana   |
| Kelsey  |
+---------+
*/
/*
+--------+
|  name  |
+--------+
| Bruce  |
+--------+
*/