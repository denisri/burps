if( brainvisa_enabled )
  BRAINVISA_GET_FILE_LIST_FROM_PRO( libburps.pro "HEADERS" _headers "SOURCES" _sources )
  BRAINVISA_COPY_AND_INSTALL_HEADERS( _headers burps headersTarget )
  BRAINVISA_ADD_MOC_FILES( _sources ${_headers} )

  add_library( burps SHARED ${_sources} )
  add_dependencies( burps ${headersTarget} )
  set_property( TARGET burps PROPERTY VERSION ${${PROJECT_NAME}_VERSION} )
  target_link_libraries( burps ${BURPS_LIBRARIES} )

  BRAINVISA_INSTALL( TARGETS burps
                DESTINATION lib
                COMPONENT ${PROJECT_NAME} )

else()

  macro( BRAINVISA_ADD_MOC_FILES _sources )
    foreach( _current_FILE ${ARGN} )
      get_filename_component( _tmp_FILE ${_current_FILE} ABSOLUTE )
      file( READ "${_tmp_FILE}" _content )
      string( REGEX MATCH Q_OBJECT _match "${_content}" )
      if( _match )
        get_filename_component( _basename ${_tmp_FILE} NAME_WE )
        set( _moc ${CMAKE_CURRENT_BINARY_DIR}/${_basename}.moc.cpp )
        if( DESIRED_QT_VERSION EQUAL 3 )
          add_custom_command(OUTPUT ${_moc}
            COMMAND ${QT_MOC_EXECUTABLE}
            ARGS ${_tmp_FILE} -o ${_moc}
            DEPENDS ${_tmp_FILE}
          )
        else()
          QT4_GENERATE_MOC( "${_tmp_FILE}" "${_moc}" )
        endif()
        set(${_sources} ${${_sources}} "${_moc}" )
      endif()
    endforeach()
  endmacro()

  set( _sources
    gui/bwin.cc
    gui/locwin.cc
    math/table.cc
    math/logTable.cc
    math/gaussTable.cc
    math/sigmoTable.cc
    math/orTable.cc
    math/localization.cc
  )

  set( _headers
    gui/bwin.h
    gui/locwin.h
    math/documentation.h
    math/table.h
    math/logTable.h
    math/gaussTable.h
    math/sigmoTable.h
    math/orTable.h
    math/localization.h
  )

  BRAINVISA_ADD_MOC_FILES( _sources ${_headers} )

  unset( headersTarget )
  foreach( _file ${_headers} )
    set( f "${CMAKE_BINARY_DIR}/include/burps/${_file}" )
    set( _absoluteFile "${CMAKE_SOURCE_DIR}/src/libburps/${_file}" )
    set( headersTarget "${headersTarget}" "${f}" )
    add_custom_command(
      OUTPUT "${f}"
      DEPENDS "${_absoluteFile}"
      COMMAND "${CMAKE_COMMAND}" -E copy "${_absoluteFile}" "${f}" )
  endforeach()
  add_custom_target( burps_headers ALL
    DEPENDS ${headersTarget} )

  add_library( burps SHARED ${_sources} )
  add_dependencies( burps burps_headers )
  set_property( TARGET burps PROPERTY VERSION ${${PROJECT_NAME}_VERSION} )
  target_link_libraries( burps ${BURPS_LIBRARIES} )

endif()

