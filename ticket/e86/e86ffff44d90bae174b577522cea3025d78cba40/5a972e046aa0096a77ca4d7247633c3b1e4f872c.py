#!/usr/bin/env python

#python >= 2.3
#run from doc/latex/wx directory

from sys import argv, stderr
import re
from sets import Set
from difflib import unified_diff

category_filename  = "category.tex"
alphabetic_filename = "classes.tex"


category_classes = {}
alphabetic_classes = {}
pseudoalphabetical = []

def get_by_category():
    """collecting classes from "by category" list"""
    for i in file(category_filename):
        r = re.match(r"[^%]*helpref\{(wx\w+)\}\{(\w+)\}", i)
        if r:
            category_classes[r.group(2)] = r.group(1)


def _get_filenames():
    """collecting file names \input'ed in alphabetical list"""
    files = []
    for i in file(alphabetic_filename):
        if not i.strip(): #blank
            continue
        r = re.search(r"^[^%]*\\input\s+(\w+.tex)", i)
        if r: 
            files.append(r.group(1))
    return files


def get_alphabetical():
    """collecting classes in "alphabetical" list"""
    for filename in _get_filenames():
        for line in file(filename):
            if re.match(r"\\section", line): 
                warn = "WARNING: \\section in %s has " % filename
                rc= re.search(r"\\class\{(\w+)\}", line)
                if not rc: 
                    print >>stderr, warn + " no \\class: %s" % line.rstrip()
                    continue
                rl= re.search(r"\\label\{(\w+)\}", line)
                if not rl: 
                    print >>stderr, warn + "no \\label: %s" % line.rstrip()
                    continue
                alphabetic_classes[rl.group(1)] = rc.group(1)
                pseudoalphabetical.append(rc.group(1))


def print_missing_classes(tex=False):
    """ checking for missing classes and printing to stdout """
    as = Set(alphabetic_classes.keys())
    cs = Set(category_classes.keys())
    if tex:
        for i in as-cs:
            print r"\twocolitem{\helpref{wxSingleInstanceChecker}{wxsingleinstancechecker}}{...}"
    else:
        print "Classes that are in Alphabetic list and not in Category list: "
        for i in as-cs:
            print "%s\t\t(%s)" % (i, alphabetic_classes[i])
        print "---------------- end --------------\n"
        print "Classes that are in Category list and not in Alphabetic list: "
        for i in cs-as:
            print "%s\t\t(%s)" % (i, category_classes[i])
        print "---------------- end --------------\n"



def print_nonalphabetic_diff():
    """ checking alphabetic order and printing to stdout """
    really_alphabetical = pseudoalphabetical[:]
    really_alphabetical.sort(lambda x, y: cmp(x.lower(), y.lower()))
    for i in unified_diff(pseudoalphabetical, really_alphabetical, n=1):
        print i

def main():
    if len(argv) < 2 or argv[1] not in ('a', 'm', 't'):
        print """\
   Usage:
    %s a \t\t check for alphabetic order
    %s m \t\t check for missing classes in by-category list
    %s t \t\t prints latex that can be inserted into %s
    Run it from .../doc/latex/wx directory
    """ % (argv[0], argv[0], argv[0], category_filename)
    elif argv[1] == 'a':
        get_alphabetical()
        print_nonalphabetic_diff()
    else:
        get_by_category()
        get_alphabetical()
        print_missing_classes(argv[1]=='t')

if __name__ == "__main__":
    main()

 	  	 
