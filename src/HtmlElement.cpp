
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

		const auto writeAttributes = [&](string& buff) {
			if (this->attributes.empty())
				return;
			buff += " ";
			this->attributes.to_html(buff, env.options.colored);
		};

		const string innerHtml = this->innerHtml(env);
		string indent = "";
		if (formatted)
			for (int i = 0; i < env.indentLevel; i++)
				indent += env.options.indent;
		//string attributes = this->attributes.to_html(env.options.colored);
		if (innerHtml.empty() && this->compactable)
		{
			buff += indent;
			buff += gray("<");
			buff += tag;
			writeAttributes(buff);
			buff += (this->finalSlash ? gray(" /") : ""s);
			buff += gray(">");
			return;
		}
		else
		{
			if (formatted && this->blockFormatted)
			{
				buff += gray("<");
				buff += tag;
				writeAttributes(buff);
				buff += gray(">\n");
				buff += innerHtml;
				buff += "\n";
				buff += indent;
				buff += gray("</");
				buff += tag;
				buff += gray(">");
				return;
			}
			else
			{
				buff += gray("<");
				buff += tag;
				writeAttributes(buff);
				buff += gray(">");
				buff += innerHtml;
				buff += gray("</");
				buff += tag;
				buff += gray(">");
				return;
			}
		}
	}

	string HtmlElement::outerHtml(HtmlGenerationEnv& env) const
	{
		string buff;
		this->outerHtml(buff, env);
		return buff;
	}

	void HtmlElement::openingTag(string& buff, bool colored) const
	{
		using namespace std::string_literals;
		const auto gray = [&](const string& str) { return colorize(str, TerminalColor::GRAY, colored); };
		const string tag = colorize(this->tag(), terminal_themes::dark::keyword, colored);

		const auto writeAttributes = [&](string& buff) {
			if (this->attributes.empty())
				return;
			buff += " ";
			this->attributes.to_html(buff, colored);
		};

		//string attributes = this->attributes.to_html(env.options.colored);
		buff += gray("<");
		buff += tag;
		writeAttributes(buff);
		buff += (this->finalSlash ? gray(" /") : ""s);
		buff += gray(">");
	}
	
	string HtmlElement::openingTag(bool colored) const
	{
		string buff;
		this->openingTag(buff, colored);
		return buff;
	}

	void HtmlElement::closingTag(string& buff, bool colored) const
	{
		using namespace std::string_literals;
		const auto gray = [&](const string& str) { return colorize(str, TerminalColor::GRAY, colored); };
		const string tag = colorize(this->tag(), terminal_themes::dark::keyword, colored);

		buff += gray("</");
		buff += tag;
		buff += gray(">");
	}

	string HtmlElement::closingTag(bool colored) const
	{
		string buff;
		this->closingTag(buff, colored);
		return buff;
	}
}