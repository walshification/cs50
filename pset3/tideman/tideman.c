/**
 * Problem Set 3: Tideman
 * ----------------------
 * Complete the implementation of the Tideman program.
 *
 * More context: https://cs50.harvard.edu/x/2021/psets/3/tideman/
 *
 * Complete the vote function.
 * Complete the record_preferences function.
 * Complete the add_pairs function.
 * Complete the sort_pairs function.
 * Complete the lock_pairs function.
 * Complete the print_winner function.
 */

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
}
pair;

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

// helpers
bool has_no_cycle(int winner, int loser);

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
    for (int i = 0; i < candidate_count; ++i)
    {
        // If name matches a candidate name ...
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update ranks to indicate the voter has the candidate as their rank
            // preference, (where 0 is the first preference, 1 is the second preference,
            // etc.) Recall that ranks[i] here represents the user’s ith preference.
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the global preferences array to add the current voter’s preferences.
    // Recall that preferences[i][j] should represent the number of voters who prefer
    // candidate i over candidate j.
    for (int i = 0; i < candidate_count; ++i)
    {
        for (int j = i + 1; j < candidate_count; ++j)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Fo all candidates ...
    for (int i = 0; i < candidate_count; ++i)
    {
        for (int j = 0; j < candidate_count; ++j)
        {
            // Add all pairs of candidates where one candidate is preferred to the pairs array.
            // A pair of candidates who are tied should not be added to the array.
            if (preferences[i][j] > 0 && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // Update pair_count to be the number of pairs of candidates.
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort the pairs array in decreasing order of strength of victory, where strength
    // of victory is the number of voters who prefer the preferred candidate.
    // If multiple pairs have the same strength, the order does not matter.
    // Begin selection sort.
    for (int i = 0; i < pair_count; ++i)
    {
        int largest_margin = 0;
        pair winningest_pair;
        int former_index;
        for (int j = i; j < pair_count; ++j)
        {
            // Compare margins of victory.
            int winner_pref = preferences[pairs[j].winner][pairs[j].loser];
            int loser_pref = preferences[pairs[j].loser][pairs[j].winner];
            int margin = winner_pref - loser_pref;
            if (margin > largest_margin)
            {
                // For the largest margin (so far), note the margin, which pair it is,
                // and the index for that pair (for swapping).
                largest_margin = margin;
                winningest_pair = pairs[j];
                former_index = j;
            }
        }
        // Remove the current resident of the to-be-sorted index.
        pair to_swap = pairs[i];
        // Replace it with the sorted value.
        pairs[i] = winningest_pair;
        // Slot the pair that was replaces back in the newly-sorted pair's former slot.
        pairs[former_index] = to_swap;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Create the locked graph, adding all edges in decreasing order of victory
    // strength so long as the edge would not create a cycle.
    for (int i = 0; i < pair_count; ++i)
    {
        if (has_no_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // For all the candidates ...
    for (int i = 0; i < candidate_count; ++i)
    {
        // Assume candidate is the source.
        bool is_source = true;
        for (int j = 0; j < candidate_count; ++j)
        {
            // Does any candidate have a locked edge on this candidate?
            if (locked[j][i])
            {
                // If so, this candidate is not the source.
                is_source = false;
            }
        }
        if (is_source)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

/**
 * Function: has_no_cycle
 * ----------------------
 * Verify if the current loser has a locked edge against the current
 * winner; if so, returns false. If not, verifies if any other
 * candidate has a locked edge over the current winner; if so, checks
 * If that new winner has cycles with the current loser.
 * If not, returns true.
 *
 * winner (int): index of the current winner under inspection.
 * loser (int): index of the current loser under inspection.
 *
 * returns: (bool)
 */
bool has_no_cycle(int winner, int loser)
{
    // Base case.
    if (locked[loser][winner])
    {
        return false;
    }

    // For all the candidates ...
    for (int i = 0; i < candidate_count; ++i)
    {
        // Does anyone have a locked edge on the current winner?
        if (locked[i][winner])
        {
            // Does that candidate make a cycle with the current loser?
            return has_no_cycle(i, loser);
        }
    }
    return true;
}
