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

#include "day_5.hpp"

#include <cmath>
#include <vector>

static std::vector<std::string> get_passes(std::string &input) {
	std::vector<std::string> passes;

	while (input.find("\n") != std::string::npos) {
		unsigned pos = static_cast<unsigned>(input.find("\n"));
		passes.push_back(input.substr(0, pos));
		input = input.substr(pos + 1);
	}

	return passes;
}

static unsigned simulate_ticket(std::string &input) {
	unsigned rows_idx = 0;
	unsigned rows_range = 128;
	unsigned clmn_idx = 0;
	unsigned clmn_range = 8;
	for (auto &instruction : input) {
		switch (instruction) {
			case 'B':
				rows_idx += static_cast<unsigned>(std::ceil(rows_range / 2));
				[[fallthrough]];
			case 'F': rows_range /= 2; break;
			case 'R':
				clmn_idx += static_cast<unsigned>(std::ceil(clmn_range / 2));
				[[fallthrough]];
			case 'L': clmn_range /= 2; break;
		}
	}

	unsigned seat_id = rows_idx * 8 + clmn_idx;

	return seat_id;
}

std::string day_5::part_a(std::string input) {
	auto passes = get_passes(input);

	unsigned highest_id = 0;

	for (auto &pass : passes) {
		auto seat_id = simulate_ticket(pass);

		if (seat_id > highest_id) {
			highest_id = seat_id;
		}
	}

	return std::to_string(highest_id);
}


std::string day_5::part_b(std::string input) {
	auto passes = get_passes(input);

	std::vector<bool> occupied(1024, false);

	for (auto &pass : passes) {
		auto seat_id = simulate_ticket(pass);

		occupied[seat_id] = true;
	}

	for (unsigned i = 1; i < occupied.size() - 1; i++) {
		if (!occupied[i] && occupied[i - 1] && occupied[i + 1]) {
			return std::to_string(i);
		}
	}

	return "No solution found";
}
