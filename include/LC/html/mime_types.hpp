
#include <string>
#include <map>
#include <optional>

namespace lc::html
{
	using std::string;
	using std::map;
	using std::optional;
	using std::nullopt;

	namespace default_mime_types
	{
		const map<string, string>&  image();
		const map<string, string>&  javascript();
		const map<string, string>&  text();
		const map<string, string>&  css();
		const map<string, string>&  font();
		const map<string, string>&  other();

		const map<string, string>&  all();

		optional<string> get(const string& type);
		void set(const string& type, const string& value);
		void set(const string& type, const string& value, const map<string, string>& map);
		void remove(const string& type);
	}
}