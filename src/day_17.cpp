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

#include "day_17.hpp"

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

enum class cube : bool { inactive, active };

template <typename T>
class bvector {
public:
	std::pair<std::vector<T>, std::vector<T>> data;

	T &operator[](long long idx) {
		if (idx >= 0) {
			return data.first[static_cast<unsigned long>(idx)];
		} else {
			return data.second[static_cast<unsigned long>((-idx) - 1)];
		}
	}

	void resize(long long idx, T fill) {
		if (idx >= 0) {
			return data.first.resize(static_cast<unsigned long>(idx) + 1, fill);
		} else {
			return data.second.resize(static_cast<unsigned long>((-idx)), fill);
		}
	}

	long long size(bool negative = false) const {
		if (negative) {
			return static_cast<long long>(data.second.size());
		} else {
			return static_cast<long long>(data.first.size());
		}
	}
};

template <typename T>
class mat3 {
public:
	bvector<bvector<bvector<T>>> data;

	T &at(long long x, long long y, long long z, T fill = {}) {
		if (x >= 0) {
			if (data.size() <= x) {
				data.resize(x, {});
			}
		} else {
			if (data.size(true) <= -x) {
				data.resize(x, {});
			}
		}

		if (y >= 0) {
			if (data[x].size() <= y) {
				data[x].resize(y, {});
			}
		} else {
			if (data[x].size(true) <= -y) {
				data[x].resize(y, {});
			}
		}

		if (z >= 0) {
			if (data[x][y].size() <= z) {
				data[x][y].resize(z, fill);
			}
		} else {
			if (data[x][y].size(true) <= -z) {
				data[x][y].resize(z, fill);
			}
		}

		return data[x][y][z];
	}
};

static mat3<cube> get_pocket_dimension(std::string &input) {
	mat3<cube> output;

	std::istringstream iss;
	iss.str(input);
	std::string temp;
	unsigned y = 0;
	while (std::getline(iss, temp)) {
		for (unsigned x = 0; x < temp.size(); x++) {
			if (temp[x] == '.') {
				output.at(x, y, 0) = cube::inactive;
			} else {
				output.at(x, y, 0) = cube::active;
			}
		}
		y++;
	}

	return output;
}

static unsigned long
  count_neighbours(mat3<cube> &mat, long long x, long long y, long long z) {
	std::vector<std::pair<short, short>> directions = {
	  {-1, 1}, {0, 1},	 {1, 1},  {-1, 0}, {0, 0},
	  {1, 0},  {-1, -1}, {0, -1}, {1, -1}};

	unsigned total = 0;

	for (int i = -1; i < 2; i++) {
		for (auto &dir : directions) {
			if (mat.at(x + dir.first, y + dir.second, z + i) == cube::active) {
				total++;
			}
		}
	}

	if (mat.at(x, y, z) == cube::active) {
		total--;
	}

	return total;
}

std::string day_17::part_a(std::string input) {
	auto pocket_d = get_pocket_dimension(input);

	for (unsigned i = 0; i < 6; i++) {
		auto copy = pocket_d;

		long long max_x = pocket_d.data.size() + 7;

		for (long long x = -pocket_d.data.size(true) - 1; x < max_x; x++) {
			pocket_d.at(x, 0, 0);

			long long max_y = pocket_d.data[x].size() + 7;

			for (long long y = -pocket_d.data[x].size(true) - 1; y < max_y;
				 y++) {
				pocket_d.at(x, y, 0);

				long long max_z = pocket_d.data[x][y].size() + 7;

				for (long long z = -pocket_d.data[x][y].size(true) - 1;
					 z < max_z; z++) {
					if (pocket_d.at(x, y, z) == cube::active) {
						if (count_neighbours(pocket_d, x, y, z) == 2
							|| count_neighbours(pocket_d, x, y, z) == 3) {
							// skip
						} else {
							copy.at(x, y, z) = cube::inactive;
						}
					} else {
						if (count_neighbours(pocket_d, x, y, z) == 3) {
							copy.at(x, y, z) = cube::active;
						}
					}
				}
			}
		}

		pocket_d = copy;
	}

	unsigned total = 0;

	for (long long x = -pocket_d.data.size(true); x < pocket_d.data.size();
		 x++) {
		for (long long y = -pocket_d.data[x].size(true);
			 y < pocket_d.data[x].size(); y++) {
			for (long long z = -pocket_d.data[x][y].size(true);
				 z < pocket_d.data[x][y].size(); z++) {
				if (pocket_d.at(x, y, z) == cube::active) {
					total++;
				}
			}
		}
	}

	return std::to_string(total);
}

std::string day_17::part_b(std::string input) {
	return "";
}
