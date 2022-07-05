all: clean build test

build: rebuild

rebuild:
	cmake -B build .
	$(MAKE) all -C build -sj

test: build
	env CTEST_OUTPUT_ON_FAILURE=1 $(MAKE) test -C build

clean:
	rm -r build