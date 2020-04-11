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

void mergesort(pair pairs_arr[], int start, int end);
void merge(pair pairs_arr[], int start, int mid, int end);
bool find_cycle(void);
bool visit(int candidate_index, bool visited[], bool rec_visited[]);

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
    for (int i = 0 ; i < candidate_count ; i++)
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
    // Loop through each entry in ranks
    for (int i = 0 ; i < candidate_count ; i++)
    {
        // For each entry ranked lower than ranks[i], add one count to preferences[i][j]
        for (int j = i + 1 ; j < candidate_count ; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    // For each candidate compared to every other candidate
    // If more people choose candidate over other candidate
    // Add pair
    for (int i = 0 ; i < candidate_count; i++)
    {
        for (int j = 1 ; j < candidate_count ; j++)
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
    mergesort(pairs, 0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0 ; i < pair_count ; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (find_cycle())
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Check all candidate vertices for edge from another candidate
    for (int i = 0 ; i < candidate_count ; i++)
    {
        // By default win is true
        bool win = true;

        for (int j = 0 ; j < candidate_count ; j++)
        {
            // If edge from another candidate exists, set win to false
            if (locked[j][i])
            {
                win = false;
                break;
            }
        }

        // If candidate wins, print candidate's name
        if (win)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

void mergesort(pair pairs_arr[], int start, int end)
{
    // If only one item, return
    if (start == end)
    {
        return;
    }

    // Else sort left half of items, sort right half of items and merge sorted halves
    else
    {
        int mid = (start + end) / 2;
        mergesort(pairs_arr, start, mid);
        mergesort(pairs_arr, mid + 1, end);
        merge(pairs_arr, start, mid, end);
    }
}

void merge(pair pairs_arr[], int start, int mid, int end)
{
    // Create placeholder array
    pair sorted_pairs[end - start + 1];
    int pointer1 = start;
    int pointer2 = mid + 1;

    // Run for number of items in array - 1
    for (int i = 0 ; i < end - start + 1 ; i++)
    {
        // If left half of array is empty
        // Add remaining items from right half of array to sorted array
        if (pointer1 == mid + 1)
        {
            sorted_pairs[i] = pairs_arr[pointer2];
            pointer2++;
        }

        // If right half of array is empty
        // Add remaining items from left half of array to sorted array
        else if (pointer2 == end + 1)
        {
            sorted_pairs[i] = pairs_arr[pointer1];
            pointer1++;
        }

        // If first item in left half is smaller than first item in right half
        // Add first item in left half to sorted array
        else if (preferences[pairs_arr[pointer1].winner][pairs_arr[pointer1].loser] >
                 preferences[pairs_arr[pointer2].winner][pairs_arr[pointer2].loser])
        {
            sorted_pairs[i] = pairs_arr[pointer1];
            pointer1++;
        }

        // If first item in right half is smaller than first item in left half
        // Add first item in right half to sorted array
        else if (preferences[pairs_arr[pointer2].winner][pairs_arr[pointer2].loser] >
                 preferences[pairs_arr[pointer1].winner][pairs_arr[pointer1].loser])
        {
            sorted_pairs[i] = pairs_arr[pointer2];
            pointer2++;
        }
    }

    // Assign sorted_pairs array to actual array
    for (int i = 0 ; i < end - start + 1 ; i++)
    {
        pairs_arr[i] = sorted_pairs[i];
    }
}

bool find_cycle(void)
{
    // Declare an array to keep track of visited vertices and sets all values to false
    bool visited[candidate_count];
    for (int i = 0 ; i < candidate_count ; i++)
    {
        visited[i] = false;
    }

    // Declares an array to keep track of visited vertices on current recursion visit
    bool rec_visited[candidate_count];

    // Visit each candidate's vertex
    for (int i = 0 ; i < candidate_count; i++)
    {
        // Reset rec_visited
        for (int j = 0 ; j < candidate_count ; j++)
        {
            rec_visited[j] = false;
        }

        // If candidate vertex has been visited, got to next candidate
        if (visited[i])
        {
            continue;
        }

        // Visit vertex i, returns true if vertex i has been visited
        else if (visit(i, visited, rec_visited))
        {
            return true;
        }
    }
    return false;
}

bool visit(int candidate_index, bool visited[], bool rec_visited[])
{
    // If candidate has already been visited on current recursion, signal cycle
    if (rec_visited[candidate_index])
    {
        return true;
    }

    // Otherwise mark candidate as visited
    else
    {
        visited[candidate_index] = true;
        rec_visited[candidate_index] = true;
    }

    // If lock edge with another candidate exists, visit other candidate
    for (int i = 0 ; i < candidate_count ; i++)
    {
        if (locked[candidate_index][i])
        {
            if (visit(i, visited, rec_visited))
            {
                return true;
            }
            // If backtracked, delete candidate vertex from rec_visited
            else
            {
                rec_visited[i] = false;
            }
        }
    }

    return false;
}
