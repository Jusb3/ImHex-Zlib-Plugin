cmake_minimum_required(VERSION 3.16)
include(cmake/ImHexExternalPlugin.cmake)
project(imhex_plugin)

# Pin ImHex to a specific target tag.
# This can be a git tag, branch, or commit hash.
# Setting the IMHEX_OVERRIDE_TARGET_TAG variable when configuring the project will override this.
imhex_target_tag(master)
find_package(ZLIB)

# Create a new ImHex plugin.
add_imhex_plugin(
    NAME
        zlib

    SOURCES
        source/plugin_zlib.cpp

    INCLUDES
        include
        
    LIBRARIES
        ZLIB::ZLIB
)
