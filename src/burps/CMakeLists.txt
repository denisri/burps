
add_executable( burps-bin burps.cc )
set_property( TARGET burps-bin PROPERTY OUTPUT_NAME burps )
target_link_libraries( burps-bin burps ${BURPS_LIBRARIES} )

if( brainvisa_enabled )
  BRAINVISA_INSTALL( TARGETS burps-bin
    DESTINATION bin
    COMPONENT ${PROJECT_NAME} )
endif()

