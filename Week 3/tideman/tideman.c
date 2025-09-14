#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool isCycle(int winner, int loser);
void print_winner(void);

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
        if (strcmp(candidates[i], name) == 0)
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
    // for every candidate inside ranks
    for (int i = 0; i < candidate_count; i++)
    {
        // compare with every next candidate inside ranks
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; // And then sum 1 in our preferences matrix
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop through all unique candidate pairs
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // if candidate i is preferred over candidate j by more voters
            if (preferences[i][j] > preferences[j][i])
            {
                // record i as the winner and j as the loser
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // if candidate j is preferred over candidate i by more voters
            else if (preferences[j][i] > preferences[i][j])
            {
                // record j as the winner and i as the loser
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory and inverse selection sort
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            // will calculate the strenght of victory by seeing the strenght of the current max
            // value and the current value
            int strength_of_victory = preferences[pairs[max_index].winner][pairs[max_index].loser] -
                                      preferences[pairs[max_index].loser][pairs[max_index].winner];
            int strength_j = preferences[pairs[j].winner][pairs[j].loser] -
                             preferences[pairs[j].loser][pairs[j].winner];
            if (strength_j > strength_of_victory)
            {
                max_index = j;
            }
        }

        // if the current max value isnt in the i index, then change
        if (max_index != i)
        {
            pair temp = pairs[i];
            pairs[i] = pairs[max_index];
            pairs[max_index] = temp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (isCycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool isCycle(int winner, int loser)
{
    // If we ever connect back to the original `winner`, we have a cycle
    if (winner == loser)
    {
        return true;
    }
    // Check all candidates to see if there is a path from `loser` to `winner`
    for (int i = 0; i < candidate_count; i++)
    {
        // If there is a locked edge from `loser` to candidate `i`
        if (locked[loser][i] == true)
        {
            // Recursively check if we can reach the `winner` from candidate `i`
            if (isCycle(winner, i) == true)
            {
                return true; // Cycle found
            }
        }
    }
    // No cycle found
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool aux = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                aux = false;
                break;
            }
        }
        if (aux)
            printf("%s\n", candidates[i]);
    }
    return;
}
