THIS_DIR:=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
include ../Makefile.conf

BUILD_DIR:=$(BUILD_DIR)/$(PROJECT)

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
	cmake -DPROJECT=$(PROJECT) \
	      -DCMAKE_PREFIX_PATH=$(PREFIX_DIR) \
	      -DCMAKE_ENABLE_DEBUG=$(CONFIG_ENABLE_DEBUG) \
	      -DCMAKE_ENABLE_TEST=$(CONFIG_ENABLE_TEST) \
	      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	      $(THIS_DIR)
	cmake --build $(BUILD_DIR) -- -j$(shell nproc)
	mv $(BUILD_DIR)/compile_commands.json $(THIS_DIR)

test: $(BUILD_DIR)
	$(MAKE) $(MAKECMDGOALS) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
