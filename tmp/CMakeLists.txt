

add_executable(tmp main.cpp)
target_link_libraries(tmp LC_html_simple)

set_target_properties(
	tmp
	PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)