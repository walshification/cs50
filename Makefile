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

.PHONY = deps test lint all

all: lint test

test:
	cd lab1/hello && pipenv run check50 --local cs50/problems/2021/x/hello
	cd lab1/population && pipenv run check50 --local cs50/labs/2021/x/population
	cd lab2/scrabble && pipenv run check50 --local cs50/labs/2021/x/scrabble
	cd lab5 && pipenv run check50 --local cs50/labs/2021/x/inheritance
	cd lab3 && pipenv run check50 --local cs50/labs/2021/x/sort
	cd lab4 && pipenv run check50 --local cs50/labs/2021/x/volume
	cd lab5 && pipenv run check50 --local cs50/labs/2021/x/inheritance

	cd pset1/mario && pipenv run check50 --local cs50/problems/2021/x/mario/more
	cd pset1/credit && pipenv run check50 --local cs50/problems/2021/x/credit
	cd pset2/readability && pipenv run check50 --local cs50/problems/2021/x/readability
	cd pset2/substitution && pipenv run check50 --local cs50/problems/2021/x/substitution
	cd pset3/plurality && pipenv run check50 --local cs50/problems/2021/x/plurality
	cd pset3/tideman && pipenv run check50 --local cs50/problems/2021/x/tideman
	cd pset4/filter && pipenv run check50 --local cs50/problems/2021/x/filter/more
	cd pset4/recover && pipenv run check50 --local cs50/problems/2021/x/recover

lint:
	pipenv run style50 lab1/hello/hello.c
	pipenv run style50 lab1/population/population.c
	pipenv run style50 lab2/scrabble/scrabble.c
	pipenv run style50 lab4/volume.c
	pipenv run style50 lab5/inheritance.c

	pipenv run style50 pset1/mario/mario.c
	pipenv run style50 pset1/credit/credit.c
	pipenv run style50 pset2/readability/readability.c
	pipenv run style50 pset2/substitution/substitution.c
	pipenv run style50 pset3/plurality/plurality.c
	pipenv run style50 pset3/tideman/tideman.c
	pipenv run style50 pset4/filter/helpers.c
	pipenv run style50 pset4/recover/recover.c

hello:
	make lab1/hello/hello

population:
	make lab1/population/population

mario:
	make pset1/mario/mario

credit:
	make pset1/credit/credit

scrabble:
	make lab2/scrabble/scrabble

readability:
	make pset2/readability/readability

plurality:
	make pset3/plurality/plurality

tideman:
	make pset3/tideman/tideman

deps:
	pipenv install --dev
