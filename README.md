# ImHex Zlib Plugib

This repository contains source code to build a plugin for ImHex. This plugin adds `zlib::decompress(u8[] bytes)` function to the [PatternLanguage](https://github.com/WerWolv/PatternLanguage). The plugin is effectively a wrapper to the [Zlib](https://github.com/madler/zlib) inflate. Zlib inflate can decompress raw deflate, zlib wrapped deflate and gzip wrapped deflate streams.

## Building

Building a plugin works similarly to building ImHex. Make sure you have all dependencies installed that are necessary to build ImHex itself. Afterwards simply use cmake in the top level of this repository to build libimhex and the plugin. Consult the ImHex README.md for a more in-depth guide on how to compile ImHex using cmake.

## Notice

Plugins can depend on the ImHex version you're using. 
To find out what commit the plugin was built for, check the commit hash next to the ImHex submodule.
