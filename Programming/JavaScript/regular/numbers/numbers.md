## Numbers [Back](./../regular.md)

Since the regex engine has not known the meaning after a number, this chapter has mainly matched all kinds of numbers with regular expressions.

### Integer numbers

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

### Strip leading zeros

- **Problem**

    How to match an integer number, and return the number without any leading zeros or delete the leading zeros?

- **Solution**

    ```js
    function stripLeadingZeros(subject) {
        subject = subject.replace(/\b0*([1-9][0-9]*|0)\b/, '$1');
    }
    ```

### Numbers within a certain range

- **Problem**

    How to match an integer number within a certain range of numbers?

- **Solution**
    - 1 to 12 (hour or month):

        **/^(1[0-2]|[1-9])$/**

    - 1 to 24 (hour):

        **/^(2[0-4]|1[0-9]|[1-9])$/**

    - 1 to 31 (day of the month):

        **/^(3[01]|[12][0-9]|[1-9])$/**

    - 1 to 63 (week of the year):

        **/^(5[0-3]|[1-4][0-9]|[1-9])$/**

    - 0 to 59 (minute or second):

        **/^[1-5]?[0-9]$/**

    - 0 to 100 (percentage):

        **/^(100|[1-9]?[0-9])$/**

    - 1 to 100:

        **/^(100|[1-9][0-9]?)$/**

    - 32 to 126 (principle ASCII codes):

        **/^(12[0-6]|1[01][0-9]|[4-9][0-9]|3[2-9])$/**

    - 0 to 127 (nonnegative signed byte):

        **/^(12[0-7]|1[01][0-9]|[1-9]?[0-9])$/**

    - -128 to 127 (signed byte):

        **/^(12[0-7]|1[01][0-9]|[1-9]?[0-9]|-(12[0-8]|1[01][0-9]|[1-9]?[0-9]))$/**

    - 0 to 255 (unsigned byte):

        **/^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$/**

    - 1 to 366 (day of the year):

        **/^(36[0-6]|3[0-5][0-9]|[12][0-9]{2}|[1-9][0-9]?)$/**

    - 1900 to 2099 (year):

        **/^(19|20)[0-9]{2}$/**

    - 0 to 32767 (nonnegative signed word):

        **/^(3276[0-7]|327[0-5][0-9]|32[0-6][0-9]{2}|3[01][0-9]{3}|[12][0-9]{4}|[1-9][0-9]{1,3}|[0-9])$/**

    - -32768 to 2767 (signed word):

        **/^(3276[0-7]|327[0-5][0-9]|32[0-6][0-9]{2}|3[01][0-9]{3}|[12][0-9]{4}|[1-9][0-9]{1,3}|[0-9]|-(3276[0-8]|327[0-5][0-9]|32[0-6][0-9]{2}|3[01][0-9]{3}|[12][0-9]{4}|[1-9][0-9]{1,3}|[0-9]))$/**

    - 0 to 65535 (unsigned word):

        **/^(6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{1,3}|[0-9])$/**

### Floating-point numbers

- **Problem**

    How to detect a floating-point number from a string?

- **Solution**
    - Mandatory sign (指示標誌), integer, fraction (小數部分), and exponent (指數部分):

        **/^[-+][0-9]+\.[0-9]+[eE][-+]?[0-9]+$/**

    - Mandatory sign, integer, and fraction, but no exponent:

        **/^[-+][0-9]+\.[0-9]+$/**

    - Optional sign, mandatory integer and fraction, and no exponent:

        **/^[-+]?[0-9]+\.[0-9]+$/**

    - Optional sign and integer, mandatory fraction, and no exponent:

        **/^[-+]?[0-9]*\.[0-9]+$/**

### Numbers with thousand separators

- **Problem**

    How to match numbers with comma as the thousand separator and the dot as the decimal separator?

- **Solution**
    - Mandatory integer and fraction:

        **/^[0-9]{1,3}(,[0-9]{3})&#42;\.[0-9]+$/**

### Add thousand separators to numbers

- **Problem**

    How to detect numbers from a string, and add thousand separators for them?

- **Solution**

    ```js
    function addThousandSeparators(subject) {
        var regex = /[0-9](?=(?:[0-9]{3})+(?![0-9]))/;

        while (regex.test(subject)) {
            subject = subject.replace(regex, '$&,');
        }
    }
    ```

- **Discussion**

    If you also want to add thousand separators in a number with fraction, you can use the following complicated way:

    ```js
    function addThousandSeparators(subject) {
        subject = subject.replace(/(^|[^0-9.])([0-9]{4,})/g, function($0, $1, $2) {
            return $1 + $2.replace(/[0-9](?=(?:[0-9]{3})+(?![0-9]))/g, "$&,");
        });
    }
    ```

### Roman Numerals

- **Problem**

    You may want to match Roman numerals like IV, XIII, or MVIII.

- **Solution**
    - Roman numerals without validation:

        **/^[MDCLXVI]+$/**

    - Modern Roman numerals, strict:

        **/^(?=[MDCLXVI])M&#42;(C[MD]|D?C{0,3})(X[CL]|L?X{0,3})(I[XV]|V?I{0,3})$/**

    - Modern Roman numerals, flexible:

        **/^(?=[MDCLXVI])M&#42;(C[MD]|D?C&#42;)(X[CL]|L?X&#42;)(I[XV]|V?I&#42;)$/**

    - Simple Roman numerals:

        **/^(?=[MDCLXVI])M&#42;D?C{0,4}L?X{0,4}V?I{0,4}$/**

- **Discussion**

    If you want to convert a roman numerals to decimal one, you can check the [post: CONVERTING ROMAN NUMERALS](./../../../../post/converting_roman_numerals/converting_roman_numerals.md)
