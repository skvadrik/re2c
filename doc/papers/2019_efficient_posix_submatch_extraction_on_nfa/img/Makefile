%.pdf : %.tex
	lualatex -shell-escape $< </dev/null > $<.build_log

all : mark_and_enum.pdf parenthesized_expressions.pdf tnfa_construction.pdf

clean:
	rm *.log *.build_log *.aux *.pdf *.pag
