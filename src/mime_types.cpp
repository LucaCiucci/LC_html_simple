
#include <atomic>
#include <stdexcept>

#include <LC/html/mime_types.hpp>

namespace lc::html
{
	// local to this translation unit
	namespace
	{
		map<string, string> image_mime_types = {
			{ "jpg", "image/jpeg" },
			{ "jpeg", "image/jpeg" },
			{ "png", "image/png" },
			{ "gif", "image/gif" },
			{ "svg", "image/svg+xml" },
			{ "ico", "image/x-icon" },
			{ "bmp", "image/bmp" },
			{ "webp", "image/webp" },
			{ "tiff", "image/tiff" },
			{ "tif", "image/tiff" },
			{ "jfif", "image/jpeg" },
			{ "jpe", "image/jpeg" },
			{ "jpx", "image/jpeg" },
			{ "j2k", "image/jpeg" },
			{ "jp2", "image/jpeg" },
			{ "j2c", "image/jpeg" },
			{ "jpc", "image/jpeg" },
		};

		map<string, string> javascript_mime_types = {
			{ "js", "application/javascript" },
			{ "mjs", "application/javascript" },
			{ "ts", "application/javascript" },
			{ "tsx", "application/javascript" },
		};

		map<string, string> text_mime_types = {
			{ "html", "text/html" },
			{ "htm", "text/html" },
			{ "shtml", "text/html" },
			{ "xhtml", "text/html" },
			{ "xml", "text/xml" },
			{ "xsl", "text/xml" },
			{ "xslt", "text/xml" },
			{ "xsd", "text/xml" },
			{ "xslth", "text/xml" },
			{ "xht", "text/xml" },
			{ "xhtm", "text/xml" },
			{ "md", "text/plain" },
			{ "txt", "text/plain" },
		};

		map<string, string> css_mime_types = {
			{ "css", "text/css" },
			{ "less", "text/css" },
			{ "scss", "text/css" },
			{ "sass", "text/css" },
			{ "styl", "text/css" },
			{ "stylus", "text/css" },
		};

		map<string, string> font_mime_types = {
			{ "woff", "font/woff" },
			{ "woff2", "font/woff2" },
			{ "ttf", "font/ttf" },
			{ "otf", "font/otf" },
			{ "eot", "font/eot" },
		};

		map<string, string> other_mime_types = {};

		map<string, string> merge() {
			map<string, string> merged;

			merged.insert(image_mime_types.begin(), image_mime_types.end());
			merged.insert(javascript_mime_types.begin(), javascript_mime_types.end());
			merged.insert(text_mime_types.begin(), text_mime_types.end());
			merged.insert(css_mime_types.begin(), css_mime_types.end());
			merged.insert(font_mime_types.begin(), font_mime_types.end());
			merged.insert(other_mime_types.begin(), other_mime_types.end());

			return merged;
		};

		std::atomic<bool> to_merge = true;
		map<string, string> merged;

		void merge_if_needed() {
			if (to_merge) {
				merged = merge();
				to_merge = false;
			}
		}
	}

	namespace default_mime_types
	{
		const map<string, string>& image()
		{
			return image_mime_types;
		}

		const map<string, string>& javascript()
		{
			return javascript_mime_types;
		}

		const map<string, string>& text()
		{
			return text_mime_types;
		}

		const map<string, string>& css()
		{
			return css_mime_types;
		}

		const map<string, string>& font()
		{
			return font_mime_types;
		}

		const map<string, string>& other()
		{
			return other_mime_types;
		}

		const map<string, string>& all()
		{
			merge_if_needed();
			return merged;
		}

		optional<string> get(const string& type)
		{
			if (to_merge)
			{
				auto it = image_mime_types.find(type);
				if (it != image_mime_types.end()) return it->second;
				it = javascript_mime_types.find(type);
				if (it != javascript_mime_types.end()) return it->second;
				it = text_mime_types.find(type);
				if (it != text_mime_types.end()) return it->second;
				it = css_mime_types.find(type);
				if (it != css_mime_types.end()) return it->second;
				it = font_mime_types.find(type);
				if (it != font_mime_types.end()) return it->second;
				it = other_mime_types.find(type);
				if (it != other_mime_types.end()) return it->second;
				return nullopt;
			}

			auto it = merged.find(type);
			if (it != merged.end()) return it->second;
			return nullopt;
		}

		void set(const string& type, const string& value)
		{
			auto it = image_mime_types.find(type);
			if (it != image_mime_types.end()) { image_mime_types[type] = value; to_merge = true; return; }
			it = javascript_mime_types.find(type);
			if (it != javascript_mime_types.end()) { javascript_mime_types[type] = value; to_merge = true; return; }
			it = text_mime_types.find(type);
			if (it != text_mime_types.end()) { text_mime_types[type] = value; to_merge = true; return; }
			it = css_mime_types.find(type);
			if (it != css_mime_types.end()) { css_mime_types[type] = value; to_merge = true; return; }
			it = font_mime_types.find(type);
			if (it != font_mime_types.end()) { font_mime_types[type] = value; to_merge = true; return; }
			it = other_mime_types.find(type);
			if (it != other_mime_types.end()) { other_mime_types[type] = value; to_merge = true; return; }
			other_mime_types[type] = value;
			to_merge = true;
		}

		void set(const string& type, const string& value, const map<string, string>& map)
		{
			if (&map == &image_mime_types)
				image_mime_types[type] = value;
			else if (&map == &javascript_mime_types)
				javascript_mime_types[type] = value;
			else if (&map == &text_mime_types)
				text_mime_types[type] = value;
			else if (&map == &css_mime_types)
				css_mime_types[type] = value;
			else if (&map == &font_mime_types)
				font_mime_types[type] = value;
			else if (&map == &other_mime_types)
				other_mime_types[type] = value;
			else
				throw std::invalid_argument("Invalid map");
			to_merge = true;
		}

		void remove(const string& type)
		{
			auto it = image_mime_types.find(type);
			if (it != image_mime_types.end()) { image_mime_types.erase(it); to_merge = true; return; }
			it = javascript_mime_types.find(type);
			if (it != javascript_mime_types.end()) { javascript_mime_types.erase(it); to_merge = true; return; }
			it = text_mime_types.find(type);
			if (it != text_mime_types.end()) { text_mime_types.erase(it); to_merge = true; return; }
			it = css_mime_types.find(type);
			if (it != css_mime_types.end()) { css_mime_types.erase(it); to_merge = true; return; }
			it = font_mime_types.find(type);
			if (it != font_mime_types.end()) { font_mime_types.erase(it); to_merge = true; return; }
			it = other_mime_types.find(type);
			if (it != other_mime_types.end()) { other_mime_types.erase(it); to_merge = true; return; }
			to_merge = true;
		}
	}
}