%.pdf : %.tex
	pdflatex -shell-escape $< </dev/null > $<.log
#	bibtex $paper
#	pdflatex -shell-escape $< </dev/null > $<.log
#	pdflatex -shell-escape $< </dev/null > $<.log

all : part_1_tnfa.pdf

clean:
	rm *.log *.aux *.pdf *.pag
