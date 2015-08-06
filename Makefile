DEST_DIR ?= /usr

all:
	@true

install:
	mkdir -p $(DEST_DIR)/include
	cp -Rf include/x-nix/ $(DEST_DIR)/include/
