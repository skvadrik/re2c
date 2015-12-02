VPATH = ..

SRC_RST = \
    src/examples/examples.rst \
    src/examples/06_braille.utf8.txt.rst \
    src/examples/example_05.rst \
    src/examples/example_02.rst \
    src/examples/home.rst \
    src/examples/example_01.rst \
    src/examples/example_03.rst \
    src/examples/example_07.rst \
    src/examples/example_04.rst \
    src/examples/example_06.rst \
    src/contents.rst \
    src/home.rst \
    src/manual/syntax/syntax.rst \
    src/manual/warnings/undefined_control_flow/default_vs_any.rst \
    src/manual/warnings/undefined_control_flow/real_world.rst \
    src/manual/warnings/undefined_control_flow/how_it_works.rst \
    src/manual/warnings/undefined_control_flow/simple_example.rst \
    src/manual/warnings/undefined_control_flow/wundefined_control_flow.rst \
    src/manual/warnings/swapped_range/wswapped_range.rst \
    src/manual/warnings/condition_order/real_world.rst \
    src/manual/warnings/condition_order/how_it_works.rst \
    src/manual/warnings/condition_order/simple_example.rst \
    src/manual/warnings/condition_order/wcondition_order.rst \
    src/manual/warnings/home.rst \
    src/manual/warnings/useless_escape/real_world.rst \
    src/manual/warnings/useless_escape/how_it_works.rst \
    src/manual/warnings/useless_escape/simple_example.rst \
    src/manual/warnings/useless_escape/wuseless_escape.rst \
    src/manual/warnings/warnings.rst \
    src/manual/warnings/warnings_list.rst \
    src/manual/warnings/empty_character_class/wempty_character_class.rst \
    src/manual/warnings/unreachable_rules/real_world.rst \
    src/manual/warnings/unreachable_rules/infinite_rules.rst \
    src/manual/warnings/unreachable_rules/how_it_works.rst \
    src/manual/warnings/unreachable_rules/simple_example.rst \
    src/manual/warnings/unreachable_rules/wunreachable_rules.rst \
    src/manual/warnings/warnings_general.rst \
    src/manual/warnings/match_empty_string/real_world.rst \
    src/manual/warnings/match_empty_string/wmatch_empty_string.rst \
    src/manual/warnings/match_empty_string/simple_example.rst \
    src/manual/warnings/match_empty_string/false_alarm.rst \
    src/manual/home.rst \
    src/manual/features/generic_api/generic_api.rst \
    src/manual/features/features.rst \
    src/manual/features/conditions/conditions.rst \
    src/manual/features/state/state.rst \
    src/manual/features/skeleton/skeleton.rst \
    src/manual/features/home.rst \
    src/manual/features/dot/dot.rst \
    src/manual/features/encodings/encodings.rst \
    src/manual/features/reuse/reuse.rst \
    src/manual/manual.rst \
    src/manual/options/options.rst \
    src/manual/options/home.rst \
    src/manual/options/options_list.rst \
    src/news/news.rst \
    src/news/changelog/changelog.rst \
    src/news/changelog/0_15_list.rst \
    src/news/changelog/0_15.rst \
    src/news/changelog/0_14.rst \
    src/news/changelog/0_13.rst \
    src/news/changelog/0_12.rst \
    src/news/changelog/0_11.rst \
    src/news/changelog/0_10.rst \
    src/news/changelog/0_09.rst \
    src/news/changelog/beginning.rst \
    src/news/release_notes/0_15.rst \
    src/news/release_notes/0_15_1.rst \
    src/news/release_notes/0_15_2.rst \
    src/news/release_notes/0_15_3.rst \
    src/news/home.rst \
    src/about/about.rst \
    src/install/install.rst \
    src/index.rst

SRC_CSS = src/css/default.css

SRC_TPL = src/template.html

SRC_OTH = \
    src/CNAME \
    src/examples/06_braille.utf8.txt \
    src/examples/05_parsing_integers_conditions.re \
    src/examples/06_braille.utf32.txt \
    src/examples/06_braille.re \
    src/examples/07_cxx98.re \
    src/examples/01_recognizing_integers.re \
    src/examples/04_parsing_integers_blocks.re \
    src/examples/06_braille.ucs2.txt \
    src/examples/06_braille.utf16.txt \
    src/examples/03_arbitrary_large_input.re \
    src/examples/02_recognizing_strings.re \
    src/favicon.ico \
    src/feed/feed.png \
    src/feed/atom.xml \
    src/manual/warnings/condition_order/wcondition_order.re \
    src/manual/warnings/match_empty_string/wmatch_empty_string.re \
    src/manual/features/dot/php_json_dot.png \
    src/manual/features/dot/utf8_any.png \
    src/manual/features/dot/php_json_neato.png \
    src/manual/features/dot/utf8_any.re \
    src/manual/features/dot/php_json.re \
    src/manual/features/skeleton/example.c \
    src/manual/features/skeleton/example.c.line4.input \
    src/manual/features/skeleton/example.c.line4.keys \
    src/manual/features/skeleton/example.png \
    src/manual/features/skeleton/example_next.png \
    src/manual/features/skeleton/gen.sh \
    src/manual/features/skeleton/hex2.re \
    src/manual/features/skeleton/plot.png \
    src/about/1994_bumbulis_cowan_re2c_a_more_versatile_scanner_generator.pdf

OBJ_RST = $(SRC_RST:%.rst=%.html)

all: $(OBJ_RST)
	@ for f in $(SRC_OTH) $(SRC_CSS); do { mkdir -p "`dirname $$f`"; cp "$(VPATH)/$$f" "$$f"; } done

-include $(SRC_RST:%.rst=%.d)

# Option '--stylesheet' to 'rst2html' is used only to override dependency
# from default stylesheet; the real stylesheet is linked in template file.
# We have to manually insert dependency from template file.
.rst.html:
	@ mkdir -p "`dirname $@`"
	@ rst2html.py --stylesheet="$(VPATH)/$(SRC_CSS)" --template="$(VPATH)/$(SRC_TPL)" --record-dependencies="$*.dd" $< $@
	@ echo $@: "$(VPATH)/$(SRC_TPL)" `cat $*.dd` > $*.d && rm $*.dd
	@ echo $@

clean:
	rm $(OBJ_RST)

.SUFFIXES: .rst .html

.POSIX:

