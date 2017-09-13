WICED_SDK_PATH      := ../WICED-SDK-3.7.0-7
WICED_SDK_BUILD_DIR := "$(WICED_SDK_PATH)/build"
WICED_SDK_MAKEFILE  := Makefile
MAKE                := "$(WICED_SDK_PATH)/make"

OS                  := FreeRTOS
APP                 := snip.stringer
STACK               := LwIP
PLATFORM            := BCM94343WWCD1
BUILD_TARGET        := $(APP)-$(OS)-$(STACK)-$(PLATFORM)

all:
	$(MAKE) -C $(WICED_SDK_PATH) -f $(WICED_SDK_MAKEFILE) $(BUILD_TARGET) 

verbose:
	$(MAKE) --debug=v -C $(WICED_SDK_PATH) -f $(WICED_SDK_MAKEFILE) $(BUILD_TARGET) 

burn:
	$(MAKE) -C $(WICED_SDK_PATH) -f $(WICED_SDK_MAKEFILE) $(BUILD_TARGET) download run 

clean:
	rm -rf $(WICED_SDK_BUILD_DIR)/$(BUILD_TARGET)
