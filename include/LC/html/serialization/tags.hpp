#pragma once

#include <ostream>

#include <LC/string_utils/common.hpp>

namespace lc::html
{
	using std::string;
	using std::string_view;
	using std::ostream;
	using namespace std::string_literals;

	template <class T>
	concept AttributesMapType = std::ranges::range<T> && (requires(T t)
	{
		{ get<0>(*t.begin()) } -> std::convertible_to<string_view>;
		{ get<1>(*t.begin()) } -> std::convertible_to<string_view>;
		{ t.empty() } -> std::same_as<bool>;
	});

	template <AttributesMapType Attrs>
	void attributes_to_html(ostream& buff, const Attrs& attrs)
	{
		if (attrs.empty())
			return;

		buff << " ";

		for (auto it = attrs.begin(); it != attrs.end(); ++it)
		{
			const auto& [key, value] = *it;

static string str; // !!! static ?!?!?!
			str = value;
			//lc::replace_all(str, "\"", "&quot;");
			lc::replace_all(str, R"(\)", R"(\\)");
			lc::replace_all(str, R"(")", R"(\")");

			buff << key;
			buff << "=\"";
			buff << str;
			buff << "\" ";

			if (std::next(it) != attrs.end())
				buff << " ";
		}
	}

	//template <AttributesMapType Attrs = std::map<string, string>>
	template <AttributesMapType Attrs = std::vector<std::pair<string, string>>>
	inline void openTag(ostream& buff, const string& name, const Attrs& attrs = {})
	{
		buff << "<";
		buff << name;
		attributes_to_html(buff, attrs);
		buff << ">";
	}

	inline void closeTag(ostream& buff, const string& name)
	{
		buff << "</";
		buff << name;
		buff << ">";
	}

	class 
}