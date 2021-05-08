export CC := clang
export CFLAGS += -ggdb3 \
	-O0 \
	-std=c11 \
	-Wall \
	-Werror \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-parameter \
	-Wno-unused-variable \
	-Wshadow \
	-lcrypt \
	-lcs50 \
	-lm
export VPATH = $(wildcard **/**)
