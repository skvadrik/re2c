%.pdf : %.tex
	pdflatex -shell-escape $< </dev/null > $<.log

all : 2022_borsotti_trofimovich_a_closer_look_at_tdfa.pdf

clean:
	rm *.log *.aux *.pdf *.pag pratend*.tex
