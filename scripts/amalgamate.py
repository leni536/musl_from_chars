import shutil
import sys
from textwrap import dedent

if __name__ == "__main__":
    filenames = [
        "include/musl_from_chars/chars_format.h",
        "include/musl_from_chars/fake_file.h",
        "include/musl_from_chars/shgetc.h",
        "include/musl_from_chars/floatscan.h",
        "include/musl_from_chars/from_chars.h",
        "src/from_chars.cpp",
    ]
    print(dedent('''
        #if !defined(MUSL_FROM_CHARS_AMALGAMATED) && !defined(MUSL_FROM_CHARS_AMALGAMATED_INTERFACE) && !defined(MUSL_FROM_CHARS_AMALGAMATED_DEFINITION)
            #define MUSL_FROM_CHARS_AMALGAMATED
        #endif
        #if (defined(MUSL_FROM_CHARS_AMALGAMATED) || defined(MUSL_FROM_CHARS_AMALGAMATED_DEFINITION)) && !defined(MUSL_FROM_CHARS_AMALGAMATED_INTERFACE)
            #define MUSL_FROM_CHARS_AMALGAMATED_INTERFACE
        #endif
        #ifndef MUSL_FROM_CHARS_AMALGAMATED_DEFINITION
            #define MUSL_FROM_CHARS_AMALGAMATED_SKIP_INSTANTIATION
        #endif
    ''')[1:-1])
    for filename in filenames:
        with open(filename) as file:
            shutil.copyfileobj(file, sys.stdout)
