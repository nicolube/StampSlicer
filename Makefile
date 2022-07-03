build:
	mkdir -p build
	(cd build && cmake .. && cmake  --build .)

test: build
	(cd build && env CTEST_OUTPUT_ON_FAILURE=1 make test)

clean:
	rm -r build