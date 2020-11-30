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

#ifndef aoc2020_input_hpp
#define aoc2020_input_hpp

#include <cstdint>
#include <string>

class input {
public:
	bool parse(int argc, char const *argv[]);

	uint8_t day;
	bool part;
	std::string input_filename;

private:
	void show_help(const std::string &name);
};


#endif	// aoc2020_input_hpp
