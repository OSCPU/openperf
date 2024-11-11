
BENCH_LIBS := bench openlibm soft-fp

$(BENCH_LIBS): %:
	$(MAKE) -s -C ./src/common/$* archive

COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

RESULT = .result
$(shell > $(RESULT))

KEEP_LOG_FAILED ?= true
KEEP_LOG_SUCCEED ?= false
TIME := $(shell date --iso=seconds)

ifeq ($(mainargs),ref)
ALL = mcf x264 stream linpack gemm whetstone
else
ALL = cpuemu mcf x264 tcc stream linpack gemm whetstone
endif

all: $(BENCH_LIBS) $(ALL)
	@echo "OpenPerf [$(words $(ALL)) item(s)]:" $(ALL)
	@if [ -z "$(mainargs)" ]; then \
		echo "Empty mainargs, use \"ref\" by default"; \
		echo "====== Running OpenPerf [input *ref*] ======"; \
	else \
		echo "====== Running OpenPerf [input *$${mainargs}*] ======"; \
	fi

$(ALL): %: $(BENCH_LIBS)
	@{\
		  TMP=$*.tmp;\
	    $(MAKE) -C ./src/$* ARCH=$(ARCH) run 2>&1 | tee -a $$TMP;\
     if [ $${PIPESTATUS[0]} -eq 0 ]; then \
		    printf "[%14s] $(COLOR_GREEN)PASS$(COLOR_NONE) " $* >> $(RESULT); \
		    cat $$TMP | grep -E -i -e "OpenPerf time: ([0-9]*\.)?[0-9]*" >> $(RESULT); \
				if $(KEEP_LOG_SUCCEED); then \
					mkdir -p "logs/$(TIME)/"; \
					mv $$TMP "logs/$(TIME)/"; \
				else \
					rm $$TMP; \
				fi \
	    else \
			  printf "[%14s] $(COLOR_RED)***FAIL***$(COLOR_NONE)\n" $* >> $(RESULT); \
				if $(KEEP_LOG_FAILED); then \
					mkdir -p "logs/$(TIME)/"; \
					mv $$TMP "logs/$(TIME)/"; \
				else \
					rm $$TMP; \
				fi \
	    fi \
	}

run: $(BENCH_LIBS) all
	@cat $(RESULT)
	@echo "============================================="
	@awk '\
		{ \
			h = min = s = ms = us = 0;\
			if (match($$0, /([0-9]+) h/, arr)) h = arr[1]; \
    	if (match($$0, /([0-9]+) min/, arr)) min = arr[1]; \
    	if (match($$0, /([0-9]+) s/, arr)) s = arr[1]; \
    	if (match($$0, /([0-9]+)\.([0-9]*) ms/, arr)) {ms = arr[1]; us = arr[2]} \
    	total_ms += h * 3600000 + min * 60000 + s * 1000 + ms; \
		} \
		END { \
			printf "Total time: %d h %d min %d s %d.%d ms\n", \
        int(total_ms / 3600000), \
        int((total_ms % 3600000) / 60000), \
        int((total_ms % 60000) / 1000), \
        total_ms % 1000, \
				us; \
	} \
	' $(RESULT)
	@if grep -q -i -e "fail" "$(RESULT)"; then \
		echo "OpenPerf FAIL"; \
		rm $(RESULT); \
		exit 1; \
	else \
		echo "OpenPerf PASS"; \
		rm $(RESULT); \
		exit 0; \
	fi

CLEAN_ALL = $(dir $(shell find . -mindepth 2 -name Makefile))
clean-all: $(CLEAN_ALL)
	 
$(CLEAN_ALL):
	-@$(MAKE) -s -C $@ clean

.PHONY: $(BENCH_LIBS) $(CLEAN_ALL) $(ALL) all run clean-all

