

#include <string>
#include <vector>
#include <map>

#include "attributes.hpp"

// In the LC libraries, we usually put everything in the lc namespace.
// Here we are using the lc::html namespace since we will be working with
// a lot of HTML related things that might have the same name as other
namespace lc::html
{
	// since we are in the lc::html namespace, we will take the liberty
	// to use some "using" statements to make our code a little bit more
	// readable.
	using std::string;
	using std::vector;
	using std::map;
}