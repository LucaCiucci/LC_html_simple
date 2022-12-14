
#include <iostream>

#include <LC/html/mime_types.hpp>

#include <LC/html/serialization/tags.hpp>

#include <fstream>

int main(const int argc, const char* argv[]) {

	std::cout << "Hello World!" << std::endl;

	using namespace lc::html;

	{
		openTag(std::cout, "html");

		openTag(std::cout, "head");
		openTag(std::cout, "title");

		closeTag(std::cout, "html");
	}


	return 0;
}
