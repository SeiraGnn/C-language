#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// CS50's Pset2 - Substitution: A program that uses a key and plaintext provided by user to encrypt his text.
// Obtains the key through a Command-line argument when running the program.
int main(int argc, string argv[])
{
    // Rejects either no command-line argument, or too many of them. Shows correct usage afterwards.
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Checks that the key is 26-characters long
    if (strlen(argv[1]) != 26)
    {
        printf("Key must be twenty-six-character long.");
        return 1;
    }
    // Checks that letters are not repeated within the key
    int alphabet[26] = {0};
    // For each letter in the key
    for (int i = 0; i < 26; i++)
    {
        int num = 65;
        // Check for a match against all uppercase letters in the alphabet and remember which one appeared with an increase in the "alphabet" array.
        for (int j = 0; j < 26; j++)
        {
            if (argv[1][i] == num)
            {
                alphabet[j]++;
                break;
            }
            num++;
        }
    }
// Nearly identical loop proceeds to check for lowercase instances
    for (int i = 0; i < 26; i++)
    {
        int num = 97;
        for (int j = 0; j < 26; j++)
        {
            if (argv[1][i] == num)
            {
                alphabet[j]++;
                break;
            }
            num++;
        }
    }
// Checks alphabet array to see if any letter was repeated or not used (any value unequal to one) and displays error message
    for (int i = 0; i < 26; i++)
        if (alphabet[i] != 1)
        {
            printf("The key must contain only letters and each must appear only once.\n");
            return 1;
        }
// Get the plaintext from user
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
// Substitute each character by the character from the key
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
// First checks if it's both a letter and lowercase (bc the constant by which you will change the ASCII value will change between cases), then substitutes if so.
        if (isalpha(plaintext[i]) && islower(plaintext[i]))
        {
// If the matching character from the key has a different case, it changes it to match before performing the substitution
            if (isupper(argv[1][(int) plaintext[i] - 97]))
            {
                argv[1][(int) plaintext[i] - 97] = argv[1][(int) plaintext[i] - 97] + 32;
            }
            plaintext[i] = argv[1][(int) plaintext[i] - 97];
            printf("%c", plaintext[i]);
        }
        else
        {
            // Substitutes all uppercase letters
            if (isalpha(plaintext[i]) && isupper(plaintext[i]))
            {
                if (islower(argv[1][(int) plaintext[i] - 65]))
                {
                    argv[1][(int) plaintext[i] - 65] = argv[1][(int) plaintext[i] - 65] - 32;
                }
                plaintext[i] = argv[1][(int) plaintext[i] - 65];
                printf("%c", plaintext[i]);
            }
            // If it's not a letter it will just print it as it was
            else
            {
                printf("%c", plaintext[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
