macro(imhex_target_tag IMHEX_TARGET_TAG)
    include(FetchContent)

    if (IMHEX_OVERRIDE_TARGET_TAG)
        message(STATUS "Overriding ImHex target tag!")
        set(IMHEX_COMMIT_TARGET ${IMHEX_OVERRIDE_TARGET_TAG})
    endif ()

    message(STATUS "Fetching ImHex \"${IMHEX_TARGET_TAG}\"")
    FetchContent_Declare(
            ImHex
            GIT_REPOSITORY https://github.com/WerWolv/ImHex
            GIT_TAG ${IMHEX_TARGET_TAG}
    )

    FetchContent_MakeAvailable(ImHex)
    message(STATUS "ImHex cloned successfully")

    set(IMHEX_BASE_FOLDER ${imhex_SOURCE_DIR})
    set(CMAKE_MODULE_PATH "${IMHEX_BASE_FOLDER}/cmake/modules")
    include("${IMHEX_BASE_FOLDER}/cmake/build_helpers.cmake")
    addDefines()

    set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

    include(ImHexPlugin)
endmacro()