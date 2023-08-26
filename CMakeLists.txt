cmake_minimum_required(VERSION 3.16)
include(cmake/ImHexExternalPlugin.cmake)
project(imhex_plugin)

# Pin ImHex to a specific target tag.
# This can be a git tag, branch, or commit hash.
# Setting the IMHEX_OVERRIDE_TARGET_TAG variable when configuring the project will override this.
imhex_target_tag(v1.30.1)

# Create a new ImHex plugin.
add_imhex_plugin(
    NAME
        example_cpp

    SOURCES
        source/plugin_example.cpp

    INCLUDES
        include
)