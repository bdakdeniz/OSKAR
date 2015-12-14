#
# CMake Packaging macros for OSKAR.
#

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/readme.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OSKAR-${OSKAR_VERSION}")
set(CPACK_PACKAGE_VENDOR "University of Oxford, Oxford e-Research Centre.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/copying.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${OSKAR_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${OSKAR_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${OSKAR_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION "${OSKAR_VERSION}")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)
set(CPACK_SOURCE_IGNORE_FILES "/build/;/debug/;/dbg/;/release/")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "ZIP")

include(CPack)

add_custom_target(dist
    COMMAND ${CMAKE_MAKE_PROGRAM} package_source
    COMMENT "Packaging Source files"
    VERBATIM)
