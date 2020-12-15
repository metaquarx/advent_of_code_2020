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

#include "day_11.hpp"

#include <sstream>
#include <utility>
#include <vector>

#include <iostream>

enum class tile { floor, empty_seat, occupied_seat };

static std::vector<std::vector<tile>> get_layout(std::string input) {
	std::vector<std::vector<tile>> output;

	std::istringstream iss(input);
	std::string line;
	while (std::getline(iss, line)) {
		std::vector<tile> ret = {};

		std::stringstream ss;
		ss << line;
		char temp;
		while (ss >> temp) {
			switch (temp) {
				case '.': ret.push_back(tile::floor); break;
				case 'L': ret.push_back(tile::empty_seat); break;
				case '#': ret.push_back(tile::occupied_seat); break;
			}
		}

		output.push_back(ret);
	}

	return output;
}

static unsigned count_changes(const std::vector<std::vector<tile>> &lhs,
							  const std::vector<std::vector<tile>> &rhs) {
	unsigned total = 0;

	for (unsigned i = 0; i < lhs.size(); i++) {
		for (unsigned j = 0; j < lhs[i].size(); j++) {
			if (lhs[i][j] != rhs[i][j]) {
				total++;
			}
		}
	}

	return total;
}

static unsigned count_adjacent(const std::vector<std::vector<tile>> &seats,
							   unsigned x,
							   unsigned y,
							   tile target) {
	unsigned total = 0;

	if (y > 0 && seats[y - 1][x] == target) {
		total++;
	}

	if (x > 0 && seats[y][x - 1] == target) {
		total++;
	}

	if (y < seats.size() - 1 && seats[y + 1][x] == target) {
		total++;
	}

	if (x < seats[y].size() - 1 && seats[y][x + 1] == target) {
		total++;
	}

	if (y > 0 && x > 0 && seats[y - 1][x - 1] == target) {
		total++;
	}

	if (x > 0 && y < seats.size() - 1 && seats[y + 1][x - 1] == target) {
		total++;
	}

	if (y > 0 && x < seats[y].size() - 1 && seats[y - 1][x + 1] == target) {
		total++;
	}

	if (y < seats.size() - 1 && x < seats[y].size() - 1
		&& seats[y + 1][x + 1] == target) {
		total++;
	}

	return total;
}

std::string day_11::part_a(std::string input) {
	auto layout = get_layout(input);

	std::vector<std::vector<tile>> old;
	do {
		old = layout;

		for (unsigned y = 0; y < old.size(); y++) {
			for (unsigned x = 0; x < old[0].size(); x++) {
				if (old[y][x] == tile::empty_seat) {
					if (count_adjacent(old, x, y, tile::occupied_seat) == 0) {
						layout[y][x] = tile::occupied_seat;
					}
				}

				if (old[y][x] == tile::occupied_seat) {
					if (count_adjacent(old, x, y, tile::occupied_seat) >= 4) {
						layout[y][x] = tile::empty_seat;
					}
				}
			}
		}
	} while (count_changes(old, layout) != 0);

	unsigned total = 0;
	for (auto &line : layout) {
		for (auto &square : line) {
			if (square == tile::occupied_seat) {
				total++;
			}
		}
	}

	return std::to_string(total);
}

static unsigned count_visible(const std::vector<std::vector<tile>> &seats,
							  int x,
							  int y) {
	std::vector<std::pair<short, short>> directions = {
	  {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

	int maxiy = static_cast<int>(seats.size());
	int maxix = static_cast<int>(seats[0].size());

	unsigned total = 0;
	for (auto &dir : directions) {
		int cy = dir.first;
		int cx = dir.second;

		for (int ty = y + cy, tx = x + cx;
			 ty >= 0 && ty < maxiy && tx >= 0 && tx < maxix;
			 ty += cy, tx += cx) {
			if (seats[static_cast<unsigned>(ty)][static_cast<unsigned>(tx)]
				== tile::empty_seat) {
				break;
			} else if (seats[static_cast<unsigned>(ty)]
							[static_cast<unsigned>(tx)]
					   == tile::occupied_seat) {
				total++;
				break;
			}
		}
	}

	return total;
}

std::string day_11::part_b(std::string input) {
	auto layout = get_layout(input);

	std::vector<std::vector<tile>> old;
	do {
		old = layout;

		for (unsigned y = 0; y < old.size(); y++) {
			for (unsigned x = 0; x < old[0].size(); x++) {
				if (old[y][x] == tile::empty_seat) {
					if (count_visible(old, static_cast<int>(x),
									  static_cast<int>(y))
						== 0) {
						layout[y][x] = tile::occupied_seat;
					}
				}

				if (old[y][x] == tile::occupied_seat) {
					if (count_visible(old, static_cast<int>(x),
									  static_cast<int>(y))
						>= 5) {
						layout[y][x] = tile::empty_seat;
					}
				}
			}
		}
	} while (count_changes(old, layout) != 0);

	unsigned total = 0;
	for (auto &line : layout) {
		for (auto &square : line) {
			if (square == tile::occupied_seat) {
				total++;
			}
		}
	}

	return std::to_string(total);
}
