
#include <iostream>

#include <LC/html/html.hpp>
#include <LC/html/mime_types.hpp>
#include <LC/html/attributes.hpp>
#include <LC/html/TextNode.hpp>
#include <LC/html/HtmlElement.hpp>

#include <fstream>

int main(const int argc, const char* argv[]) {

	std::cout << "Hello World!" << std::endl;

	using namespace lc::html;

	auto div = HtmlDivElement::create();
	div->attributes["class"] = "test";
	div->attributes["id"] = "test";
	div->attributes["style"] = "color: red;";
	div->children.push_back(HtmlHeadingElement::create(1));
	div->children.push_back(HtmlSpanElement::create());
	div->children.push_back(HtmlSpanElement::create());
	div->children.push_back(HtmlSpanElement::create());
	div->children.push_back(HtmlSpanElement::create());

	auto span = HtmlSpanElement::create();
	span->children.push_back(HtmlSpanElement::create());
	div->children.push_back(span);
	span = HtmlSpanElement::create();
	span->attributes["class"] = "test";
	span->children.push_back(TextNode::create("Hello World!"));
	div->children.push_back(span);

	auto div2 = HtmlDivElement::create();
	div2->attributes["class"] = "test";
	div2->attributes["id"] = "test";
	div2->attributes["style"] = "color: red;";
	div2->children.push_back(HtmlSpanElement::create());
	div2->children.push_back(HtmlSpanElement::create());
	div2->children.push_back(HtmlSpanElement::create());
	div2->children.push_back(span);

	div->children.push_back(div2);
	div->children.push_back(HtmlSpanElement::create());
	div->children.push_back(HtmlSpanElement::create());
	div->children.push_back(TextNode::create(R"qwfe(Lorem ipsum dolordae sunt?
Lorem ipsum dolor sit amet consectetur adipisicing elit. Magni temporlendus, dolores?
Lorem ipsum dolor sit amet consectetur, adipisicing elit. Recusandae,amet?)qwfe"));
	
	std::cout << div->to_html(HtmlGenerationOptions{.colored=true, .formatted=true}) << std::endl;

	std::ofstream file("test.html");
	file << div->to_html(HtmlGenerationOptions{.colored=false, .formatted=false});

	std::cout << to_html(div->children, {.colored=true, .formatted=true}) << std::endl;


	return 0;
}
