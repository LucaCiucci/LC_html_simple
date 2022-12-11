
project(LC_html_simple LANGUAGES CXX)

set(LC_HTML_SIMPLE_MAIN_PROJECT OFF)
if((CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR) AND (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME))
	set(LC_HTML_SIMPLE_MAIN_PROJECT ON)
endif()

include(FetchContent)

FetchContent_Declare(
    LC_string_utils
    GIT_REPOSITORY https://github.com/LucaCiucci/LC_string_utils
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(LC_string_utils)

FetchContent_Declare(
    LC_console_utils
    GIT_REPOSITORY https://github.com/LucaCiucci/LC_console_utils
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(LC_console_utils)

FetchContent_Declare(
    LC_base_classes
    GIT_REPOSITORY https://github.com/LucaCiucci/LC_base_classes
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(LC_base_classes)

add_library(LC_html_simple)

target_link_libraries(LC_html_simple PUBLIC LC_string_utils LC_console_utils LC_base_classes)

#target_include_directories(LC_html_simple
#    PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#        $<INSTALL_INTERFACE:include>
#)

target_include_directories(LC_html_simple PUBLIC include)
target_sources(
	LC_html_simple
	PRIVATE
		src/tmp.cpp
		src/mime_types.cpp
		src/attributes.cpp
		src/Node.cpp
		src/TextNode.cpp
		src/escapes.cpp
		src/RawContentNode.cpp
		src/Element.cpp
		src/HtmlElement.cpp
)

# C++20
set_target_properties(
	LC_html_simple
	PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)

if (LC_HTML_SIMPLE_MAIN_PROJECT)
	add_subdirectory(tmp)
endif()