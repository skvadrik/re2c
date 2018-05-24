%.pdf : %.tex
	lualatex -shell-escape $< </dev/null > $<.build_log

all : trees.pdf tnfa.pdf gor1.pdf

clean:
	rm *.log *.build_log *.aux *.pdf *.pag
