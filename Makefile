TARGET_EXEC ?= example.elf
TARGET_BIN := example.bin

PREFIX := riscv-none-elf-
AS := $(PREFIX)gcc
CC := $(PREFIX)gcc
CXX := $(PREFIX)g++
CP := $(PREFIX)objcopy
BIN := $(CP) -O binary -S

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
VENDOR_DIR ?= ./vendor
ALL_SRC_DIRS := $(SRC_DIRS) $(VENDOR_DIR)/Core $(VENDOR_DIR)/Debug $(VENDOR_DIR)/Peripheral $(VENDOR_DIR)/Startup $(VENDOR_DIR)/User

FLASH_PROG ?= minichlink

SRCS := $(shell find $(ALL_SRC_DIRS) -name *.cpp -or -name *.c -or -name *.S)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(ALL_SRC_DIRS) -type f -name \*.h | sed 's!/[^/]*$$!!' | sort -u)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(EXTRA_INC)

FLAGS ?= -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g
DEFINES ?= -DSYSCLK_FREQ_144MHz
ASFLAGS ?= $(FLAGS) -x assembler $(INC_FLAGS) $(DEFINES) -MMD -MP
CPPFLAGS ?=  $(FLAGS) $(INC_FLAGS) $(DEFINES) -std=gnu99 -MMD -MP
LDFLAGS ?= $(FLAGS) -T $(VENDOR_DIR)/Ld/Link.ld -nostartfiles -Xlinker --gc-sections -Wl,-Map,"$(BUILD_DIR)/CH32V307VCT6.map" --specs=nano.specs --specs=nosys.specs


$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	$(PREFIX)size $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(BIN) $< $@

flash: $(BUILD_DIR)/$(TARGET_BIN)
	$(FLASH_PROG) -a -w $< 0x08000000 -b

usbflash: $(BUILD_DIR)/$(TARGET_EXEC)
	wchisp flash $<

# assembly
$(BUILD_DIR)/%.S.o: %.S
	$(MKDIR_P) $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
