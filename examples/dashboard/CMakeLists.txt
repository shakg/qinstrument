add_executable(dashboard main.cpp)

target_link_libraries(dashboard
    PRIVATE
        GaugeQt
        Qt${QT_VERSION_MAJOR}::Widgets
)
