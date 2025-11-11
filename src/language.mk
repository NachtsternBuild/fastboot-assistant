# Makefile
#
# (C) Copyright 2025 AtlantisOS Project
# by @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
#
# Advanced makefile for the main makefile for the project

# default textdomain
PACKAGE = fastboot-assistant
 # default localedir for dev
LOCALEDIR = po
LINGUAS_FILE := $(shell find . -name 'LINGUAS')  # list of languages
LINGUAS := $(shell cat $(LINGUAS_FILE))

POTFILE = $(LOCALEDIR)/$(PACKAGE).pot

# targets
# extract strings from C source
SRC := $(shell find . -name '*.c' ! -name 'test.c')
# source files with test
SRC_TEST := $(shell find . -name '*.c')

.PHONY: lang pot update-po compile-po

# create pot file
pot:
	xgettext --keyword=_ --language=C --from-code=UTF-8 \
		--output=$(POTFILE) $(SRC)

# update po files
update-po: pot
	@for lang in $(LINGUAS); do \
		if [ -f $(LOCALEDIR)/$$lang.po ]; then \
			msgmerge --update --backup=off $(LOCALEDIR)/$$lang.po $(POTFILE); \
		else \
			msginit --no-translator --locale=$$lang --input=$(POTFILE) \
				--output-file=$(LOCALEDIR)/$$lang.po; \
		fi; \
	done

# compile mo files
compile-po: update-po
	@for lang in $(LINGUAS); do \
		mkdir -p $(LOCALEDIR)/$$lang/LC_MESSAGES; \
		msgfmt $(LOCALEDIR)/$$lang.po -o $(LOCALEDIR)/$$lang/LC_MESSAGES/$(PACKAGE).mo; \
	done

# full langauge build
lang: compile-po
	@echo "[i18n] Build finished for languages: $(LINGUAS)"

# create pot file
pot-test:
	xgettext --keyword=_ --language=C --from-code=UTF-8 \
		--output=$(POTFILE) $(SRC_TEST)

# update po files
update-po-test: pot-test
	@for lang in $(LINGUAS); do \
		if [ -f $(LOCALEDIR)/$$lang.po ]; then \
			msgmerge --update --backup=off $(LOCALEDIR)/$$lang.po $(POTFILE); \
		else \
			msginit --no-translator --locale=$$lang --input=$(POTFILE) \
				--output-file=$(LOCALEDIR)/$$lang.po; \
		fi; \
	done

# compile mo files
compile-po-test: update-po-test
	@for lang in $(LINGUAS); do \
		mkdir -p $(LOCALEDIR)/$$lang/LC_MESSAGES; \
		msgfmt $(LOCALEDIR)/$$lang.po -o $(LOCALEDIR)/$$lang/LC_MESSAGES/$(PACKAGE).mo; \
	done


# build test app
test-po: compile-po-test
	@echo "[i18n] Build finished for languages: $(LINGUAS) with test files"
