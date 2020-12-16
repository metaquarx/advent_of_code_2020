// Copyright 2020 metaquarx, metaquarx@pm.me

//  This file is part of advent_of_code_2020.
//
//  advent_of_code_2020 is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  advent_of_code_2020 is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with advent_of_code_2020.  If not, see
//  <https://www.gnu.org/licenses/>.

#include "day_16.hpp"

#include <algorithm>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <iostream>

class tickets {
public:
	tickets() : rules({}), my_ticket({}), nearby_tickets({}) {}
	std::unordered_map<std::string, std::vector<std::pair<unsigned, unsigned>>>
	  rules;

	std::vector<unsigned> my_ticket;
	std::vector<std::vector<unsigned>> nearby_tickets;
};

static tickets get_input(std::string &input) {
	tickets output;

	std::regex rule("([a-z ]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");

	std::string temp;
	std::istringstream ss;
	ss.str(input);
	bool your_ticket = false;
	bool nearby_tickets = false;
	while (std::getline(ss, temp)) {
		if (temp == "your ticket:") {
			your_ticket = true;
		} else if (temp == "nearby tickets:") {
			nearby_tickets = true;
		} else if (nearby_tickets) {
			std::vector<unsigned> line;
			std::replace(temp.begin(), temp.end(), ',', '\n');
			std::stringstream ss2;
			ss2 << temp;
			unsigned temp2;
			while (ss2 >> temp2) {
				line.push_back(temp2);
			}
			output.nearby_tickets.push_back(line);
		} else if (your_ticket) {
			std::replace(temp.begin(), temp.end(), ',', '\n');
			std::stringstream ss2;
			ss2 << temp;
			unsigned temp2;
			while (ss2 >> temp2) {
				output.my_ticket.push_back(temp2);
			}
		} else {
			std::smatch mtch;
			if (std::regex_match(temp, mtch, rule)) {
				output.rules.emplace(std::make_pair(
				  mtch[1], std::vector<std::pair<unsigned, unsigned>>()));
				output.rules[mtch[1]].push_back(
				  {std::stoi(mtch[2]), std::stoi(mtch[3])});
				output.rules[mtch[1]].push_back(
				  {std::stoi(mtch[4]), std::stoi(mtch[5])});
			}
		}
	}

	return output;
}

std::string day_16::part_a(std::string input) {
	auto all = get_input(input);

	unsigned total = 0;

	for (auto &ticket : all.nearby_tickets) {
		for (auto &entry : ticket) {
			bool matched = false;
			for (auto &rule : all.rules) {
				for (auto &range : rule.second) {
					if (entry >= range.first && entry <= range.second) {
						matched = true;
					}
				}
			}

			if (!matched) {
				total += entry;
				break;
			}
		}
	}

	return std::to_string(total);
}


std::string day_16::part_b(std::string input) {
	auto all = get_input(input);

	for (auto ticket = all.nearby_tickets.begin();
		 ticket != all.nearby_tickets.end();) {
		bool rm = false;
		for (auto &entry : *ticket) {
			bool matched = false;
			for (auto &rule : all.rules) {
				for (auto &range : rule.second) {
					if (entry >= range.first && entry <= range.second) {
						matched = true;
					}
				}
			}

			if (!matched) {
				rm = true;
				break;
			}
		}

		if (rm) {
			ticket = all.nearby_tickets.erase(ticket);
		} else {
			ticket++;
		}
	}

	std::vector<std::vector<std::string>> possibilities;

	for (unsigned i = 0; i < all.nearby_tickets[0].size(); i++) {
		possibilities.push_back({});
		for (auto &rule : all.rules) {
			bool all_matched = true;
			for (auto &row : all.nearby_tickets) {
				bool matched = false;

				for (auto &range : rule.second) {
					if (row[i] >= range.first && row[i] <= range.second) {
						matched = true;
					}
				}

				if (!matched) {
					all_matched = false;
				}
			}

			if (all_matched) {
				possibilities[i].push_back(rule.first);
			}
		}
	}

	while (true) {
		bool all_good = true;
		for (unsigned i = 0; i < possibilities.size(); i++) {
			if (possibilities[i].size() == 1) {
				for (unsigned j = 0; j < possibilities.size(); j++) {
					if (j != i) {
						possibilities[j].erase(
						  std::remove(possibilities[j].begin(),
									  possibilities[j].end(),
									  possibilities[i][0]),
						  possibilities[j].end());
					}
				}
			} else {
				all_good = false;
			}
		}

		if (all_good) {
			unsigned long total = 1;

			for (unsigned i = 0; i < possibilities.size(); i++) {
				if (possibilities[i][0].rfind("departure", 0) == 0) {
					total *= all.my_ticket[i];
				}
			}

			return std::to_string(total);
		}
	}
}
