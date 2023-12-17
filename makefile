# ----------------------------
# Makefile Options
# ----------------------------

NAME = MINESWEP
ICON = icon.png
DESCRIPTION = "Endless-Super-Sweeper"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
