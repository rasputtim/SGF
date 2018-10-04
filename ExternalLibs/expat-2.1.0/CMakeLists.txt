# This file is copyrighted under the BSD-license for buildsystem files of KDE
# copyright 2010, Patrick Spendrin <ps_ml@gmx.de>

#sal project(expat)

message("ADDING EXPAT CMAKE CONFIGURATION SCRIPT")

cmake_minimum_required(VERSION 2.6)
set(PACKAGE_BUGREPORT "expat-bugs@libexpat.org")
set(PACKAGE_NAME "expat")
set(PACKAGE_VERSION "2.1.0")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}")

option(BUILD_tools "build the xmlwf tool for expat library" ON)
option(BUILD_examples "build the examples for expat library" ON)
option(BUILD_tests "build the tests for expat library" ON)
option(BUILD_shared "build a shared expat library" OFF)

# configuration options
set(XML_CONTEXT_BYTES 1024 CACHE STRING "Define to specify how much context to retain around the current parse point")
option(XML_DTD "Define to make parameter entity parsing functionality available" ON)
option(XML_NS "Define to make XML Namespaces functionality available" ON)

if(XML_DTD)
    set(XML_DTD 1)
else(XML_DTD)
    set(XML_DTD 0)
endif(XML_DTD)
if(XML_NS)
    set(XML_NS 1)
else(XML_NS)
    set(XML_NS 0)
endif(XML_NS)

if(BUILD_tests)
    enable_testing()
endif(BUILD_tests)

message (STATUS "EXPAT SOURCE DIR:  ${CMAKE_SOURCE_DIR}")

include(${CMAKE_SOURCE_DIR}/cmake/ConfigureChecksExpat.cmake)
set (EXPAT_SOURCE_DIR  ${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0 )


include_directories(${CMAKE_BINARY_DIR} ${EXPAT_SOURCE_DIR}/lib)
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -wd4996)
endif(MSVC)

set(expat_SRCS
    ${EXPAT_SOURCE_DIR}/lib/xmlparse.c
    ${EXPAT_SOURCE_DIR}/lib/xmlrole.c
    ${EXPAT_SOURCE_DIR}/lib/xmltok.c 
    ${EXPAT_SOURCE_DIR}/lib/xmltok_impl.c 
    ${EXPAT_SOURCE_DIR}/lib/xmltok_ns.c
)

if(WIN32 AND BUILD_shared)
    set(expat_SRCS ${expat_SRCS} ${EXPAT_SOURCE_DIR}/lib/libexpat.def)
endif(WIN32 AND BUILD_shared)

if(BUILD_shared)
    set(_SHARED SHARED)
else(BUILD_shared)
    set(_SHARED STATIC)
endif(BUILD_shared)

#add_library(expat ${_SHARED} ${expat_SRCS})
add_library(expat STATIC ${expat_SRCS})

#sal install(TARGETS expat RUNTIME DESTINATION bin
#sal                       LIBRARY DESTINATION lib
#sal                       ARCHIVE DESTINATION lib)

#sal set(prefix ${CMAKE_INSTALL_PREFIX})
#sal set(exec_prefix "\${prefix}/bin")
#sal set(libdir "\${prefix}/lib")
#sal set(includedir "\${prefix}/include")
#sal configure_file(expat.pc.in ${CMAKE_CURRENT_BINARY_DIR}/expat.pc)

#sal install(FILES lib/expat.h lib/expat_external.h DESTINATION include)
#sal install(FILES ${CMAKE_CURRENT_BINARY_DIR}/expat.pc DESTINATION lib/pkgconfig)



if(BUILD_tools AND NOT WINCE)
    set(${EXPAT_SOURCE_DIR}/xmlwf_SRCS
        ${EXPAT_SOURCE_DIR}/xmlwf/xmlwf.c
        ${EXPAT_SOURCE_DIR}/xmlwf/xmlfile.c
        ${EXPAT_SOURCE_DIR}/xmlwf/codepage.c
        ${EXPAT_SOURCE_DIR}/xmlwf/readfilemap.c
    )

    #sal add_executable(xmlwf ${xmlwf_SRCS})
    #saltarget_link_libraries(xmlwf expat)
   #sal install(TARGETS xmlwf DESTINATION bin)
   #sal install(FILES doc/xmlwf.1 DESTINATION share/man/man1)
endif(BUILD_tools AND NOT WINCE)

if(BUILD_examples)
#sal    add_executable(elements examples/elements.c)
#sal    target_link_libraries(elements expat)
#sal
#sal    add_executable(outline examples/outline.c)
#sal    target_link_libraries(outline expat)
endif(BUILD_examples)

if(BUILD_tests)
    ## these are unittests that can be run on any platform
 #sal   add_executable(runtests tests/runtests.c tests/chardata.c tests/minicheck.c)
#sal    target_link_libraries(runtests expat)
 #sal   add_test(runtests runtests)

 #sal   add_executable(runtestspp tests/runtestspp.cpp tests/chardata.c tests/minicheck.c)
 #sal   target_link_libraries(runtestspp expat)
 #sal   add_test(runtestspp runtestspp)
endif(BUILD_tests)
