#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// CS50's Pset 2 - Readability: A program that assesses which academic grade is best suited for understanding the user's text input
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    // Gets the text from the user
    string text = get_string("Text: ");

    // Obtain the number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Get the avg letters & sentences per 100 words
    float avg_letters = (float) letters / (float) words * 100;
    float avg_sentences = (float) sentences / (float) words * 100;

    // Calculate the Coleman-Liau index
    float index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;

    // Sets a minimum and max levels and successfully exits the program
    if (index < 1)
    {
        printf("Before Grade 1\n");
        return (0);
    }

    if (index >= 16)
    {
        printf("Grade 16+\n");
        return (0);
    }

    // Displays the grades between min and max
    printf("Grade %.0f\n", index);
}

// Define a function that counts the number of alphabetical letters in a text
int count_letters(string s)
{
    int letters = 0;
// Iterates for each char of the string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Checks if the char is alphabetic and counts it inside a variable if so
        if (isalpha(s[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Define a function that counts the number of words in a text
int count_words(string s)
{
    int words = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isspace(s[i]) && !isspace(s[i - 1]))
        {
            words++;
        }
    }
    words++;
    return words;
}

// Define a function that counts the number of sentences in a text
int count_sentences(string s)
{
    int sentences = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}
