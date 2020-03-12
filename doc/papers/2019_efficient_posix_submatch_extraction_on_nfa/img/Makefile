%.pdf : %.tex
	lualatex -shell-escape $< </dev/null > $<.build_log

all : mark_and_enum.pdf parenthesized_expressions.pdf parenthesized_expressions_2.pdf tnfa_construction.pdf tnfa_example.pdf

clean:
	rm *.log *.build_log *.aux *.pdf *.pag
