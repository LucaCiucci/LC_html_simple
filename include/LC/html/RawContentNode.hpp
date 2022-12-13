#pragma once

#include <LC/html/Node.hpp>

namespace lc::html
{
	class RawContentNode final : public Node
	{
	public:
		string rawContent;

		RawContentNode(const string& rawContent) : rawContent(rawContent) {}

		shared_ptr<Node> clone() const override { return make_shared<RawContentNode>(this->rawContent); }

		void to_html(string& buff, HtmlGenerationEnv& env) const override { buff += this->rawContent; }
	};
}