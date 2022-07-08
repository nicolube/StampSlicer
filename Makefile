all: clean build test

build: rebuild

rebuild:
	cmake -B build .
	$(MAKE) all -C build -sj

test: build
	env CTEST_OUTPUT_ON_FAILURE=1 $(MAKE) test -C build

install:
	sudo cp build/cli/StampSlicerCliTool /usr/bin/stamp_slicer

clean:
	rm -r build