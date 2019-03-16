CC=g++
EXEC=exec
DIR=src

all: $(EXEC)

$(EXEC) :
	@(cd $(DIR) && $(MAKE))

clean:
	@(cd $(DIR) && $(MAKE) $@)
	
mr: clean
	@(cd $(DIR) && $(MAKE) $@)
