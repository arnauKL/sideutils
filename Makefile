SUBDIRS = ashew sideutils

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)

# run make for every dir
$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
