#!/usr/bin/env python3

"""
rst2txt.py
======

This module provides a simple command line interface that outputs
plain text formatted from ReStructuredText source.
"""

import locale
try:
    locale.setlocale(locale.LC_ALL, '')
except Exception:
    pass

from docutils.core import publish_cmdline, default_description

import docutils_txt

description = ("Generates plain text.  "
               + default_description)

publish_cmdline(writer = docutils_txt.Writer(), description = description)
