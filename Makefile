BUILD_DIR := build

.PHONY: configure build

configure:
	cmake -S . -B $(BUILD_DIR)

build: configure
	cmake --build $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --target dashboard
