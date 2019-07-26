%.pdf : %.tex
	pdflatex -shell-escape $< </dev/null > $<.log

all : 2019_borsotti_trofimovich_efficient_posix_submatch_extraction_on_nfa.pdf

clean:
	rm *.log *.aux *.pdf *.pag pratend*.tex
