CC  = clang

MODE =

CFLAGS += -Wall -Wextra -Werror
CFLAGS += -I$(INCLUDE_DIR)
CFLAGS += -std=c99

ifeq ($(MODE), DEBUG)
CFLAGS += -Wswitch-bool
CFLAGS += -Wswitch-default
CFLAGS += -Wswitch-enum
CFLAGS += -DDEBUG
CFLAGS += -ggdb

LDFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=leak
LDFLAGS += -lm
endif

ifeq ($(MODE), RELEASE)
CFLAGS += -O3

LDFLAGS += -lm
endif

OUTPUT_OPTION = -MMD -MF $(@:.o=.d) -o $@

INCLUDE_DIR = include

ifeq ($(MODE), RELEASE)
TARGET = target/fftc-release
endif
ifeq ($(MODE), DEBUG)
TARGET = target/fftc-debug
endif

SRC = \
			src/main.c \
			src/common.c \
			src/1-simple-dft.c \
			src/2-complex-dft.c

BUILD_DIR = build
ifeq ($(MODE), DEBUG)
BUILD_DIR = build/debug
endif
ifeq ($(MODE), RELEASE)
BUILD_DIR = build/release
endif

OBJS := $(SRC:src/%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRC:src/%.c=$(BUILD_DIR)/%.d)

.PHONY: all
all:
	$(MAKE) MODE=DEBUG build
	$(MAKE) MODE=RELEASE build

.PHONY: build
build: $(TARGET)

-include ${DEPS}

$(BUILD_DIR)/%.o: src/%.c
	@mkdir --parents $(shell dirname $@)
	$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d) -c -o $@ $<

$(TARGET): $(OBJS) | target
	$(CC) -o $@ $^ $(LDFLAGS)

target:
	mkdir --parents $@

.PHONY: .clangd
.clangd:
	@echo '$(CFLAGS)' | tr ' ' '\n' > /tmp/cflags-temp-file
	@echo '$(CXXFLAGS)' | tr ' ' '\n' > /tmp/cxxflags-temp-file

	@( \
	only_CFLAGS="$$(grep --invert-match --line-regexp --fixed-strings --file=/tmp/cxxflags-temp-file /tmp/cflags-temp-file | tr '\n' ' ')" ;\
	only_CXXFLAGS="$$(grep --invert-match --line-regexp --fixed-strings --file=/tmp/cflags-temp-file /tmp/cxxflags-temp-file | tr '\n' ' ')" ;\
	shared_CFLAGS="$$(grep --line-regexp --fixed-strings --file="/tmp/cflags-temp-file" "/tmp/cxxflags-temp-file" | tr '\n' ' ')" ;\
	echo 'Diagnostics:' ;\
	echo '  UnusedIncludes: Strict' ;\
	echo '  MissingIncludes: Strict' ;\
	\
	if [ "$$(echo "$$shared_CFLAGS" | wc --words)" -ge 1 ] ;\
	then \
	    echo 'CompileFlags:' ;\
	    echo '  Add:' ;\
	    for cflag in $$shared_CFLAGS ;\
	    do \
		printf '    - %s\n' "$$cflag" ;\
	    done \
	fi ;\
	\
	if [ "$$(echo "$$only_CFLAGS" | wc --words)" -ge 1 ] ;\
	then \
	    echo '---' ;\
	    echo 'If:' ;\
	    echo '  PathMatch: [.*\.c, .*\.h]' ;\
	    echo 'CompileFlags:' ;\
	    echo '  Add:' ;\
	    for cflag in $$only_CFLAGS ;\
	    do \
		printf '    - %s\n' "$$cflag" ;\
	    done \
	fi ;\
	\
	if [ "$$(echo "$$only_CXXFLAGS" | wc --words)" -ge 1 ] ;\
	then \
	    echo '---' ;\
	    echo 'If:' ;\
	    echo '  PathMatch: [.*\.cpp, .*\.hpp]' ;\
	    echo 'CompileFlags:' ;\
	    echo '  Add:' ;\
	    for cflag in $$only_CXXFLAGS ;\
	    do \
		printf '    - %s\n' "$$cflag" ;\
	    done \
	fi ;\
	) | tee $@
	@echo '--include-directory=$(INCLUDE_DIR)' | tee compile_flags.txt

.PHONY: clean
clean:
	rm --force --recursive $(TARGET) $(BUILD_DIR)
