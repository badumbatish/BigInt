
folders=$(wildcard */)
all:
	$(foreach var,$(folders), make -C $(var) $(TARGET);)

	
