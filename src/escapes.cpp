
#include <LC/string_utils/common.hpp>
#include <LC/console/console.hpp>

#include <LC/html/escapes.hpp>

namespace lc::html
{
	string escapeHtml(const string& text, bool colored)
	{
		// TODO missing &, unicode, ....
		auto result = text;
		replace_all(result, "<", colorize("&lt;", lc::terminal_themes::dark::keyword, colored));
		replace_all(result, ">", colorize("&gt;", lc::terminal_themes::dark::keyword, colored));
		return result;
	}

	string unescapeHtml(const string& text, bool colored)
	{
		// TODO missing &, unicode, ....
		auto result = text;
		replace_all(result, "&lt;", "<");
		replace_all(result, "&gt;", ">");
		return result;
	}
}