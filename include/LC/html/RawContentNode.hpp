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

		string to_html(HtmlGenerationEnv& env) const override { return this->rawContent; }
	};
}