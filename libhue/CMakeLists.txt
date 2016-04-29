include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(libhue_SRCS
    huebridgeconnection.cpp
    hueobject.cpp
    huemodel.cpp
    discovery.cpp
    configuration.cpp
    groups.cpp
    group.cpp
    lights.cpp
    lightsfiltermodel.cpp
    light.cpp
    lightinterface.h
    scenes.cpp
    scene.cpp
    schedules.cpp
    schedule.cpp
    scenesfiltermodel.cpp
    schedulesfiltermodel.cpp
    sensor.cpp
    sensors.cpp
    sensorsfiltermodel.cpp
    rule.cpp
    rules.cpp
    rulesfiltermodel.cpp
)

set(libhue_HDRS
    huebridgeconnection.h
    hueobject.h
    huemodel.h
    discovery.h
    configuration.h
    groups.h
    group.h
    lights.h
    lightsfiltermodel.h
    light.h
    lightinterface.h
    scenes.h
    scene.h
    schedules.h
    schedule.h
    scenesfiltermodel.h
    schedulesfiltermodel.h
    sensor.h
    sensors.h
    sensorsfiltermodel.h
    rule.h
    rules.h
    rulesfiltermodel.h
)

add_library(hue SHARED ${libhue_SRCS})

if(HARMATTAN_BUILD)
    target_link_libraries(hue qjson)
else()
    qt5_use_modules(hue Gui Network)
endif()

install(FILES ${libhue_HDRS} DESTINATION /usr/include/libhue)
install(TARGETS hue DESTINATION lib)

