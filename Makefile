CHECK_FLAGS := --local
RUN_CHECK := pipenv run check50
RUN_STYLE := pipenv run style50

.PHONY = deps test lint all

all: lint test

test:
	cd lab1/hello && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/hello
	cd lab1/population && $(RUN_CHECK) $(CHECK_FLAGS) cs50/labs/2021/x/population
	cd lab2/scrabble && $(RUN_CHECK) $(CHECK_FLAGS) cs50/labs/2021/x/scrabble
	cd lab5 && $(RUN_CHECK) $(CHECK_FLAGS) cs50/labs/2021/x/inheritance
	cd lab3 && $(RUN_CHECK) $(CHECK_FLAGS) cs50/labs/2021/x/sort
	cd lab4 && $(RUN_CHECK) $(CHECK_FLAGS) cs50/labs/2021/x/volume
	cd lab5 && $(RUN_CHECK) $(CHECK_FLAGS) cs50/labs/2021/x/inheritance
	cd lab6 && $(RUN_CHECK) $(CHECK_FLAGS) cs50/labs/2021/x/worldcup

	cd pset1/mario && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/mario/more
	cd pset1/credit && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/credit
	cd pset2/readability && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/readability
	cd pset2/substitution && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/substitution
	cd pset3/plurality && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/plurality
	cd pset3/tideman && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/tideman
	cd pset4/filter && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/filter/more
	cd pset4/recover && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/recover
	cd pset5/speller && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/speller
	cd pset6/hello && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/sentimental/hello
	cd pset6/mario && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/sentimental/mario/more
	cd pset6/credit && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/sentimental/credit
	cd pset6/readability && $(RUN_CHECK) $(CHECK_FLAGS) cs50/problems/2021/x/sentimental/readability

lint:
	$(RUN_STYLE) lab1/hello/hello.c
	$(RUN_STYLE) lab1/population/population.c
	$(RUN_STYLE) lab2/scrabble/scrabble.c
	$(RUN_STYLE) lab4/volume.c
	$(RUN_STYLE) lab5/inheritance.c

	$(RUN_STYLE) pset1/mario/mario.c
	$(RUN_STYLE) pset1/credit/credit.c
	$(RUN_STYLE) pset2/readability/readability.c
	$(RUN_STYLE) pset2/substitution/substitution.c
	$(RUN_STYLE) pset3/plurality/plurality.c
	$(RUN_STYLE) pset3/tideman/tideman.c
	$(RUN_STYLE) pset4/filter/helpers.c
	$(RUN_STYLE) pset4/recover/recover.c
	$(RUN_STYLE) pset5/speller/dictionary.c
	$(RUN_STYLE) pset6/hello/hello.py
	$(RUN_STYLE) pset6/mario/mario.py
	$(RUN_STYLE) pset6/credit/credit.py
	$(RUN_STYLE) pset6/readability/readability.py

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

filter:
	make pset4/filter/filter

recover:
	make pset4/recover/recover

speller:
	make pset5/speller/speller

deps:
	pipenv install --dev
