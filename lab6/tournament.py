# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

	# Ensure correct usage
	if len(sys.argv) != 2:
		sys.exit("Usage: python tournament.py FILENAME")

	teams = [] # each team is a dictionary
	with open(sys.argv[1]) as file:
		reader = csv.DictReader(file)
		#next(reader)
		for row in reader:
			row["rating"] = int(row["rating"])
			teams.append(row)



	counts = {} # counts is a dictionary that names to how many times a team wins the tournament
	# TODO: Simulate N tournaments and keep track of win counts
	for i in range(N):
		winner = simulate_tournament(teams)
		if not winner["team"] in counts:
			counts[winner["team"]] = 0
		else:
			counts[winner["team"]] += 1


	# Print each team's chances of winning, according to simulation
	for team in sorted(counts, key=lambda team: counts[team], reverse=True):
		print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
	"""Simulate a game. Return True if team1 wins, False otherwise."""
	rating1 = team1["rating"]
	rating2 = team2["rating"]
	probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
	return random.random() < probability


def simulate_round(teams):
	"""Simulate a round. Return a list of winning teams."""
	winners = []

	# Simulate games for all pairs of teams
	#print(len(teams))
	for i in range(0, len(teams), 2):
		#print(i)
		if simulate_game(teams[i], teams[i + 1]):
			winners.append(teams[i])
		else:
			winners.append(teams[i + 1])

	return winners


def simulate_tournament(teams):
	"""Simulate a tournament. Return name of winning team."""
	# TODO
	while len(teams) > 1:
		teams = simulate_round(teams)
	return teams[0]


if __name__ == "__main__":
	main()
