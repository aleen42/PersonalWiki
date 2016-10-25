## Basic Skills [Back](./../regular.md)

### Match Literal Text

- **Problem**

    Create a regular expression to exactly match the sentence: **The punctuation characters in the SCII table are: !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~**.

- **Solution**:

    /The punctuation characters in the SCII table are: !"#\$%&'\(\)\*\+,-\./:;<=>\?@\[\\]\^_`\{\|}~/

- **Discussion**

    Any regular expression that does not include any of the dozen character **$()\*+.?[\^{|** simply matches itself. These **12** punctuation characters (標點符號) are called `metacharacters`, which you should add a blackslash `\` before them, if you want to match them literally.

### Match Nonprintable Characters

- **Problem**

    Match a string of the following ASCII control characters: bell (07), escape (1B), form feed (0C), line feed (0A), carriage return (0D), horizontal tab (09), and vertical tab (0B).

- **Solution**

    /\x07\x1B\f\n\r\t\v/

- **Discussion**

    Seven of the most commonly used ASCII control characters have dedicated `escape sequences`, which all consists of a blackslash `\` followed by a letter. JavaScript does not support `\a` and `\e`, and so for JavaScript we need a separate solution.

- **Variation**

    In JavaScript, we can also match those seven control characters by: /\cG\x1B\cL\cJ\cM\cI\cK/, and using \cA through \cZ, you can match one of the 26 control characters too. The `c` must be lowercase, and the letter following the `c` is case insensitive, which is recommended to use an uppercase letter.

    Besides, we can also use the 7-bit character set to match control characters: /\x07\x1B\x0C\x0A\x0D\x09\x0B/. It's recommended to use the Unicode code rather than to use \x80 through \xFF, because various regex engine will interpret various meanings for them.

    ASCII table with 7-bit characters are described as followed:

1|0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F
:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:
0|NUL|SOH|STX|ETX|EOT|ENQ|ACK|BEL|BS|HT|LF|VT|FF|CR|SO|SI
1|DLE|DC1|DC2|DC3|DC4|NAK|SYN|ETB|CAN|EM|SUB|ESC|FS|GS|RS|US
2|SP|!|"|#|$|%|&|'|(|)|*|+|,|-|.|/
3|0|1|2|3|4|5|6|7|8|9|:|;|<|=|>|?
4|@|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O
5|P|Q|R|S|T|U|V|W|X|Y|Z|[|\|]|^|_
6|`|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o
7|p|q|r|s|t|u|v|w|x|y|z|{|&#124;|}|~|DEL
