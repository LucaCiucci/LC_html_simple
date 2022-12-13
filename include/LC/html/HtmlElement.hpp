#pragma once

#include <concepts>

#include <LC/html/Element.hpp>
#include <LC/html/attributes.hpp>

namespace lc::html
{
	class HtmlElement : public Element
	{
	public:

		HtmlElement(const string& tag) : m_tag(tag) {}
		HtmlElement(HtmlElement&&) = default;
		HtmlElement(const HtmlElement&) = default;

		AttributesMap attributes;

		string tag() const { return m_tag; }

		shared_ptr<Node> clone() const override { return make_shared<HtmlElement>(*this); }

		using Element::to_html;
		void to_html(string& buff, HtmlGenerationEnv& env) const override final;

		bool breaksLineBefore() const override { return this->blockFormatted; }
		bool breaksLineAfter() const override { return this->blockFormatted; }

		void innerHtml(string& buff, HtmlGenerationEnv& env) const;
		string innerHtml(HtmlGenerationEnv& env) const;
		void outerHtml(string& buff, HtmlGenerationEnv& env) const;
		string outerHtml(HtmlGenerationEnv& env) const;

		bool formattable = true;
		bool compactable = false;
		bool finalSlash = true;
		bool blockFormatted = false;

	private:
		const string m_tag;
	};

	class HtmlSpanElement : public HtmlElement
	{
	public:
		HtmlSpanElement() : HtmlElement("span") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = false;
		}
		HtmlSpanElement(HtmlSpanElement&&) = default;
		HtmlSpanElement(const HtmlSpanElement&) = default;

		static shared_ptr<HtmlSpanElement> create() { return make_shared<HtmlSpanElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlSpanElement>(*this); }
	};

	class HtmlDivElement : public HtmlElement
	{
	public:
		HtmlDivElement() : HtmlElement("div") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlDivElement(HtmlDivElement&&) = default;
		HtmlDivElement(const HtmlDivElement&) = default;

		static shared_ptr<HtmlDivElement> create() { return make_shared<HtmlDivElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlDivElement>(*this); }
	};

	class HtmlPreElement : public HtmlElement
	{
	public:
		HtmlPreElement() : HtmlElement("pre") {
			this->formattable = false;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlPreElement(HtmlPreElement&&) = default;
		HtmlPreElement(const HtmlPreElement&) = default;

		static shared_ptr<HtmlPreElement> create() { return make_shared<HtmlPreElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlPreElement>(*this); }
	};

	class HtmlParagraphElement : public HtmlElement
	{
	public:
		HtmlParagraphElement() : HtmlElement("p") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlParagraphElement(HtmlParagraphElement&&) = default;
		HtmlParagraphElement(const HtmlParagraphElement&) = default;

		static shared_ptr<HtmlParagraphElement> create() { return make_shared<HtmlParagraphElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlParagraphElement>(*this); }
	};

	class HtmlHeadingElement : public HtmlElement
	{
	public:
		HtmlHeadingElement(int level) : HtmlElement("h" + std::to_string(level)) {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = false;
		}
		HtmlHeadingElement(HtmlHeadingElement&&) = default;
		HtmlHeadingElement(const HtmlHeadingElement&) = default;

		static shared_ptr<HtmlHeadingElement> create(int level) { return make_shared<HtmlHeadingElement>(level); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlHeadingElement>(*this); }

		bool breaksLineBefore() const override { return true; }
		bool breaksLineAfter() const override { return true; }
	};

	class HtmlTableElement : public HtmlElement
	{
	public:
		HtmlTableElement() : HtmlElement("table") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlTableElement(HtmlTableElement&&) = default;
		HtmlTableElement(const HtmlTableElement&) = default;

		static shared_ptr<HtmlTableElement> create() { return make_shared<HtmlTableElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlTableElement>(*this); }
	};

	class HtmlTableHeadElement : public HtmlElement
	{
	public:
		HtmlTableHeadElement() : HtmlElement("thead") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlTableHeadElement(HtmlTableHeadElement&&) = default;
		HtmlTableHeadElement(const HtmlTableHeadElement&) = default;

		static shared_ptr<HtmlTableHeadElement> create() { return make_shared<HtmlTableHeadElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlTableHeadElement>(*this); }
	};

	class HtmlTableBodyElement : public HtmlElement
	{
	public:
		HtmlTableBodyElement() : HtmlElement("tbody") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlTableBodyElement(HtmlTableBodyElement&&) = default;
		HtmlTableBodyElement(const HtmlTableBodyElement&) = default;

		static shared_ptr<HtmlTableBodyElement> create() { return make_shared<HtmlTableBodyElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlTableBodyElement>(*this); }
	};

	class HtmlTableRowElement : public HtmlElement
	{
	public:
		HtmlTableRowElement() : HtmlElement("tr") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlTableRowElement(HtmlTableRowElement&&) = default;
		HtmlTableRowElement(const HtmlTableRowElement&) = default;

		static shared_ptr<HtmlTableRowElement> create() { return make_shared<HtmlTableRowElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlTableRowElement>(*this); }
	};

	class HtmlTableHeaderElement : public HtmlElement
	{
	public:
		HtmlTableHeaderElement() : HtmlElement("th") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlTableHeaderElement(HtmlTableHeaderElement&&) = default;
		HtmlTableHeaderElement(const HtmlTableHeaderElement&) = default;

		static shared_ptr<HtmlTableHeaderElement> create() { return make_shared<HtmlTableHeaderElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlTableHeaderElement>(*this); }
	};

	class HtmlTableDataElement : public HtmlElement
	{
	public:
		HtmlTableDataElement() : HtmlElement("td") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlTableDataElement(HtmlTableDataElement&&) = default;
		HtmlTableDataElement(const HtmlTableDataElement&) = default;

		static shared_ptr<HtmlTableDataElement> create() { return make_shared<HtmlTableDataElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlTableDataElement>(*this); }
	};

	class HtmlListElement : public HtmlElement
	{
	public:
		HtmlListElement(bool ordered) : HtmlElement(ordered ? "ol" : "ul") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlListElement(HtmlListElement&&) = default;
		HtmlListElement(const HtmlListElement&) = default;

		static shared_ptr<HtmlListElement> create(bool ordered) { return make_shared<HtmlListElement>(ordered); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlListElement>(*this); }
	};

	class HtmlListItemElement : public HtmlElement
	{
	public:
		HtmlListItemElement() : HtmlElement("li") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlListItemElement(HtmlListItemElement&&) = default;
		HtmlListItemElement(const HtmlListItemElement&) = default;

		static shared_ptr<HtmlListItemElement> create() { return make_shared<HtmlListItemElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlListItemElement>(*this); }
	};

	class HtmlPreformattedElement : public HtmlElement
	{
	public:
		HtmlPreformattedElement() : HtmlElement("pre") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlPreformattedElement(HtmlPreformattedElement&&) = default;
		HtmlPreformattedElement(const HtmlPreformattedElement&) = default;

		static shared_ptr<HtmlPreformattedElement> create() { return make_shared<HtmlPreformattedElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlPreformattedElement>(*this); }
	};

	class HtmlCodeElement : public HtmlElement
	{
	public:
		HtmlCodeElement() : HtmlElement("code") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = false;
		}
		HtmlCodeElement(HtmlCodeElement&&) = default;
		HtmlCodeElement(const HtmlCodeElement&) = default;

		static shared_ptr<HtmlCodeElement> create() { return make_shared<HtmlCodeElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlCodeElement>(*this); }
	};

	class HtmlQuoteElement : public HtmlElement
	{
	public:
		HtmlQuoteElement() : HtmlElement("q") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlQuoteElement(HtmlQuoteElement&&) = default;
		HtmlQuoteElement(const HtmlQuoteElement&) = default;

		static shared_ptr<HtmlQuoteElement> create() { return make_shared<HtmlQuoteElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlQuoteElement>(*this); }
	};

	class HtmlBlockQuoteElement : public HtmlElement
	{
	public:
		HtmlBlockQuoteElement() : HtmlElement("blockquote") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlBlockQuoteElement(HtmlBlockQuoteElement&&) = default;
		HtmlBlockQuoteElement(const HtmlBlockQuoteElement&) = default;

		static shared_ptr<HtmlBlockQuoteElement> create() { return make_shared<HtmlBlockQuoteElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlBlockQuoteElement>(*this); }
	};

	class HtmlAddressElement : public HtmlElement
	{
	public:
		HtmlAddressElement() : HtmlElement("address") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = true;
		}
		HtmlAddressElement(HtmlAddressElement&&) = default;
		HtmlAddressElement(const HtmlAddressElement&) = default;

		static shared_ptr<HtmlAddressElement> create() { return make_shared<HtmlAddressElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlAddressElement>(*this); }
	};

	class HtmlBrElement : public HtmlElement
	{
	public:
		HtmlBrElement() : HtmlElement("br") {
			this->formattable = false;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = false;
		}
		HtmlBrElement(HtmlBrElement&&) = default;
		HtmlBrElement(const HtmlBrElement&) = default;

		static shared_ptr<HtmlBrElement> create() { return make_shared<HtmlBrElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlBrElement>(*this); }

		bool breaksLineBefore() const override { return false; }
		bool breaksLineAfter() const override { return true; }
	};

	class HtmlHrElement : public HtmlElement
	{
	public:
		HtmlHrElement() : HtmlElement("hr") {
			this->formattable = false;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = false;
		}
		HtmlHrElement(HtmlHrElement&&) = default;
		HtmlHrElement(const HtmlHrElement&) = default;

		static shared_ptr<HtmlHrElement> create() { return make_shared<HtmlHrElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlHrElement>(*this); }

		bool breaksLineBefore() const override { return true; }
		bool breaksLineAfter() const override { return true; }
	};

	class HtmlAElement : public HtmlElement
	{
	public:
		HtmlAElement() : HtmlElement("a") {
			this->formattable = true;
			this->compactable = false;
			this->finalSlash = true;
			this->blockFormatted = false;
		}
		HtmlAElement(HtmlAElement&&) = default;
		HtmlAElement(const HtmlAElement&) = default;

		static shared_ptr<HtmlAElement> create() { return make_shared<HtmlAElement>(); }

		shared_ptr<Node> clone() const override { return make_shared<HtmlAElement>(*this); }
	};

	template <std::derived_from<Node> _Node>
	string to_html(const vector<shared_ptr<_Node>>& elements, const HtmlGenerationOptions& options = {})
	{
		HtmlDivElement div;
		for (auto& element : elements)
			div.children.push_back(element);
		HtmlGenerationEnv env(options);
		env.indentLevel = -1;
		return div.innerHtml(env);
	}
}