set(YEEP_SOURCES)
set(YEEP_SOURCES ${YEEP_SOURCES} Application.cpp PausableClock.cpp World.cpp Body.cpp Node.cpp Singleton.h Hud.cpp ImageManager.cpp)

set(YEEP_SOURCES ${YEEP_SOURCES})

add_executable(yeep main.cpp ${YEEP_SOURCES})

configure_file(res/arial.ttf ../res/arial.ttf COPYONLY)
configure_file(res/play.png ../res/play.png COPYONLY)
configure_file(res/pause.png ../res/pause.png COPYONLY)

target_link_libraries(yeep ${mainLibs})
