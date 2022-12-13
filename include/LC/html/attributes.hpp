
#pragma once

#include <string>
#include <map>

namespace lc::html
{
	using std::string;
	using std::map;

	class AttributeValue
	{
	public:

		string value;

		constexpr AttributeValue() = default;
		constexpr AttributeValue(const AttributeValue&) = default;
		constexpr AttributeValue(AttributeValue&&) = default;
		constexpr AttributeValue(const string& value) : value(value) {}
		constexpr AttributeValue(const char* value) : value(value) {}
		constexpr AttributeValue(const bool value) { *this = value; }
		constexpr AttributeValue(const int value) { *this = value; }
		constexpr AttributeValue(const float value) { *this = value; }
		constexpr AttributeValue(const double value) { *this = value; }

		constexpr operator const string&() const { return this->value; }
		constexpr explicit operator string() const;
		constexpr explicit operator bool() const;
		explicit operator int() const;
		explicit operator float() const;
		explicit operator double() const;

		constexpr AttributeValue& operator=(const string& value);
		constexpr AttributeValue& operator=(const char* value);
		constexpr AttributeValue& operator=(const bool value);
		constexpr AttributeValue& operator=(const int value);
		constexpr AttributeValue& operator=(const float value);
		constexpr AttributeValue& operator=(const double value);
	};

	class AttributesMap : public map<string, AttributeValue>
	{
	public:

		using map<string, AttributeValue>::map;
		using map<string, AttributeValue>::operator=;

		bool has(const string& key) const;

		void to_html(string& buff, bool colored = false) const;
		string to_html(bool colored = false) const;
	};

	string to_html(const AttributesMap& attributes, bool colored = false);
}

// ================================================================================================================================
// ================================================================================================================================
//                                                      IMPLEMENTATION
// ================================================================================================================================
// ================================================================================================================================

namespace lc::html
{
	constexpr AttributeValue::operator string() const
	{
		return this->value;
	}

	constexpr AttributeValue::operator bool() const
	{
		if (this->value.empty())
			return false;

		if (this->value == "true")
			return true;
		if (this->value == "true")
			return true;

		return true;
	}

	constexpr AttributeValue& AttributeValue::operator=(const string& value)
	{
		this->value = value;
		return *this;
	}

	constexpr AttributeValue& AttributeValue::operator=(const char* value)
	{
		this->value = value;
		return *this;
	}

	constexpr AttributeValue& AttributeValue::operator=(const bool value)
	{
		this->value = value ? "true" : "false";
		return *this;
	}

	constexpr AttributeValue& AttributeValue::operator=(const int value)
	{
		this->value = std::to_string(value);
		return *this;
	}

	constexpr AttributeValue& AttributeValue::operator=(const float value)
	{
		this->value = std::to_string(value);
		return *this;
	}

	constexpr AttributeValue& AttributeValue::operator=(const double value)
	{
		this->value = std::to_string(value);
		return *this;
	}
}