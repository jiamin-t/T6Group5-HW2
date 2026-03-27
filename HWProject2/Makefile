SRCS = HWProject2.cpp csv_parser.cpp ring.cpp
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

# compare with .csv
compare:
	diff test/output_$(INPUT) test/expected_$(INPUT:.csv=.txt)

# run+compare together
check: run compare
	@echo "$(INPUT) test passed!"


## How to use:
# make                                                         - build
# make print INPUT=input_blob_with_two_holes.csv TARGET_V=17  - print to console
# make run INPUT=input_blob_with_two_holes.csv TARGET_V=17    - save to csv
# make compare INPUT=input_blob_with_two_holes.csv            - compare vs expected
# make check INPUT=input_blob_with_two_holes.csv TARGET_V=17  - run + compare
# make clean                                                   - remove build + outputs


# zhe ge shi for us to test after all implementations are done
# REMOVE during submission
# ─── Shortcuts ────────────────────────────────────────────────────
blob:
	./$(TARGET) test/input_blob_with_two_holes.csv 17

blob_save:
	./$(TARGET) test/input_blob_with_two_holes.csv 17 > test/output_blob_with_two_holes.csv

blob_check: blob_save
	diff test/output_blob_with_two_holes.csv test/output_blob_with_two_holes.txt
	@echo "blob test passed!"

lake:
	./$(TARGET) test/input_original_01.csv 99

lake_save:
	./$(TARGET) test/input_original_01.csv 99 > test/output_original_01.csv

lake_check: lake_save
	diff test/output_original_01.csv test/output_original_01.txt
	@echo "lake test passed!"

## How to use:
# make                - build
# make blob           - print blob to console
# make blob_save      - save blob output to csv
# make blob_check     - save blob + compare vs expected

# make lake           - print lake to console
# make lake_save      - save lake output to csv
# make lake_check     - save lake + compare vs expected
# make clean          - remove build + output files