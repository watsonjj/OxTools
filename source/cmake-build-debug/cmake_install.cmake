# Install script for directory: /Users/Jason/Software/OxTools/source

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/create_charge_resolution")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./create_charge_resolution" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./create_charge_resolution")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./create_charge_resolution")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./create_charge_resolution")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/fit_pulse_spectrum")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./fit_pulse_spectrum" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./fit_pulse_spectrum")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./fit_pulse_spectrum")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./fit_pulse_spectrum")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/join_runs")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./join_runs" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./join_runs")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./join_runs")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./join_runs")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/plot_camera_image")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_camera_image" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_camera_image")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_camera_image")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_camera_image")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/plot_hillas")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_hillas" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_hillas")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_hillas")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_hillas")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/plot_pixel_positions")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_pixel_positions" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_pixel_positions")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_pixel_positions")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_pixel_positions")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/plot_temp_vs_ped")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_temp_vs_ped" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_temp_vs_ped")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_temp_vs_ped")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_temp_vs_ped")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/plot_timeseries")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_timeseries" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_timeseries")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_timeseries")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_timeseries")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/plot_vector_camera_image")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_vector_camera_image" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_vector_camera_image")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_vector_camera_image")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./plot_vector_camera_image")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/print_file_info")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./print_file_info" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./print_file_info")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./print_file_info")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./print_file_info")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/run_simulation")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./run_simulation" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./run_simulation")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./run_simulation")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./run_simulation")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/save_oxroot")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./save_oxroot" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./save_oxroot")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./save_oxroot")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./save_oxroot")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE EXECUTABLE FILES "/Users/Jason/Software/OxTools/source/cmake-build-debug/bin/test_fn")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./test_fn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./test_fn")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Jason/Software/root-6.06.00/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./test_fn")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./test_fn")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/Jason/Software/OxTools/source/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
