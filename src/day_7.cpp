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

#include "day_7.hpp"

#include <cstdint>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>

static std::unordered_map<std::string,
						  std::vector<std::pair<uint8_t, std::string>>>
  get_rules(std::string &input) {
	std::unordered_map<std::string,
					   std::vector<std::pair<uint8_t, std::string>>>
	  output;
	std::stringstream rules;
	rules << input;
	std::string temp;

	std::regex categoriser("(\\d+) ([a-z]+ [a-z]+) bags?");
	std::smatch mtch;

	while (std::getline(rules, temp, '\n')) {
		std::string source = temp.substr(0, temp.find(" bags contain "));
		temp = temp.substr(temp.find(" bags contain") + 14,
						   temp.size() - temp.find(" bags contain") - 15);

		auto start = temp.cbegin();
		auto end = temp.cend();

		output[source] = {};

		while (std::regex_search(start, end, mtch, categoriser)) {
			start = mtch[0].second;
			output[source].push_back({std::stoi(mtch[1]), mtch[2]});
		}
	}

	return output;
}

static bool contains_gold(
  std::unordered_map<std::string, std::vector<std::pair<uint8_t, std::string>>>
	&bags,
  std::string bag) {
	for (auto &inside_bag : bags[bag]) {
		if (inside_bag.second == "shiny gold") {
			return true;
		}
	}

	for (auto &inside_bag : bags[bag]) {
		if (contains_gold(bags, inside_bag.second)) {
			return true;
		}
	}

	return false;
}

std::string day_7::part_a(std::string input) {
	auto rules = get_rules(input);

	unsigned total = 0;

	for (auto &bag : rules) {
		if (contains_gold(rules, bag.first)) {
			total++;
		}
	}

	return std::to_string(total);
}

static unsigned count_bags(
  std::unordered_map<std::string, std::vector<std::pair<uint8_t, std::string>>>
	&bags,
  std::string bag) {
	unsigned total = 0;

	for (auto &bag_inside : bags[bag]) {
		unsigned count = bag_inside.first;
		total += count * count_bags(bags, bag_inside.second) + count;
	}

	return total;
}


std::string day_7::part_b(std::string input) {
	auto rules = get_rules(input);

	return std::to_string(count_bags(rules, "shiny gold"));
}
