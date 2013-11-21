# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := autoshapes vecmath

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

autoshapes: vecmath
	@echo "==== Building autoshapes ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f autoshapes.make

vecmath: 
	@echo "==== Building vecmath ($(config)) ===="
	@${MAKE} --no-print-directory -C vecmath -f Makefile

clean:
	@${MAKE} --no-print-directory -C . -f autoshapes.make clean
	@${MAKE} --no-print-directory -C vecmath -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug"
	@echo "   release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   autoshapes"
	@echo "   vecmath"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
