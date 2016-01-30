#pragma once

#include <string>
#include <sstream>
#include <vector>

// ×Ö·û´®·Ö¸î£¬·Ö¸ô·ûÎª delimeter
static std::vector<std::string> split_string(const std::string& s, char delimeter) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delimeter)) {
		elems.push_back(item);
	}
	return elems;
}