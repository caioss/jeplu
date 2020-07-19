# Finds libzip.
#
# This module defines:
# LIBZIP_INCLUDE_DIR_ZIP
# LIBZIP_INCLUDE_DIR_ZIPCONF
# LIBZIP_LIBRARY
#

if (UNIX)
	find_package(PkgConfig)
	pkg_check_modules(PC_LIBZIP QUIET libzip)

	find_path(LIBZIP_INCLUDE_DIR_ZIP
		NAMES zip.h
		HINTS ${PC_LIBZIP_INCLUDE_DIRS})

	find_path(LIBZIP_INCLUDE_DIR_ZIPCONF
		NAMES zipconf.h
		HINTS ${PC_LIBZIP_INCLUDE_DIRS})

	find_library(LIBZIP_LIBRARY
		NAMES zip)

	include(FindPackageHandleStandardArgs)
	FIND_PACKAGE_HANDLE_STANDARD_ARGS(
		LIBZIP DEFAULT_MSG
		LIBZIP_LIBRARY LIBZIP_INCLUDE_DIR_ZIP LIBZIP_INCLUDE_DIR_ZIPCONF)

	set(LIBZIP_VERSION 0)

	if (LIBZIP_INCLUDE_DIR_ZIPCONF)
	  FILE(READ "${LIBZIP_INCLUDE_DIR_ZIPCONF}/zipconf.h" _LIBZIP_VERSION_CONTENTS)
	  if (_LIBZIP_VERSION_CONTENTS)
		STRING(REGEX REPLACE ".*#define LIBZIP_VERSION \"([0-9.]+)\".*" "\\1" LIBZIP_VERSION "${_LIBZIP_VERSION_CONTENTS}")
	  endif ()
	endif ()

	set(LIBZIP_VERSION ${LIBZIP_VERSION} CACHE STRING "Version number of libzip")
else ()
	if (MSVC14)
		set(LIB_COMPILER "vc140")	# Visual Studio 2015
	elseif (MSVC12)
		set(LIB_COMPILER "vc120")	# Visual Studio 2013
	elseif (MSVC11)
		set(LIB_COMPILER "vc110")	# Visual Studio 2012
	elseif (MSVC10)
		set(LIB_COMPILER "vc100")	# Visual Studio 2010
	endif()


	set(LIBZIP_INCLUDE_DIR_ZIP
	  ${EXTERNAL_LIBS_DIR}/libzip/include CACHE INTERNAL "zip include directories"
	)
	set(LIBZIP_LIBRARY_BIN
		${EXTERNAL_LIBS_DIR}/libzip/bin/${LIB_COMPILER} CACHE INTERNAL "zip binary directory"
	)

	add_library(zip SHARED IMPORTED GLOBAL)

	# Set .dll files.
	set(LIBZIP_LIB_DEBUG_PATH "${LIBZIP_LIBRARY_BIN}/zipd${CMAKE_SHARED_LIBRARY_SUFFIX}")
	set(LIBZIP_LIB_RELEASE_PATH "${LIBZIP_LIBRARY_BIN}/zip${CMAKE_SHARED_LIBRARY_SUFFIX}")
	# Set .lib files.
	set(LIBZIP_IMPLIB_DEBUG_PATH "${EXTERNAL_LIBS_DIR}/libzip/lib/${LIB_COMPILER}/zipd${CMAKE_STATIC_LIBRARY_SUFFIX}")
	set(LIBZIP_IMPLIB_RELEASE_PATH "${EXTERNAL_LIBS_DIR}/libzip/lib/${LIB_COMPILER}/zip${CMAKE_STATIC_LIBRARY_SUFFIX}")

	set_target_properties(zip PROPERTIES 
							  IMPORTED_LOCATION_DEBUG ${LIBZIP_LIB_DEBUG_PATH}
							  IMPORTED_IMPLIB_DEBUG ${LIBZIP_IMPLIB_DEBUG_PATH}
							  IMPORTED_LOCATION_RELEASE ${LIBZIP_LIB_RELEASE_PATH}
							  IMPORTED_IMPLIB_RELEASE ${LIBZIP_IMPLIB_RELEASE_PATH})

	set(LIBZIP_LIBRARY zip CACHE INTERNAL "zip library")
endif ()

