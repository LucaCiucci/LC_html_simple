
#include <vector>
#include <format>

#include <LC/string_utils/common.hpp>
#include <LC/console/console.hpp>

#include <LC/html/attributes.hpp>

namespace lc::html
{
	using std::vector;

	AttributeValue::operator int() const
	{
		return std::stoi(this->value);
	}

	AttributeValue::operator float() const
	{
		return std::stof(this->value);
	}

	AttributeValue::operator double() const
	{
		return std::stod(this->value);
	}

	bool AttributesMap::has(const string& key) const
	{
		return this->find(key) != this->end();
	}

	string AttributesMap::to_html(bool colored) const
	{
		using namespace std::string_literals;

		vector<string> attributes_strings;
		for (const auto& [key, value] : *this)
		{
			const string keyStr = lc::colorize(key, lc::terminal_themes::dark::attribute, colored);

			string str = value.value;
			if (str.empty())
				attributes_strings.push_back(key);

			//lc::replace_all(str, "\"", "&quot;");
			lc::replace_all(str, R"(\)", R"(\\)");
			lc::replace_all(str, R"(")", R"(\")");
			const string valueStr = lc::colorize("\""s + str + "\"", lc::terminal_themes::dark::string, colored);

			attributes_strings.push_back(std::format("{}={}", keyStr, valueStr));
		}

		return lc::join(attributes_strings, " ");
	}

	string to_html(const AttributesMap& attributes, bool colored)
	{
		return attributes.to_html();
	}
}