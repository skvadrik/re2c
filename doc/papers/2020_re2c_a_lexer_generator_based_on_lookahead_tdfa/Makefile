2020_trofimovich_re2c_a_lexer_generator_based_on_lookahead_tdfa.pdf : 2020_trofimovich_re2c_a_lexer_generator_based_on_lookahead_tdfa.tex example.pdf
	pdflatex -shell-escape $< </dev/null > $<.log

example.pdf : example.tex
	lualatex -shell-escape $< </dev/null > $<.build_log

clean:
	rm -f *.log *.pdf *.build_log *.aux *.out *.spl
