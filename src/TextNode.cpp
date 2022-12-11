
#include <LC/string_utils/common.hpp>

#include <LC/html/TextNode.hpp>

#include <LC/html/escapes.hpp>

namespace lc::html
{
	shared_ptr<Node> TextNode::clone() const
	{
		return make_shared<TextNode>(*this);
	}

	string TextNode::to_html(HtmlGenerationEnv& env) const
	{
		auto lines = splitString(this->textContent, "\n");
		if (env.format())
		{
			string indent = "";
			for (int i = 0; i < env.indentLevel; i++)
				indent += env.options.indent;
			if (lines.size() > 1)
				for (auto it = std::next(lines.begin()); it != lines.end(); it++)
					*it = indent + *it;
		}
		return escapeHtml(join(lines, "\n"), env.options.colored);
	}
}