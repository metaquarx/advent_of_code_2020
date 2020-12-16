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

#include "day_12.hpp"

#include <cmath>
#include <cstdint>
#include <sstream>
#include <utility>
#include <vector>

enum class instruction { north, south, east, west, left, right, forward };

class ship {
public:
	ship(long x_ = 0, long y_ = 0, int angle_ = 0)
	  : x(x_), y(y_), angle(angle_) {}
	long x;
	long y;

	int angle;
};

static std::vector<std::pair<instruction, int16_t>>
  get_instructions(std::string &input) {
	std::vector<std::pair<instruction, int16_t>> output;

	std::istringstream ss;
	ss.str(input);
	std::string temp;
	while (std::getline(ss, temp)) {
		int value = std::stoi(temp.substr(1));
		switch (temp[0]) {
			case 'N': output.push_back({instruction::north, value}); break;
			case 'S': output.push_back({instruction::south, value}); break;
			case 'E': output.push_back({instruction::east, value}); break;
			case 'W': output.push_back({instruction::west, value}); break;

			case 'R': output.push_back({instruction::right, value}); break;
			case 'L': output.push_back({instruction::left, value}); break;
			case 'F': output.push_back({instruction::forward, value}); break;
		}
	}

	return output;
}

std::string day_12::part_a(std::string input) {
	auto instructions = get_instructions(input);
	ship ferry;

	for (auto &ins : instructions) {
		switch (ins.first) {
			case instruction::north: ferry.y += ins.second; break;
			case instruction::east: ferry.x += ins.second; break;
			case instruction::south: ferry.y -= ins.second; break;
			case instruction::west: ferry.x -= ins.second; break;

			case instruction::right: ferry.angle += ins.second; break;
			case instruction::left: ferry.angle -= ins.second; break;
			case instruction::forward:
				if (ferry.angle < 0) {
					ferry.angle = ferry.angle;
				}
				ferry.angle %= 360;

				if (ferry.angle == 0) {
					ferry.y += ins.second;
				} else if (ferry.angle == 90) {
					ferry.x += ins.second;
				} else if (ferry.angle == 180) {
					ferry.y -= ins.second;
				} else if (ferry.angle == 270) {
					ferry.x -= ins.second;
				}
				break;
		}
	}

	return std::to_string(std::abs(ferry.x) + std::abs(ferry.y));
}

static ship rotate(const ship &origin, const ship &action, int angle) {
	if (angle == -90 || angle == 270) {
		ship output;

		output.x = action.x - origin.x;
		output.y = action.y - origin.y;

		long temp = output.x;
		output.x = -output.y;
		output.y = temp;

		output.x += origin.x;
		output.y += origin.y;

		return output;
	} else {
		if (angle == 0) {
			return action;
		} else if (angle == 180 || angle == -180) {
			return rotate(origin, rotate(origin, action, -90), -90);
		} else if (angle == 90 || angle == -270) {
			return rotate(origin, rotate(origin, action, 180), -90);
		}
	}

	return {};
}

std::string day_12::part_b(std::string input) {
	auto instructions = get_instructions(input);

	ship ferry;
	ship waypoint(10, 1, 0);

	for (auto &ins : instructions) {
		switch (ins.first) {
			case instruction::north: waypoint.y += ins.second; break;
			case instruction::east: waypoint.x += ins.second; break;
			case instruction::south: waypoint.y -= ins.second; break;
			case instruction::west: waypoint.x -= ins.second; break;

			case instruction::left:
				waypoint = rotate(ferry, waypoint, -ins.second);
				break;
			case instruction::right:
				waypoint = rotate(ferry, waypoint, ins.second);
				break;

			case instruction::forward:
				ship displacement;
				displacement.x = (waypoint.x - ferry.x) * ins.second;
				displacement.y = (waypoint.y - ferry.y) * ins.second;

				ferry.x += displacement.x;
				ferry.y += displacement.y;

				waypoint.x += displacement.x;
				waypoint.y += displacement.y;
				break;
		}
	}

	return std::to_string(std::abs(ferry.x) + std::abs(ferry.y));
}
