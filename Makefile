
BENCH_LIBS := openlibm soft-fp

$(BENCH_LIBS): %: latest
	$(MAKE) -s -C ./src/common/$* archive

RESULT = .result
$(shell > $(RESULT))

ALL = x264

all:$(BENCH_LIBS) $(ALL)
	@echo "test list [$(words $(ALL)) item(s)]:" $(ALL)

$(ALL): %: latest
	@if make -s -C ./src/$* ARCH=$(ARCH) $(MAKECMDGOALS); then \
		printf "[%14s] $(COLOR_GREEN)PASS$(COLOR_NONE)\n" $* >> $(RESULT); \
	else \
		printf "[%14s] $(COLOR_RED)***FAIL***$(COLOR_NONE)\n" $* >> $(RESULT); \
	fi

run: all
	@cat $(RESULT)
	@rm $(RESULT)


CLEAN_ALL = $(dir $(shell find . -mindepth 2 -name Makefile))
clean-all: $(CLEAN_ALL)
	 
$(CLEAN_ALL):
	-@$(MAKE) -s -C $@ clean

.PHONY: $(BENCH_LIBS) all run clean-all latest

latest:

