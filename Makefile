
BENCH_LIBS := bench openlibm soft-fp

$(BENCH_LIBS): %: latest
	$(MAKE) -s -C ./src/common/$* archive

COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

RESULT = .result
$(shell > $(RESULT))

ALL = mcf x264 tcc stream linpack gemm whetstone

all: $(BENCH_LIBS) $(ALL)
	@echo "test list [$(words $(ALL)) item(s)]:" $(ALL)

$(ALL): %: $(BENCH_LIBS) latest
	@{\
		  TMP=$*.tmp;\
	    make -C ./src/$* ARCH=$(ARCH) run 2>&1 | tee -a $$TMP;\
      if [ $${PIPESTATUS[0]} -eq 0 ]; then \
		    printf "[%14s] $(COLOR_GREEN)PASS$(COLOR_NONE) " $* >> $(RESULT); \
		    cat $$TMP | grep -E -i -e "time: ([0-9]*\.)?[0-9]* ms" >> $(RESULT); \
		    rm $$TMP;\
	    else \
			  printf "[%14s] $(COLOR_RED)***FAIL***$(COLOR_NONE)\n" $* >> $(RESULT); \
				rm $$TMP; \
	    fi \
	}

run: $(BENCH_LIBS) all
	@cat $(RESULT)
	@cat $(RESULT) | grep -E -o "time: ([0-9]*\.[0-9]*) ms" | awk '{sum += $$2} END {print sum " ms"}'
	@rm $(RESULT)


CLEAN_ALL = $(dir $(shell find . -mindepth 2 -name Makefile))
clean-all: $(CLEAN_ALL)
	 
$(CLEAN_ALL):
	-@$(MAKE) -s -C $@ clean

.PHONY: $(BENCH_LIBS) $(CLEAN_ALL) $(ALL) all run clean-all latest

latest:

