# Install script for directory: /home/donolin/projects/KolossussUtils

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/donolin/projects/KolossussUtils/cmake/source/7z/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/zlib/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/zip/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/SDL/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/configuration/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/containers/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/exceptions/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/filesystem/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/memory/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/strings/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/threads/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/utils/cmake_install.cmake")
  include("/home/donolin/projects/KolossussUtils/cmake/source/xml/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/donolin/projects/KolossussUtils/cmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
