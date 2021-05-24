THIS_DIR:=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
include ../../Makefile.conf

COMPONENT_NAME=$(shell basename $(THIS_DIR))
BUILD_DIR:=$(BUILD_DIR)/$(COMPONENT_NAME)

COMPONENT_DIR=boost_1_76_0
COMPONENT_AR=$(COMPONENT_DIR).tar.gz

all: $(COMPONENT_DIR) build

$(COMPONENT_DIR):
	tar -xf $(COMPONENT_AR) -C $(THIS_DIR)

build:
	mkdir -p $(PREFIX_DIR)/include
	cp -r $(COMPONENT_DIR)/boost $(PREFIX_DIR)/include/

clean:
	rm -rf $(BUILD_DIR)

remove:
	rm -rf $(COMPONENT_DIR)

