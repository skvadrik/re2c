# Author: Doug Cook
# Copyright: This module has been placed in the public domain.

"""
Simple text writer for Docutils.
"""

__docformat__ = 'reStructuredText'

import typing
import textwrap
from docutils import writers, nodes

_PARAGRAPH_INDENT = 4
_LITERAL_INDENT = 8
_LIST_INDENT = 4

class _Escaper:

    cache = {}

    def __getitem__(self, key : int) -> str:
        try:
            return _Escaper.cache[key]
        except:
            pass

        if key == ord('"'):
            ch = '\\"'
        elif key == ord('\\'):
            ch = '\\\\'
        elif key < 32:
            ch = '\\{0:03o}'.format(key)
        elif key < 128:
            ch = chr(key)
        elif key < 0x10000:
            ch = '\\u{0:04x}'.format(key)
        else:
            ch = '\\U{0:08x}'.format(key)

        _Escaper.cache[key] = ch
        return ch

class Writer(writers.Writer):

    @staticmethod
    def __validate_text_width(
        setting, value, option_parser,
        config_parser=None, config_section=None
        ) -> int:
        value = int(value)
        if value < 40:
            raise ValueError("value too small; must be at least 40")
        return value

    supported = ('txt', 'c')
    """Formats this writer supports."""

    settings_spec = (
        'TEXT Writer Options',
        None,
        ( ('If set, generate a C file instead of a text file.',
          ['--variable-name'],
          {}
          ),
          ('Specify the maximum line length before wrapping. (default: 79)',
          ['--text-width'],
          {'default': 79, 'type': 'int', 'validator': __validate_text_width }
          )
        )
      )

    config_section = 'docutils_txt writer'
    config_section_dependencies = ('writers',)

    output = None
    """Final translated form of `document`."""

    def __init__(self):
        writers.Writer.__init__(self)
        self.translator_class = Translator

    def translate(self):

        visitor = self.translator_class(self.document)
        self.document.walkabout(visitor)

        if self.document.settings.variable_name:
            esc = _Escaper()
            lines = []
            lines.append('extern const char* ' + self.document.settings.variable_name + ';')
            lines.append('const char* ' + self.document.settings.variable_name + ' =')
            for line in visitor.output:
                lines.append('"' + line.translate(esc) + '\\n"')
            lines.append(';')
        else:
            lines = visitor.output
        
        if len(lines) != 0 and lines[-1] != '':
            lines.append('')

        self.output = '\n'.join(lines)

class Translator(nodes.NodeVisitor):

    indent: int
    literal: int
    output: typing.List[str]
    wrapper: textwrap.TextWrapper

    def __init__(self, document : nodes.document):
        nodes.NodeVisitor.__init__(self, document)
        self.indent = 0
        self.literal = 0
        self.output = []
        self.wrapper = textwrap.TextWrapper(width = document.settings.text_width)

    def __append_text(self, text : str) -> None:
        spaces = ' ' * self.indent
        if self.literal != 0:
            for line in text.split('\n'):
                self.output.append(spaces + line)
        else:
            self.wrapper.initial_indent = spaces
            self.wrapper.subsequent_indent = spaces
            self.output.extend(self.wrapper.wrap(text))
    
    def __append_newline(self) -> None:
        if len(self.output) != 0 and self.output[-1] != '':
            self.output.append('')

    # Descend

    def visit_document(self, document : nodes.Element):
        pass

    def depart_document(self, document : nodes.Element):
        pass

    def visit_section(self, node : nodes.Element):
        pass

    def depart_section(self, node : nodes.Element):
        pass

    def visit_definition_list_item(self, node : nodes.Element):
        pass

    def depart_definition_list_item(self, node : nodes.Element):
        pass

    # Lists

    def visit_bullet_list(self, node : nodes.Element):
        self.__list_begin()

    def depart_bullet_list(self, node : nodes.Element):
        self.__list_end()

    def visit_enumerated_list(self, node : nodes.Element):
        self.__list_begin()

    def depart_enumerated_list(self, node : nodes.Element):
        self.__list_end()

    def visit_definition_list(self, node : nodes.Element):
        self.__list_begin()

    def depart_definition_list(self, node : nodes.Element):
        self.__list_end()

    def visit_field_list(self, node : nodes.Element):
        self.__list_begin()

    def depart_field_list(self, node : nodes.Element):
        self.__list_end()

    def visit_option_list(self, node : nodes.Element):
        self.__list_begin()

    def depart_option_list(self, node : nodes.Element):
        self.__list_end()

    # Preformatted

    def visit_literal_block(self, node : nodes.Element):
        self.__pre_begin()

    def depart_literal_block(self, node : nodes.Element):
        self.__pre_end()

    def visit_doctest_block(self, node : nodes.Element):
        self.__pre_begin()

    def depart_doctest_block(self, node : nodes.Element):
        self.__pre_end()

    def visit_math_block(self, node : nodes.Element):
        self.__pre_begin()

    def depart_math_block(self, node : nodes.Element):
        self.__pre_end()

    # Text

    def visit_title(self, node : nodes.Element):
        self.__do_newline_text(node.astext().upper())

    def visit_subtitle(self, node : nodes.Element):
        self.__do_newline_text(node.astext())

    def visit_term(self, node : nodes.Element):
        self.__do_newline_text(node.astext())

    def visit_definition(self, node : nodes.Element):
        self.__do_paragraph(node.astext())

    def visit_paragraph(self, node : nodes.Element):
        self.__do_paragraph(node.astext())

    def visit_block_quote(self, node : nodes.Element):
        self.__do_paragraph(node.astext())

    def visit_Text(self, node : nodes.Text):
        self.__do_tight_text(node.astext())

    def unknown_visit(self, node : nodes.Node):
        self.__do_tight_text(node.astext())
    
    # Invisible

    def visit_meta(self, node : nodes.Element):
        raise nodes.SkipNode

    def visit_comment(self, node : nodes.Element):
        raise nodes.SkipNode

    def visit_substitution_definition(self, node : nodes.Element):
        raise nodes.SkipNode

    def visit_target(self, node : nodes.Element):
        raise nodes.SkipNode

    def visit_pending(self, node : nodes.Element):
        raise nodes.SkipNode

    def visit_raw(self, node : nodes.Element):
        raise nodes.SkipNode

    # Implementation

    def __list_begin(self):
        self.indent += _LIST_INDENT

    def __list_end(self):
        self.indent -= _LIST_INDENT

    def __pre_begin(self):
        self.__append_newline()
        self.indent += _LITERAL_INDENT
        self.literal += 1

    def __pre_end(self):
        self.indent -= _LITERAL_INDENT
        self.literal -= 1

    def __do_tight_text(self, text : str):
        self.__append_text(text)
        raise nodes.SkipNode

    def __do_newline_text(self, text : str):
        self.__append_newline()
        self.__append_text(text)
        raise nodes.SkipNode

    def __do_paragraph(self, text : str):
        self.__append_newline()
        self.indent += _PARAGRAPH_INDENT
        self.__append_text(text)
        self.indent -= _PARAGRAPH_INDENT
        raise nodes.SkipNode

# vim: set fileencoding=utf-8 et ts=4 ai :
