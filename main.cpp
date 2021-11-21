#include <iostream>
#include <filesystem>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
	auto l{ [](const std::string& dir, const std::string& ext) {

		std::filesystem::path path(dir);

		auto u_ptr = std::make_unique<std::vector<std::string>>();

		for (const auto& elem : std::filesystem::recursive_directory_iterator{ path }) {
			if (std::filesystem::is_regular_file(std::filesystem::status(elem.path())) && elem.path().extension().string() == ext) 
				std::back_inserter(*u_ptr) = elem.path().filename().string();
		}

		return u_ptr;
	}};
		
	std::string dir;
		
	while (true)
	{
		std::cout << "Path: ";
		
		std::cin >> dir;

		if (std::filesystem::exists(dir)) break;

		std::cout << "Path not found!\n";
	}

	std::cout << "Extension: ";
	std::string ext;
	std::cin >> ext;

	if (ext[0] != '.') ext = '.' + ext;
	
	auto u_ptr = l(dir, ext);

	std::cout << "\nList of files:\n";

	std::copy(u_ptr.get()->cbegin(), u_ptr.get()->cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
}