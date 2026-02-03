set(SOURCES
    core/gaugewidget.cpp
    core/gaugeneedle.cpp
    core/gaugescale.cpp
    core/gaugezone.cpp
    core/gaugebackground.cpp
    gauges/radialgauge.cpp
    gauges/speedometer.cpp
)

set(HEADERS
    ../include/GaugeQt/gaugeqt_global.h
    ../include/GaugeQt/GaugeQt
    ../include/GaugeQt/gaugewidget.h
    ../include/GaugeQt/gaugeneedle.h
    ../include/GaugeQt/gaugescale.h
    ../include/GaugeQt/gaugezone.h
    ../include/GaugeQt/gaugebackground.h
    ../include/GaugeQt/radialgauge.h
    ../include/GaugeQt/speedometer.h
    util/gaugemath.h
)

add_library(GaugeQt SHARED ${SOURCES} ${HEADERS})

target_compile_definitions(GaugeQt PRIVATE GAUGEQT_LIBRARY)

target_include_directories(GaugeQt
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(GaugeQt
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS GaugeQt
    EXPORT GaugeQtTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT GaugeQtTargets
    FILE GaugeQtTargets.cmake
    DESTINATION lib/cmake/GaugeQt
)
