## Numbers [Back](./../regular.md)

Since the regex engine has not known the meaning after a number, this chapter has mainly matched all kinds of numbers with regular expressions.

### Interget numbers

- **Problem**

    Detect an integer decimal number from a string.

- **Solution**
    - Find any positive integer decimal numbers:

        **/\\b[0-9]+\\b/**

    - Check whether a test string hold just a positive integer decimal number:

        **/^[0-9]+$/**

    - Find any positive integer decimal number, allowing leading whitespaces to be included in the regex match:

        **/(^|\\s)([0-9]+)(?=$|\\s)/**

    - Find any integer decimal number with an optional leading plus or minus sign:

        **/[+-]?\\b[0-9]+\\b/**

    - Check whether a test string holds just an integer decimal number with optional sign:

        **/^[+-]?[0-9]+$/**

    - Find any integer decimal number with optional sign, allowing whitespace between the number and the sign, but no leading whitespace without the sign:

        **/(?:[+-] &#42;)?\\b[0-9]+\\b/**

### Hexadecimal Numbers

- **Problem**

    Detect an hexadecimal number from a string.

- **Solution**
    - Find any hexadecimal number in a string:

        **/\\b[0-9A-F]+\\b/i**

    - Check whether a test sting holds just a hexadecimal number:

        **/^[0-9A-F]+$/i**

    - Find a hexadecimal number with a `0x` prefix:

        **/\\b0x[0-9A-F]+\\b/i**

    - Find a hexadecimal number with an `&H` prefix:

        **/\\b&H[0-9A-F]+\\b/i**

    - Find a hexadecimal with an `H` suffix:

        **/\\b[0-9A-F]+H\\b/i**

    - Find a hexadecimal byte value or 8-bit number:

        **/\\b[0-9A-F]{2}\\b/i**

    - Find a hexadecimal word value or 16-bit number:

        **/\\b[0-9A-F]{4}\\b/i**

    - Find a hexadecimal double word value or 32-bit number:

        **/\\b[0-9A-F]{8}\\b/i**

    - Find a hexadecimal quad word value or 64-bit number:

        **/\\b[0-9A-F]{16}\\b/i**

    - Find a string of hexadecimal bytes:

        **/\\b(?:[0-9A-F]{2})+\\b/**

### Binary Numbers

- **Problem**

    Detect a binary number from a string.

- **Solution**
    - Find a binary number in a string:

        **/\\b[01]+\\b/**

    - Check whether a text string holds just a binary number:

        **/^[01]+$/**

    - Find a binary number with a `0b` prefix:

        **/\\b0b[01]+\\b/**

    - Find a binary number with a `B` suffix:

        **/\\b[01]+B\\b/i**

    - Find a binary byte value or 8-bit number:

        **/\\b[01]{8}\\b/**

    - Find a binary word value or 16-bit number:

        **/\\b[01]{16}\\b/**

    - Find a string of bytes:

        **/\\b(?:[01]{8})+\\b/**

### Octal Numbers

- **Problem**

    Detect an octal number in a string.

- **Solution**
    - Find an octal number from a string:

        **/\\b0[0-7]&#42;\\b/**

    - Check whether a text string holds just an octal number:

        **/^0[0-7]&#42;$/**

    - Find an octal number with a `0o` prefix:

        **/\\b0o[0-7]+\\b/**

### Decimal Numbers

- **Problem**

    Detect an integer decimal number in a string.

- **Solution**
    - Find any positive integer decimal number without a leading zero from a string:

        **/\\b(0|[1-9][0-9]&#42;)\\b/**

    - Check whether a string holds just a positive integer decimal number without a leading zero:

        **/^(0|[1-9][0-9]&#42;)$/**
