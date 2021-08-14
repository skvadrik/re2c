%.pdf : %.tex
	lualatex -shell-escape $< </dev/null >/dev/null

PDFS := \
    tnfa_construction.pdf \
    tdfa_construction.pdf \
    tdfa_multipass.pdf \
    tdfa_optimized.pdf \
    tdfa_opttagfix.pdf \
    benchmark_dfa_aot_alt.pdf \
    benchmark_dfa_aot_cat.pdf \
    benchmark_dfa_aot_rep.pdf \
    benchmark_dfa_aot_main.pdf \
    benchmark_dfa_jit.pdf \
    benchmark_java_sparse.pdf \
    benchmark_java_dense.pdf

all : $(PDFS)

clean:
	rm *.log *.build_log *.aux *.pdf *.pag
