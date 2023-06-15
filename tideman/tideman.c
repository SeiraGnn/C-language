#include <cs50.h>
#include <stdio.h>
#include <string.h>

// A program that runs a Tideman election

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];

pair pairs[MAX * (MAX - 1) / 2];

// Global variables
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle_check(int w, int l);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            preferences[ranks[j]][ranks[k]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int a = 0; a < candidate_count - 1; a++)
    {
        for (int b = 1; b < candidate_count; b++)
        {
            if (preferences[a][b] > preferences[b][a])
            {
                pairs[pair_count].winner = a;
                pairs[pair_count].loser = b;

                pair_count++;
            }

            else if (preferences[a][b] < preferences[b][a])
            {
                pairs[pair_count].winner = b;
                pairs[pair_count].loser = a;

                pair_count++;
            }
        }
    }
    return;
}

// Bubble sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int n = 0;
    int n1 = 0;

    for (int a = 0; a < pair_count; a++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] <= preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                // Store the value before it's swapped in the sort
                n = pairs[i].winner;
                n1 = pairs[i].loser;

                // Perform swap
                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;

                pairs[i + 1].winner = n;
                pairs[i + 1].loser = n1;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (cycle_check(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Checks that no cycle is created if an edge is locked
bool cycle_check(int w, int l)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][w])
        {
            if (i == l)
            {
                return false;
            }

            if (cycle_check(i, l) == false)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return true;
}

// Print the winner of the election
void print_winner(void)
{
    // draft
    for (int i = 0; i < candidate_count; i++)
    {
        int lock = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                lock++;
                break;
            }
        }

        if (lock == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
