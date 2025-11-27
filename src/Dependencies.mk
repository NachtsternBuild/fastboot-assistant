# Dependencies.mk
#
# (C) Copyright 2025 AtlantisOS Project
# by @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
#
# Usage:
# make
# make prepare
# make clean
#
# Notes: 
# - This makefile is only used to add the additional repositories.
# - use: 'include Dependencies.mk' to access this in the main makefile

# configs
BUILD_DIR := build
TMP_DIR := $(BUILD_DIR)/.external

# use SSH by default, switch to HTTPS with "make GIT_HTTPS=1"
GIT_HTTPS ?= 0

ifeq ($(GIT_HTTPS),1)
  UIBASE_URL := https://github.com/AtlantisOS-Project/atlantis-UI-base.git
  DEBBUILD_URL := https://github.com/AtlantisOS-Project/base-debian-build.git
else
  UIBASE_URL := git@github.com:AtlantisOS-Project/atlantis-UI-base.git
  DEBBUILD_URL := git@github.com:AtlantisOS-Project/base-debian-build.git
endif

# atl ui base configs
UIBASE_NAME := atlantis-UI-base
UIBASE_SUBFOLDER := src

# deb build base configs
DEBBUILD_NAME := base-debian-build
DEBBUILD_SUBFOLDER := src
DEBBUILD_CONFFOLDER := $(DEBBUILD_SUBFOLDER)/config
DEBBUILD_TARGET := deb

all: prepare clean-tmp

prepare:
	@echo "[INFO] Preparing external dependencies..."
	rm -rf $(TMP_DIR)
	mkdir -p $(TMP_DIR)

	@echo "[INFO] Cloning Atlantis UI Base..."
	git clone --depth=1 $(UIBASE_URL) $(TMP_DIR)/$(UIBASE_NAME)
	@echo "[INFO] Cloning Base Debian Build..."
	git clone --depth=1 $(DEBBUILD_URL) $(TMP_DIR)/$(DEBBUILD_NAME)

	# create target dirs
	mkdir -p $(BUILD_DIR)/uibase
	mkdir -p $(DEBBUILD_TARGET)
		
	# copy code and other files
	rsync -av --update --exclude '.git/' --exclude='*.md' --exclude='test/' --exclude='po/' --exclude='custom_css_adw.c' $(TMP_DIR)/$(UIBASE_NAME)/$(UIBASE_SUBFOLDER)/* $(BUILD_DIR)/

	rsync -av --update --exclude '.git/' --exclude='*.md' --exclude='config/' $(TMP_DIR)/$(DEBBUILD_NAME)/$(DEBBUILD_SUBFOLDER)/* $(DEBBUILD_TARGET)

clean-tmp:
	rm -rf $(TMP_DIR)

.PHONY: all prepare clean-tmp


