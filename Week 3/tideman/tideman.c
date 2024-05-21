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
    // TODO
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++) // Start from i + 1 to avoid self-comparison
        {
            int preferred_candidate = ranks[i];      // Candidate preferred at rank i
            int less_preferred_candidate = ranks[j]; // Candidate preferred at rank j

            // Increment preference count for preferred_candidate over less_preferred_candidate
            preferences[preferred_candidate][less_preferred_candidate]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort algorithm to sort pairs in decreasing order by margin of victory
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int margin1 = preferences[pairs[j].winner][pairs[j].loser] -
                          preferences[pairs[j].loser][pairs[j].winner];
            int margin2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] -
                          preferences[pairs[j + 1].loser][pairs[j + 1].winner];

            // Swap pairs if the margin of victory is greater for the next pair
            if (margin1 < margin2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}
bool dfs(int candidate, bool visited[])
{
    // If this candidate has already been visited, return false (indicating a cycle)
    if (visited[candidate])
    {
        return false;
    }

    // Mark this candidate as visited
    visited[candidate] = true;

    // Recursively visit all candidates this candidate defeats
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[candidate][i] && !dfs(i, visited))
        {
            return false; // If a cycle is found in the subtree, return false
        }
    }

    return true; // No cycle found for this candidate
}

// Function to check if locking the current pair creates a cycle in the graph
bool cycle_exists(int winner, int loser)
{
    // Mark all candidates as not visited
    bool visited[MAX];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }

    // Temporarily lock the current pair
    locked[winner][loser] = true;

    // Perform DFS from the loser candidate
    bool cycle = !dfs(loser, visited);

    // Unlock the current pair
    locked[winner][loser] = false;

    return cycle;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Lock the current pair only if it doesn't create a cycle
        if (!cycle_exists(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}
// Print the winner of the election
void print_winner(void)
{
    // Array to keep track of whether a candidate is a winner (initially all true)
    bool is_winner[MAX];
    for (int i = 0; i < candidate_count; i++)
    {
        is_winner[i] = true;
    }

    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate i is defeated by any other candidate
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) // If candidate j defeats candidate i
            {
                is_winner[i] = false; // Candidate i is not the winner
                break;
            }
        }
    }

    // Print the winner(s)
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_winner[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
}
