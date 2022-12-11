#pragma once

#include <vector>

#include <LC/html/Node.hpp>

namespace lc::html
{
	using std::vector;

	class Element : public Node
	{
	public:

		vector<std::shared_ptr<Node>> children;
	};
}