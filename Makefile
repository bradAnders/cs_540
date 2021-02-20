# https://stackoverflow.com/questions/3724772/makefile-for-unit-tests-in-c
# SUBDIRS = src tests
all:
	make -C ./src
# 	make -C ./tests

clean:
	make -C ./src clean

# test:
# 	make -C ./tests test