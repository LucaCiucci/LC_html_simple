
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

	void AttributesMap::to_html(string& buff, bool colored) const
	{
		using namespace std::string_literals;

		for (auto it = this->begin(); it != this->end(); ++it)
		{
			const auto& [key, value] = *it;
			const string keyStr = lc::colorize(key, lc::terminal_themes::dark::attribute, colored);

			if (value.value.empty())
				buff += key;

			string str = value.value;
			//lc::replace_all(str, "\"", "&quot;");
			lc::replace_all(str, R"(\)", R"(\\)");
			lc::replace_all(str, R"(")", R"(\")");
			const string valueStr = lc::colorize("\""s + str + "\"", lc::terminal_themes::dark::string, colored);

			buff += keyStr;
			buff += '=';
			buff += valueStr;

			if (std::next(it) != this->end())
				buff += ' ';
		}
	}

	string AttributesMap::to_html(bool colored) const
	{
		string buff;
		this->to_html(buff, colored);
		return buff;
	}

	string to_html(const AttributesMap& attributes, bool colored)
	{
		return attributes.to_html();
	}
}