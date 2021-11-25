CHECK_FLAGS := --local
RUN_CHECK := pipenv run check50
RUN_STYLE := pipenv run style50
PROBLEMS := cs50/problems/2021/x
LABS := cs50/labs/2021/x
RUN_LAB := $(RUN_CHECK) $(CHECK_FLAGS) $(LABS)
RUN_PROBLEM := $(RUN_CHECK) $(CHECK_FLAGS) $(PROBLEMS)

.PHONY = deps test lint all

all: lint test

test:
	cd $(CURDIR)/lab1/population && $(RUN_LAB)/population
	cd $(CURDIR)/lab2/scrabble && $(RUN_LAB)/scrabble
	cd $(CURDIR)/lab5 && $(RUN_LAB)/inheritance
	cd $(CURDIR)/lab3 && $(RUN_LAB)/sort
	cd $(CURDIR)/lab4 && $(RUN_LAB)/volume
	cd $(CURDIR)/lab5 && $(RUN_LAB)/inheritance
	cd $(CURDIR)/lab6 && $(RUN_LAB)/worldcup
	cd $(CURDIR)/lab7 && $(RUN_LAB)/songs

	cd $(CURDIR)/pset1/hello && $(RUN_PROBLEM)/hello
	cd $(CURDIR)/pset1/mario && $(RUN_PROBLEM)/mario/more
	cd $(CURDIR)/pset1/credit && $(RUN_PROBLEM)/credit
	cd $(CURDIR)/pset2/readability && $(RUN_PROBLEM)/readability
	cd $(CURDIR)/pset2/substitution && $(RUN_PROBLEM)/substitution
	cd $(CURDIR)/pset3/plurality && $(RUN_PROBLEM)/plurality
	cd $(CURDIR)/pset3/tideman && $(RUN_PROBLEM)/tideman
	cd $(CURDIR)/pset4/filter && $(RUN_PROBLEM)/filter/more
	cd $(CURDIR)/pset4/recover && $(RUN_PROBLEM)/recover
	cd $(CURDIR)/pset5/speller && $(RUN_PROBLEM)/speller
	cd $(CURDIR)/pset6/hello && $(RUN_PROBLEM)/sentimental/hello
	cd $(CURDIR)/pset6/mario && $(RUN_PROBLEM)/sentimental/mario/more
	cd $(CURDIR)/pset6/credit && $(RUN_PROBLEM)/sentimental/credit
	cd $(CURDIR)/pset6/readability && $(RUN_PROBLEM)/sentimental/readability
	cd $(CURDIR)/pset6/dna && $(RUN_PROBLEM)/dna
	cd $(CURDIR)/pset7/movies && $(RUN_PROBLEM)/movies
	cd $(CURDIR)/pset7/fiftyville && $(RUN_PROBLEM)/fiftyville
	cd $(CURDIR)/pset9/finance && $(RUN_PROBLEM)/finance

lint:
	$(RUN_STYLE) lab1/population/population.c
	$(RUN_STYLE) lab2/scrabble/scrabble.c
	$(RUN_STYLE) lab4/volume.c
	$(RUN_STYLE) lab5/inheritance.c

	$(RUN_STYLE) pset1/hello/hello.c
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
	$(RUN_STYLE) pset9/finance/*.py

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
