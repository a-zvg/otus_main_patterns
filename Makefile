THIS_DIR:=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
BUILD_DIR:=$(THIS_DIR)/_build

all: contrib
	cd $(BUILD_DIR) && \
	cmake -DCMAKE_BUILD_TYPE=Debug \
	      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	      $(THIS_DIR)
	cmake --build $(BUILD_DIR) -- -j$(shell nproc)
	cp -f $(BUILD_DIR)/compile_commands.json $(THIS_DIR)

contrib: $(BUILD_DIR)/conanbuildinfo.cmake

$(BUILD_DIR)/conanbuildinfo.cmake:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
	conan install $(THIS_DIR)

test doc: $(BUILD_DIR)
	$(MAKE) $(MAKECMDGOALS) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
