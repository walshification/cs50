CHECK_FLAGS := --local
RUN_CHECK := pipenv run check50
RUN_STYLE := pipenv run style50
PROBLEMS := cs50/problems/2021/x
LABS := cs50/labs/2021/x

.PHONY = deps test lint all

all: lint test

test:
	cd $(CURDIR)/lab1/hello && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/hello
	cd $(CURDIR)/lab1/population && $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)/population
	cd $(CURDIR)/lab2/scrabble && $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)/scrabble
	cd $(CURDIR)/lab5 && $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)/inheritance
	cd $(CURDIR)/lab3 && $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)/sort
	cd $(CURDIR)/lab4 && $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)/volume
	cd $(CURDIR)/lab5 && $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)/inheritance
	cd $(CURDIR)/lab6 && $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)/worldcup

	cd $(CURDIR)/pset1/mario && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/mario/more
	cd $(CURDIR)/pset1/credit && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/credit
	cd $(CURDIR)/pset2/readability && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/readability
	cd $(CURDIR)/pset2/substitution && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/substitution
	cd $(CURDIR)/pset3/plurality && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/plurality
	cd $(CURDIR)/pset3/tideman && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/tideman
	cd $(CURDIR)/pset4/filter && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/filter/more
	cd $(CURDIR)/pset4/recover && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/recover
	cd $(CURDIR)/pset5/speller && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/speller
	cd $(CURDIR)/pset6/hello && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/sentimental/hello
	cd $(CURDIR)/pset6/mario && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/sentimental/mario/more
	cd $(CURDIR)/pset6/credit && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/sentimental/credit
	cd $(CURDIR)/pset6/readability && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/sentimental/readability
	cd $(CURDIR)/pset6/dna && $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)/dna

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
	$(RUN_STYLE) pset6/dna/dna.py

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
