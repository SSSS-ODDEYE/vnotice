########################################################################
############################ vnotice ###################################
########################################################################
APPNAME = vnotice
CONFIGFILE = .config
ROBOT_ID = $(shell if [ -f $(CONFIGFILE) ]; then  grep -Po '(?<=ROBOT_ID=).*' $(CONFIGFILE) ;fi)

.PHONY: help
help:
	@echo "Run \`\033[35m$(MAKE)\033[0m \033[34minstall ROBOT_ID=\033[0m\033[32mYour_Robot_Id\033[0m\` to install \033[35m$(APPNAME)\033[0m"
	@echo "Contact us for assistance if necessary (\033[36mzhu.thatboy@outlook.com\033[0m | \033[36mboy_dongjie@foxmail.com\033[0m)."

.PHONY: install
install: $(APPNAME)
ifeq ($(ROBOT_ID),)
	$(warning Error: No ROBOT_ID given!)
	$(warning Use `$(MAKE) $@ ROBOT_ID=XXX-XXX-XXX-XXX` instread.)
	$(warning Contact us for assistance if necessary (zhu.thatboy@outlook.com | boy_dongjie@foxmail.com).)
	$(error Install failed.)
endif
	@echo "Config ROBOT_ID : \033[34m$(ROBOT_ID)\033[0m"
	@echo ROBOT_ID=$(ROBOT_ID) > $(CONFIGFILE)
	@sudo ln -sf `pwd`/$(APPNAME) /usr/bin/
	@echo "Run \`\033[35m$(APPNAME)\033[0m \033[34m--help\033[0m\` for help."
	@echo "\033[35m$(APPNAME)\033[0m installed at \033[34m`pwd`/$(APPNAME)\033[0m."

.PHONY: version
version: $(APPNAME)
	@./$(APPNAME) -v

.PHONY: update
update: 
	@git pull -f
	@git checkout main
	@$(MAKE) install

.PHONY: uninstall
uninstall:
ifneq ($(APPNAME),)
	@echo "Remove \033[35m$(APPNAME)\033[0m ..."
	@sudo rm -f /usr/bin/$(APPNAME)
	@echo "\033[34mDone\033[0m."
endif