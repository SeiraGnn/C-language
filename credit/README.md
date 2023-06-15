TITLE: Credit

USAGE: 

$ ./credit

Number: 4003600000000014


If you received a credit card number for a purchase, how would you quickly determine if it's a valid number or if it has a typo -- perhaps even an attempt at fraud?

Querying a large database could prove too slow. Instead, you can encode information in the credit-card numbers themselves when they're issued.
A 'checksum' encodes a mathematical relationship between the numbers that enables computers (or humans who like math)
to determine if a credit card number is (syntactically) valid, much quicker. 
Most cards use an algorithm invented by Hans Peter Luhn of IBM thatyou can check as follows:

1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
2. Add the sum to the sum of the digits that weren’t multiplied by 2.
3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

Companies also follow certain patterns to make recognizing the issuer easy. All American Express numbers start with 34 or 37, for example.

# CREDIT is a program that prompts the user for a credit card number and then uses Luhn's algorithm to identify which company it belongs to (AMEX, VISA, etc.) or if it's an INVALID credit card number.
