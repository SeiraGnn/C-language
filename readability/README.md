This program estimates the grade level required to comprehend a given text. 
Your first intuition on how to assess a text's level would be to employ a human expert to read it and pass judgement; 
nevertheless, how could one go about achieving this programmatically?
It turns out this can be done by first breaking up the text into its different level components: sentences, words, letters.
Then you can analyze the complexity of an element in each level, in terms of the the level preceding it.
To make it clear, a sentence's complexity is analyzed by counting the number of words it contains, and the complexity of each word by the number of letters in it.
Longer words and longer sentences correlate with higher reading levels. 
This program calculates the (U.S.) grade level for a given text using the following formula, called the Coleman-Liau index.

index = 0.0588 * L - 0.296 * S - 15.8

where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
