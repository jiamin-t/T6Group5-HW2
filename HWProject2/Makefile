SRCS = HWProject2.cpp csv_parser.cpp ring.cpp
TARGET = simplify

$(TARGET): $(SRCS)
	g++ -std=c++17 -Wall -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)


## this is how to use:
# Step 1 - build:   make
# Step 2 - run:     ./simplify <input_file.csv> <target_vertices>
# Example:          ./simplify test/input_blob_with_two_holes.csv 17
# Clean build:      make clean