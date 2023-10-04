CC=g++ 
CFLAGS=-Wall -Werror -Wextra
CLANG_FORMAT ?= clang-format
OS := $(shell uname)

.PHONY: all
all: clean install open

.PHONY: install
install: clean
	cmake -G "Unix Makefiles" -B ./build
	cmake --build ./build --target ObjectViewer --parallel 8
	mv build/ObjectViewer.app ~/Desktop

.PHONY: uninstall
uninstall:
	rm -rf ~/Desktop/ObjectViewer.app

.PHONY: open
open:
	@open -n ~/Desktop/ObjectViewer.app --args -AppCommandLineArg

.PHONY: dvi
dvi:
	@open README.html

.PHONY: test
test: clean
	$(CC) -std=c++17 $(CFLAGS) -lgtest src/Command/Command.cc \
									src/FileReader/ObjectFileReader.cc \
									src/Object/Object.cc \
									src/Transformer/Transformer.cc \
									tests/unit_tests.cc -o unit_test && ./unit_test

.PHONY: dist
dist:
	rm -rf ObjectViewer/
	mkdir ObjectViewer
	cp -r src tests third_party CMakeLists.txt Makefile README.html ObjectViewer
	tar -cvzf ObjectViewer.tar.gz ObjectViewer
	rm -rf ObjectViewer

.PHONY: format
format:
	@find src -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google

.PHONY: check
check:
	@find src -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google

.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf unit_test
	@rm -rf build/
	@rm -rf ObjectViewer
	@rm -rf CMakeLists.txt.user
	@rm -rf ObjectViewer.tar.gz
