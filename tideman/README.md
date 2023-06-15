Skills used: Graph theory / Recursive functions / Structs / 2D arrays / Bubble sort

This project simulates an electoral system called Ranked Pairs or also the Tideman method. Developed in 1987 by Nicolaus Tideman, 
this method, selects a single winner using votes that express preferences.

I loved this problem because it offers an alternative solution to the very important and complex problem of how to select our leaders. 
A problem with bi-partisan voting, as in the US (democrats and republicans), is that you constraint the candidates to just two sides of the political spectrum. 
You might think it's just a matter of adding more parties into the system, but even in countries where elections happen this way, 
like in our neighboring Mexico, savvy voters avoid voting for their preferred candidate if they see he has no reasonable chances of winning, 
and vote for the least bad candidate of the reamining options. 
Not only can this lead to a winner whom the majority doesn't truly prefer, but it also leads to elections ruled by only two prevailing parties, 
essentially recurring back to the initial problem.

But the Tideman voting system works differently. In a Tideman system, voters can vote for more than one candidate.
Instead of just voting for their top choice, they can rank the candidates in order of preference.
This way you give a voice to the minorities who prefer a 3rd or 4th candidate over the 1st (when ranked by only votes on number 1 spot).
You can also extract information on which candidate voters prefer when faced off in pairs 1 vs 1; 
hence the name 'ranked pairs'.

Another thing I loved about this project is that it was extremely hard to envision how to make
my algorithm traverse the votes, adding pairs of preferences and locking them in such a way that ensures a winner.
As you can already intuit, this voting mehtod is quite complicated, and even getting to understand how it works in detail can be a bit of a hassle.
So I'll attempt to explain it as briefly as possible, but if you're interested in learning more about
this fascinating topic, you're welcome to read:
1. The originating course's full specifications for the project at https://cs50.harvard.edu/x/2023/psets/3/tideman/
2. This great educative video at https://www.youtube.com/watch?v=PaxVCsnox_4

So, generally speaking, the Tideman method works by constructing a “graph” of 
candidates, where an arrow (i.e. edge) from candidate A to candidate B indicates 
that candidate A wins against candidate B in a head-to-head matchup.
The final graph for a hypothetical election, then, might look like the below, with Nashville, as the root of all edges, being the winner.

This process consists of 3 steps:
Tally: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
Sort: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.
Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.

Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner!

USAGE:

./tideman Alice Bob Charlie

Number of voters: 5

Rank 1: Alice

Rank 2: Charlie

Rank 3: Bob


Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Winner is Charlie!
