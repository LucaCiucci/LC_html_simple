#pragma once

#include <string>

namespace lc::html
{
	using std::string;

	string escapeHtml(const string& text, bool colored = false);

	string unescapeHtml(const string& text, bool colored = false);
}