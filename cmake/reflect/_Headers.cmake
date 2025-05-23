# This file will be regenerated by `mulle-match-to-cmake` via
# `mulle-sde reflect` and any edits will be lost.
#
# This file will be included by cmake/share/Headers.cmake
#
if( MULLE_TRACE_INCLUDE)
   MESSAGE( STATUS "# Include \"${CMAKE_CURRENT_LIST_FILE}\"" )
endif()

#
# contents are derived from the file locations

set( INCLUDE_DIRS
src/reflect
src/generic
src
src/hoedown
)

#
# contents selected with patternfile ??-header--private-generated-headers
#
set( PRIVATE_GENERATED_HEADERS
src/reflect/_MulleHoedown-import-private.h
src/reflect/_MulleHoedown-include-private.h
)

#
# contents selected with patternfile ??-header--private-generic-headers
#
set( PRIVATE_GENERIC_HEADERS
src/generic/import-private.h
)

#
# contents selected with patternfile ??-header--public-generated-headers
#
set( PUBLIC_GENERATED_HEADERS
src/reflect/_MulleHoedown-export.h
src/reflect/_MulleHoedown-import.h
src/reflect/_MulleHoedown-include.h
src/reflect/_MulleHoedown-provide.h
)

#
# contents selected with patternfile ??-header--public-generic-headers
#
set( PUBLIC_GENERIC_HEADERS
src/generic/import.h
)

#
# contents selected with patternfile ??-header--public-headers
#
set( PUBLIC_HEADERS
src/MulleHoedown.h
src/MulleObjCLoader+MulleHoedown.h
src/NSData+MulleHoedown.h
src/NSString+MulleHoedown.h
src/hoedown/autolink.h
src/hoedown/buffer.h
src/hoedown/document.h
src/hoedown/escape.h
src/hoedown/html.h
src/hoedown/stack.h
src/hoedown/version.h
src/reflect/_MulleHoedown-versioncheck.h
)

