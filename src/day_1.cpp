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

#include "day_1.hpp"

#include <sstream>
#include <vector>

#include <iostream>

std::string day_1::part_a(std::string input) {
	std::vector<unsigned> expense_report;

	std::stringstream ss;
	ss << input;

	unsigned temp;
	while (ss >> temp) {
		expense_report.push_back(temp);
	}

	for (unsigned i = 0; i < expense_report.size(); i++) {
		for (unsigned j = 0; j < expense_report.size(); j++) {
			if (expense_report[i] + expense_report[j] == 2020) {
				return std::to_string(expense_report[i] * expense_report[j]);
			}
		}
	}

	return "No solution";
}


std::string day_1::part_b(std::string input) {
	std::vector<unsigned> expense_report;

	std::stringstream ss;
	ss << input;

	unsigned temp;
	while (ss >> temp) {
		expense_report.push_back(temp);
	}

	for (unsigned i = 0; i < expense_report.size(); i++) {
		for (unsigned j = 0; j < expense_report.size(); j++) {
			for (unsigned k = 0; k < expense_report.size(); k++) {
				if (expense_report[i] + expense_report[j] + expense_report[k]
					== 2020) {
					return std::to_string(expense_report[i] * expense_report[j]
										  * expense_report[k]);
				}
			}
		}
	}

	return "No solution";
}
