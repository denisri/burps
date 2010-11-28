cmake_minimum_required( VERSION 2.6 )

find_package( brainvisa-cmake )
if( brainvisa-cmake_FOUND )
  set( brainvisa_enabled "1" )
  BRAINVISA_PROJECT()
else()

  set( brainvisa_enabled "" )
  set( PROJECT_NAME burps )
  set( qroll_VERSION 0.3 )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
  if ( NOT DEFINED WIN32 )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
  else()
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
  endif()
endif()

if( NOT DESIRED_QT_VERSION )
  find_package( Qt REQUIRED )
endif()
if( DESIRED_QT_VERSION EQUAL 4 )
  find_package( Qt4 COMPONENTS QtCore QtGui Qt3Support REQUIRED )
endif()
find_package( QtVersion )
find_package( Qwt REQUIRED )

set( BURPS_DEFINITIONS "-DBURPS_EXPORTS" )

set( BURPS_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include )
include_directories( "${BURPS_INCLUDE_DIR}" "${QWT_INCLUDE_DIR}" )
add_definitions( ${BURPS_DEFINITIONS} )

if( DESIRED_QT_VERSION EQUAL 3 )
  include_directories( ${QT_INCLUDE_DIR} )
  add_definitions( ${QT_DEFINITIONS} )
  set( BURPS_LIBRARIES ${QT_LIBRARIES} )
else()
  include( "${QT_USE_FILE}" )
  set( BURPS_LIBRARIES ${QT_QT3SUPPORT_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} )
endif()

set( BURPS_LIBRARIES ${BURPS_LIBRARIES} ${QWT_LIBRARY} )

add_subdirectory( src )
# add_subdirectory( doxygen )

