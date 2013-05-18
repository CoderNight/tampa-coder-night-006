TARGET = robots-vs-lasers

CC = c++
CFLAGS = -g -Wall -I${INC_DIR}

SRC_DIR = src
OUT_DIR = build
INC_DIR = include
SOURCES = $(shell find $(SRC_DIR) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%,$(OUT_DIR)/%,$(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(SOURCES) $(TARGET)

clean:
	rm -r $(OUT_DIR) $(TARGET)
