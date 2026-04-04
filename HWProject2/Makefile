SRCS = HWProject2.cpp csv_parser.cpp ring.cpp geo.cpp simplifier.cpp
TARGET = simplify

$(TARGET): $(SRCS)
	g++ -std=c++17 -Wall -o $(TARGET) $(SRCS)

# ─── Generic targets ──────────────────────────────────────────────
clean:
	rm -f $(TARGET)
	rm -f test/output_*.csv

# print to console only (rubric requirement)
run:
	./$(TARGET) test/$(INPUT) $(TARGET_V)

# write to a file
output:
	./$(TARGET) test/$(INPUT) $(TARGET_V) > test/output_$(INPUT)

# compare with expected
compare:
	diff test/output_$(INPUT) test/expected_$(INPUT:.csv=.txt)

# run + compare together
check: output compare
	@echo "$(INPUT) test passed!"

# ─── Run ALL test cases ───────────────────────────────────────────
test_all: $(TARGET)
	@echo "=== Running ALL test cases ==="
	@echo ""
	$(MAKE) test_provided
	@echo ""
	$(MAKE) test_custom
	@echo ""
	@echo "=== All tests complete ==="

# ─── Run provided test cases only ────────────────────────────────
test_provided: $(TARGET)
	@echo "=== Running provided test cases ==="
	./$(TARGET) test/input_blob_with_two_holes.csv 17
	./$(TARGET) test/input_cushion_with_hexagonal_hole.csv 13
	./$(TARGET) test/input_lake_with_two_islands.csv 17
	./$(TARGET) test/input_original_01.csv 99
	./$(TARGET) test/input_original_02.csv 99
	./$(TARGET) test/input_original_03.csv 99
	./$(TARGET) test/input_original_04.csv 99
	./$(TARGET) test/input_original_05.csv 99
	./$(TARGET) test/input_original_06.csv 99
	./$(TARGET) test/input_original_07.csv 99
	./$(TARGET) test/input_original_08.csv 99
	./$(TARGET) test/input_original_09.csv 99
	./$(TARGET) test/input_original_10.csv 99
	./$(TARGET) test/input_rectangle_with_two_holes.csv 11
	./$(TARGET) test/input_wavy_with_three_holes.csv 21
	@echo "=== Provided tests complete ==="

# ─── Run custom test cases only ───────────────────────────────────
test_custom: $(TARGET)
	@echo "=== Running custom test cases ==="
	./$(TARGET) test/custom_01_1000verts.csv 99
	./$(TARGET) test/custom_02_3000verts.csv 99
	./$(TARGET) test/custom_03_5000verts.csv 99
	./$(TARGET) test/custom_04_many_holes.csv 50
	./$(TARGET) test/custom_05_near_degeneracy.csv 10
	@echo "=== Custom tests complete ==="

# ─── Benchmark (runtime + memory) ────────────────────────────────
bench: $(TARGET)
	@echo "=== Benchmarking custom test cases ==="
	@echo ""
	@echo "--- custom_01: 1,000 vertices ---"
	/usr/bin/time -v ./$(TARGET) test/custom_01_1000verts.csv 99 > /dev/null
	@echo ""
	@echo "--- custom_02: 3,000 vertices ---"
	/usr/bin/time -v ./$(TARGET) test/custom_02_3000verts.csv 99 > /dev/null
	@echo ""
	@echo "--- custom_03: 5,000 vertices (~35s) ---"
	/usr/bin/time -v ./$(TARGET) test/custom_03_5000verts.csv 99 > /dev/null
	@echo ""
	@echo "--- custom_04: many holes ---"
	/usr/bin/time -v ./$(TARGET) test/custom_04_many_holes.csv 50 > /dev/null
	@echo ""
	@echo "--- custom_05: near-degeneracy ---"
	/usr/bin/time -v ./$(TARGET) test/custom_05_near_degeneracy.csv 10 > /dev/null
	@echo ""
	@echo "=== Benchmark complete ==="

# ─── Provided test shortcuts ──────────────────────────────────────
blob:
	./$(TARGET) test/input_blob_with_two_holes.csv 17
blob_save:
	./$(TARGET) test/input_blob_with_two_holes.csv 17 > test/output_blob_with_two_holes.csv
blob_check: blob_save
	diff test/output_blob_with_two_holes.csv test/output_blob_with_two_holes.txt
	@echo "blob test passed!"

cushion:
	./$(TARGET) test/input_cushion_with_hexagonal_hole.csv 13
cushion_save:
	./$(TARGET) test/input_cushion_with_hexagonal_hole.csv 13 > test/output_cushion_with_hexagonal_hole.csv
cushion_check: cushion_save
	diff test/output_cushion_with_hexagonal_hole.csv test/output_cushion_with_hexagonal_hole.txt
	@echo "cushion test passed!"

lake:
	./$(TARGET) test/input_lake_with_two_islands.csv 17
lake_save:
	./$(TARGET) test/input_lake_with_two_islands.csv 17 > test/output_lake_with_two_islands.csv
lake_check: lake_save
	diff test/output_lake_with_two_islands.csv test/output_lake_with_two_islands.txt
	@echo "lake test passed!"

rectangle:
	./$(TARGET) test/input_rectangle_with_two_holes.csv 11
rectangle_save:
	./$(TARGET) test/input_rectangle_with_two_holes.csv 11 > test/output_rectangle_with_two_holes.csv
rectangle_check: rectangle_save
	diff test/output_rectangle_with_two_holes.csv test/output_rectangle_with_two_holes.txt
	@echo "rectangle test passed!"

wavy:
	./$(TARGET) test/input_wavy_with_three_holes.csv 21
wavy_save:
	./$(TARGET) test/input_wavy_with_three_holes.csv 21 > test/output_wavy_with_three_holes.csv
wavy_check: wavy_save
	diff test/output_wavy_with_three_holes.csv test/output_wavy_with_three_holes.txt
	@echo "wavy test passed!"

original_01:
	./$(TARGET) test/input_original_01.csv 99
original_01_save:
	./$(TARGET) test/input_original_01.csv 99 > test/output_original_01.csv
original_01_check: original_01_save
	diff test/output_original_01.csv test/output_original_01.txt
	@echo "original_01 test passed!"

original_02:
	./$(TARGET) test/input_original_02.csv 99
original_02_save:
	./$(TARGET) test/input_original_02.csv 99 > test/output_original_02.csv
original_02_check: original_02_save
	diff test/output_original_02.csv test/output_original_02.txt
	@echo "original_02 test passed!"

original_03:
	./$(TARGET) test/input_original_03.csv 99
original_03_save:
	./$(TARGET) test/input_original_03.csv 99 > test/output_original_03.csv
original_03_check: original_03_save
	diff test/output_original_03.csv test/output_original_03.txt
	@echo "original_03 test passed!"

original_04:
	./$(TARGET) test/input_original_04.csv 99
original_04_save:
	./$(TARGET) test/input_original_04.csv 99 > test/output_original_04.csv
original_04_check: original_04_save
	diff test/output_original_04.csv test/output_original_04.txt
	@echo "original_04 test passed!"

original_05:
	./$(TARGET) test/input_original_05.csv 99
original_05_save:
	./$(TARGET) test/input_original_05.csv 99 > test/output_original_05.csv
original_05_check: original_05_save
	diff test/output_original_05.csv test/output_original_05.txt
	@echo "original_05 test passed!"

original_06:
	./$(TARGET) test/input_original_06.csv 99
original_06_save:
	./$(TARGET) test/input_original_06.csv 99 > test/output_original_06.csv
original_06_check: original_06_save
	diff test/output_original_06.csv test/output_original_06.txt
	@echo "original_06 test passed!"

original_07:
	./$(TARGET) test/input_original_07.csv 99
original_07_save:
	./$(TARGET) test/input_original_07.csv 99 > test/output_original_07.csv
original_07_check: original_07_save
	diff test/output_original_07.csv test/output_original_07.txt
	@echo "original_07 test passed!"

original_08:
	./$(TARGET) test/input_original_08.csv 99
original_08_save:
	./$(TARGET) test/input_original_08.csv 99 > test/output_original_08.csv
original_08_check: original_08_save
	diff test/output_original_08.csv test/output_original_08.txt
	@echo "original_08 test passed!"

original_09:
	./$(TARGET) test/input_original_09.csv 99
original_09_save:
	./$(TARGET) test/input_original_09.csv 99 > test/output_original_09.csv
original_09_check: original_09_save
	diff test/output_original_09.csv test/output_original_09.txt
	@echo "original_09 test passed!"

original_10:
	./$(TARGET) test/input_original_10.csv 99
original_10_save:
	./$(TARGET) test/input_original_10.csv 99 > test/output_original_10.csv
original_10_check: original_10_save
	diff test/output_original_10.csv test/output_original_10.txt
	@echo "original_10 test passed!"

# ─── Custom test shortcuts ────────────────────────────────────────
custom_01:
	./$(TARGET) test/custom_01_1000verts.csv 99

custom_02:
	./$(TARGET) test/custom_02_3000verts.csv 99

custom_03:
	./$(TARGET) test/custom_03_5000verts.csv 99

custom_04:
	./$(TARGET) test/custom_04_many_holes.csv 50

custom_05:
	./$(TARGET) test/custom_05_near_degeneracy.csv 10

## ─── How to use ────────────────────────────────────────────────────
## Build:
##   make                   - build
##   make clean             - remove build + outputs
##
## Run tests:
##   make test_all          - run ALL test cases (provided + custom)
##   make test_provided     - run provided test cases only
##   make test_custom       - run custom test cases only
##   make bench             - time + memory benchmark for custom tests
##
## Generic (any file):
##   make run      INPUT=input_blob_with_two_holes.csv TARGET_V=17
##   make output   INPUT=input_blob_with_two_holes.csv TARGET_V=17
##   make compare  INPUT=input_blob_with_two_holes.csv
##   make check    INPUT=input_blob_with_two_holes.csv TARGET_V=17
##
## Provided shortcuts (NAME = blob, cushion, lake, rectangle, wavy,
##                     original_01 … original_10):
##   make NAME              - print to console
##   make NAME_save         - save to csv
##   make NAME_check        - save + diff vs expected
##
## Custom shortcuts:
##   make custom_01  make custom_02  make custom_03
##   make custom_04  make custom_05
