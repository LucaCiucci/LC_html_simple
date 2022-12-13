
#include <LC/string_utils/common.hpp>
#include <LC/console/console.hpp>

#include <LC/html/HtmlElement.hpp>

namespace lc::html
{
	void HtmlElement::to_html(string& buff, HtmlGenerationEnv& env) const
	{
		this->outerHtml(buff, env);
	}

	void HtmlElement::innerHtml(string& buff, HtmlGenerationEnv& env) const
	{
		using namespace std::string_literals;
		vector<string> lines;
		const bool formatted = this->formattable && env.format();
		auto indentGuard = env.pushIndent(formatted && this->blockFormatted);
		auto formatGuard = env.disableFormat(!this->formattable);
		string currLine = "";
		for (const auto& child : this->children)
		{
			if (child->breaksLineBefore())
			{
				if (!currLine.empty())
					lines.push_back(currLine);
				currLine = "";
			}
			child->to_html(currLine, env);
			if (child->breaksLineAfter())
			{
				lines.push_back(currLine);
				currLine = "";
			}
		}
		if (!currLine.empty())
			lines.push_back(currLine);
		string indent = "";
		if (formatted)
			for (int i = 0; i < env.indentLevel; i++)
				indent += env.options.indent;
		if (formatted && this->blockFormatted)
			if (!lines.empty())
				buff += indent + join(lines, "\n"s + indent);
			else
				buff += "";
		else
			buff += join(lines, "");
	}

	string HtmlElement::innerHtml(HtmlGenerationEnv& env) const
	{
		string buff;
		this->innerHtml(buff, env);
		return buff;
	}

	void HtmlElement::outerHtml(string& buff, HtmlGenerationEnv& env) const
	{
		using namespace std::string_literals;
		const bool formatted = this->formattable && env.format();
		const auto gray = [&](const string& str) { return colorize(str, TerminalColor::GRAY, env.options.colored); };
		const string tag = colorize(this->tag(), terminal_themes::dark::keyword, env.options.colored);

		const string innerHtml = this->innerHtml(env);
		string indent = "";
		if (formatted)
			for (int i = 0; i < env.indentLevel; i++)
				indent += env.options.indent;
		string attributes = this->attributes.to_html(env.options.colored);
		if (!attributes.empty())
			attributes = " " + attributes;
		if (innerHtml.empty() && this->compactable)
			buff += indent + gray("<") + tag + attributes + (this->finalSlash ? gray(" /") : ""s) + gray(">");
		else
		{
			if (formatted && this->blockFormatted)
				buff += gray("<") + tag + attributes + gray(">\n") + innerHtml + "\n" + indent + gray("</") + tag + gray(">");
			else
				buff += gray("<") + tag + attributes + gray(">") + innerHtml + gray("</") + tag + gray(">");
		}
	}

	string HtmlElement::outerHtml(HtmlGenerationEnv& env) const
	{
		string buff;
		this->outerHtml(buff, env);
		return buff;
	}
}