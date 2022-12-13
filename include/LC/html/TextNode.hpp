#pragma once

#include <memory>

#include <LC/html/Node.hpp>

namespace lc::html
{
	using std::shared_ptr;
	using std::make_shared;

	class TextNode final : public Node
	{
	public:

		TextNode();
		TextNode(const TextNode&) = default;
		TextNode(TextNode&&) = default;
		TextNode(const string& content) : textContent(content) {}

		static shared_ptr<TextNode> create() { return make_shared<TextNode>(); }
		static shared_ptr<TextNode> create(const string& content) { return make_shared<TextNode>(content); }
		
		shared_ptr<Node> clone() const override;

		using Node::to_html;
		void to_html(string& buff, HtmlGenerationEnv& env) const override;

		string textContent;

	private:
	};
}