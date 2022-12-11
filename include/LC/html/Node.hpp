#pragma once

#include <string>
#include <memory>

#include <LC/utils/Polymorphic.hpp>
#include <LC/utils/ScopeGuard.hpp>

namespace lc::html
{
	using std::string;
	using std::shared_ptr;
	using std::make_shared;

	struct HtmlGenerationOptions
	{
		bool colored = false;
		bool formatted = true;
		string indent = "    ";
	};

	struct HtmlGenerationEnv
	{
		HtmlGenerationEnv(const HtmlGenerationOptions& options) : options(options) {}

		const HtmlGenerationOptions& options;

		int indentLevel = 0;

		bool formatDisabled = false;

		bool format() const { return !this->formatDisabled && this->options.formatted; }

		ScopeGuard pushIndent(bool indent = true) {
			if (!indent)
				return ScopeGuard([]() {});
			this->indentLevel++;
			return ScopeGuard([this]() { this->indentLevel--; });
		}

		ScopeGuard disableFormat(bool disable = true) {
			if (!disable)
				return ScopeGuard([]() {});
			bool prev = this->formatDisabled;
			this->formatDisabled = true;
			return ScopeGuard([this, prev]() { this->formatDisabled = prev; });
		}
	};

	class Node : LCPolymorphic
	{
	public:

		virtual shared_ptr<Node> clone() const = 0;

		virtual string to_html(HtmlGenerationEnv& env) const = 0;
		string to_html(const HtmlGenerationOptions& options = {}) const {
			HtmlGenerationEnv env(options);
			return this->to_html(env);
		}

		virtual bool breaksLineBefore() const { return false; }
		virtual bool breaksLineAfter() const { return false; }
	};
}