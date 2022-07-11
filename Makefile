all: clean build test

build: rebuild

build-win32:
	cmake -DWIN32=1 -B build .
	$(MAKE) all -C build -sj

rebuild:
	cmake -B build .
	$(MAKE) all -C build -sj

test: build
	env CTEST_OUTPUT_ON_FAILURE=1 $(MAKE) test -C build

install:
	sudo cp build/cli/StampSlicerCliTool /usr/bin/stamp_slicer

clean:
	rm -r build