include keyboards/womier/common/wireless/wireless.mk

# RGB matrix uses a keyboard-level custom driver (see sk87.c) that wraps the
# WS2812 driver: the 13 side-bar/corner LEDs are wired with a different chip
# whose byte order has red and green swapped relative to the per-key LEDs.
WS2812_DRIVER_REQUIRED := yes
