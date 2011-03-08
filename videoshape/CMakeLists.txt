include_directories( ${PHONON_INCLUDE_DIR} )

########### Flake Plugin library ###############

SET (videoshape_SRCS
    VideoData.cpp
    VideoCollection.cpp
    VideoShape.cpp
    VideoShapeFactory.cpp
    VideoEventAction.cpp
    Plugin.cpp
    VideoShapeConfigWidget.cpp
    FullScreenPlayer.cpp
)

kde4_add_plugin(videoshape ${videoshape_SRCS})

target_link_libraries(videoshape ${FLAKE_LIBS}
    ${KDE4_KFILE_LIBRARY}
    ${KDE4_PHONON_LIBRARY}
)
########### install files ###############

install(TARGETS videoshape DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES videoshape.desktop DESTINATION ${SERVICES_INSTALL_DIR})

