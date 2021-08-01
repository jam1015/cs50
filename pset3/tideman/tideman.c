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
	for (int c = 0; c < candidate_count; c++)
	{
		if (strcmp(name, candidates[c]) == 0)
		{
			ranks[rank] = c;
			return true;
		}
	}
	return false;
}

// Update preferences given one voter's ranks; update record preferences array
// (2 x 2)
void record_preferences(int ranks[])
{
	for (int i = 0; i < candidate_count - 1; i++)
	{
		for (int j = i + 1; j < candidate_count; j++)
		{
			int pref_1 = ranks[i];
			int pref_2 = ranks[j];
			preferences[pref_1][pref_2]++;
		}
	}
	return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)  //# this is the (n)(n-1)/2 array of pairs with names
{
	for (int i = 0; i < candidate_count; i++)
	{
		for (int j = i + 1; j < candidate_count; j++)
		{
			if (preferences[i][j] < preferences[j][i])
			{
				pairs[pair_count].winner = j;
				pairs[pair_count].loser = i;
				pair_count++;
			}
			else if (preferences[i][j] > preferences[j][i])
			{
				pairs[pair_count].winner = i;
				pairs[pair_count].loser = j;
				pair_count++;
			}
			/*
			 printf("%i\n", pair_count);
					printf("winner %i\n", pairs[pair_count].winner);
					printf("loser %i\n", pairs[pair_count].loser);
					printf("\n"); */
		}
	}
	return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
	int difference_array[pair_count];
	for (int j = 0; j < pair_count; j++)
	{
		pair pair_used = pairs[j];
		int winner = pair_used.winner;
		int loser = pair_used.loser;

		int diff = preferences[winner][loser] - preferences[loser][winner];
		difference_array[j] = diff;
	}
	bool sorted = false;

	pair temp_pair;
	int temp_int;
	int first;
	int second;
	while (!sorted)
	{
		sorted = true;
		for (int j = 0; j < pair_count - 1; j++)
		{
			if (difference_array[j + 1] > difference_array[j])
			{
				sorted = false;
				temp_int = difference_array[j + 1];
				temp_pair = pairs[j + 1];

				difference_array[j + 1] = difference_array[j];
				difference_array[j] = temp_int;

				pairs[j + 1] = pairs[j];
				pairs[j] = temp_pair;
			}
		}
	}

	for (int j = 0; j < pair_count; j++)
	{
		//printf("%i\n", difference_array[j]);
	}
	return;
}

bool creates_cycle(int source, int to)
{
	if (to == source)
	{
		return true;
	}

	bool edge_exists;
	for (int j = 0; j < candidate_count; j++)
	{
		if (locked[to][j])
		{
			if (creates_cycle(source, j))
			{
				return true;
			}
		}
	}
	return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
	int from;
	int to;
	for (int j = 0; j < pair_count; j++)
	{
		from = pairs[j].winner;
		to = pairs[j].loser;

		if (!creates_cycle(from, to))
		{
			locked[from][to] = true;
		}
	}

	return;
}

// Print the winner of the election
int find_source(int node)
{
	int source = node;
	for (int i = 0; i < candidate_count; i++)
	{
		if (locked[i][node])
		{
			source = find_source(i);
			return source;
		}
	}
	return source;
}

void print_winner(void)
{
	int source;	 // a candidate whe know at least beats someone
	for (int j = 0; j < candidate_count; j++)
	{
		for (int i = 0; i < candidate_count; i++)
		{
			if (locked[i][j])
			{
				source = find_source(i);
				printf("%s\n", candidates[source]);
				return;
			}
		}
	}
	return;
}
