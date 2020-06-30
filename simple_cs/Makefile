DIRS=$(shell find . -type d)
DIRS:=$(filter-out ., $(DIRS))
.PHONY:all $(DIRS) 

all:$(DIRS)

$(DIRS):
	$(MAKE)  -C $@

clean:
	@for i in $(DIRS); \
	do \
	$(MAKE) -C $$i clean; \
	done
