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

#include "files.hpp"

#include <fstream>
#include <iostream>

bool files::read_file(std::string &output, const std::string &filename) {
	std::ifstream f(filename);
	if (!f) {
		std::cout << "Unable to open file " << filename << std::endl;
		return false;
	}

	f.seekg(0, std::ios::end);
	output.resize(static_cast<unsigned long>(f.tellg()));
	f.seekg(0);

	if (!f.read(output.data(), static_cast<long>(output.size()))) {
		std::cout << "Unable to read from file " << filename << std::endl;
		return false;
	}

	return true;
}
