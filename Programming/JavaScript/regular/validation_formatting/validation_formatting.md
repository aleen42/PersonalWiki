## Validation and Formatting [Back](./../regular.md)

This chapter mainly discusses recipes (秘訣) for validating and formatting common types of user input, and give a proper way for us to validate and format what we usually meet in reality development.

### Validate Email Addresses

- **Problem**

    How to check whether a provided email is a legal input?

- **Solution**
    - Simple

        **/^\S+@\S+$/i**

    - Simple, with restrictions on characters

        **/^[A-Z0-9+&#95;.-]+@[A-Z0-9.-]$/i**

    - Simple, with all validate local part characters

        **/^[A-Z0-9&#95;!#$%&'&#42;+/=?&#96;{|}~^.-]@[A-Z0-9.-]$/i**

    - No leading, trailing, or consecutive dots

        **/^[A-Z0-9&#95;!#$%&'&#42;+/=?&#96;{|}~^-]+(?:\.[A-Z0-9&#95;!#$%&'&#42;+/=?&#96;{|}~^-]+)&#42;@[A-Z0-9-]+(?:\.[A-Z0-9-]+)&#42;$/i**

    - Top-level domain has two to six letters

        **/^[\w!#$%&'&#42;+/=?&#96;{|}~^-]+(?:\.[\w!#$%&'&#42;+/=?&#96;{|}~^-]+)&#42;@(?:[A-Z0-9-]+\.)+[A-Z]{2,6}$/i**

- **Discussion**

    If you thought something as conceptually simple as validating an email address would have a simple one-size-fits-all regex solution, you're quite wrong. This recipe is a prime example that before you can start writing a regular expression, you have to decide *exactly* what you want to match. There is no universally agreed-upon rule as to which email addresses are valid and which not. It depends on your definition of *valid*.

    Allowing invalid addresses to slip through may be preferable to annoying people by blocking valid addresses.

    But if you want to avoid sending too many undeliverable emails, which still not blocking any real email addresses, the regex in "Top-level domain has two to six letters" is a good choice.

    What it means is that it all depends what you want.

    To build a complicated regex, you have to do this step-by-step, and defines a structure firstly before, like **/^\S+@\S+$/i**.

### Validate and Format Chinese Phone Numbers

- **Problem**

    Chinese phone numbers have a specific format including: **12345678901**, **123-4567-8901**, **123 4567 8901**, **+8612345678901**, **+86-123-4567-8901**, **(+86) 123 4567 8901**, and so on. If the phone number is valid, you may want to convert it all into a standard format: **(+86) 123 4567 8901**

- **Solution**

    ```js
    subject.replace(/(?:\(?\+86\)?)?[\s-]*(\d{3})[\s-]*(\d{4})[\s-]*(\d{4})/g, '(+86) $1 $2 $3');
    ```

- **Discussion**

    In China, a phone number will always have a number `1` at the first, so to validate more phone numbers, you can use a variation like **/(?:\(?\+86\)?)?[\s-]&#42;(1\d{2})[\s-]&#42;(\d{4})[\s-]&#42;(\d{4})/g**. Of course, this regex will have a problem when matching more than 11 numbers, which is actually not a Chinese phone number. Considering this problem, I'll improve it by restrict its head and tail like: **/(&#91;^(\d&#93;+)(?:\(?\+86\)?)?[\s-]&#42;(1\d{2})[\s-]&#42;(\d{4})[\s-]&#42;(\d{4})(?=&#91;^\d&#93;+?)/g**, and the corresponding replacement is `$1(+86) $2 $3 $4`.

### Validate and Format North American Phone Numbers

- **Problem**

    What if a North American phone? Match **1234567890**, **123-456-7890**, **123.456.7890**, **123 456 7890**, **(123) 456 7890**, and convert them all into a standard format: **(123) 456-7890**.

- **Solution**

    ```js
    subject.replace(/\(?([0-9]{3})\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})/g, '($1) $2-$3');
    ```

- **Discussion**

    If you want to limit matches to valid phone numbers according to the North American Numbering Plan, here are the basic rules:

- Area codes start with a number 2–9, followed by 0–8, and then any third digit.
- The second group of three digits, known as the central office or exchange code, starts with a number 2–9, followed by any two digits.
- The final four digits, known as the station code, have no restrictions.

    So the regex according to this rule should be: **/\(?([2-9][0-8][0-9])\)?[-. ]?([2-9][0-9]{2})[-. ]?([0-9]{4})/g**.

    Besides, you can also allow an optional, leading "1" for the country code: **/(?:\+?1[-. ]?)?\(?([0-9]{3})\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})/g**.

    To allow matching phone numbers that omit the local area code, enclose the first group of digits together with its surrounding parentheses and following separator in an optional, non-capturing group: **/(?:\(?([0-9]{3})\)?[-. ]?)?([0-9]{3})[-. ]?([0-9]{4})/g**.

### Validate International Phone Numbers

- **Problem**

    And what if we want to match international phone number, like **+86 123 4567 8901** of Chinese?

- **Solution**

    ```js
    function isValidate(phone) {
        return /^\+(?:[0-9] ?){6,14}[0-9]$/.test(phone);
    }
    ```

- **Discussion**

    The rules and conventions used to print international phone numbers vary significantly around the world, so it's hard to provide meaningful validation for an international phone number unless you adopt a strict format. Fortunately, there is a simple, industry standard notation specified by ITU-T E.123. And the regular expression above is responding to this rule. If you want to obey the notation specified by the Extensible Provisioning Protocol (EPP), you can use the following regex: **/^\+[0-9]{1,3}\.[0-9]{4,14}(?:x.+)?$/**;

### Validate Traditional Date Formats

- **Problem**

    Create a regex to match dates in the traditional formats: **mm/dd/yy**, **mm/dd/yyyy**, **dd/mm/yy**, and **dd/mm/yyyy**.

- **Solution**
    - Solution 1: Match any of these date formats, allowing leading zeros to be omitted

        **/^[0-3]?[0-9]/[0-3]?[0-9]/(?:[0-9]{2})?[0-9]{2}$/**

    - Solution 2: Match any of these date formats, require leading zeros:

        **/^[0-3][0-9]/[0-3][0-9]/(?:[0-9][0-9])?[0-9][0-9]$/**

    - Solution 3: Match **m/d/yy** and **mm/dd/yyyy**, allowing any combination of one or two digits for the day and month, and two or four digits for the year:

        **/^(1[0-2]|0?[1-9])/(3[01]|[12][0-9]|0?[1-9])/(?:[0-9]{2})?[0-9]{2}$/**

    - Solution 4: Match **mm/dd/yyyy**, requiring leading zeros:

        **/^(1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])/[0-9]{4}$/**

    - Solution 5: Match **d/m/yy** and **dd/mm/yyyy**, allowing any combination of one or two digits for the day and month, and two or four digits for the year:

        **/^(3[01]|[12][0-9]|0?[1-9])/(1[0-2]|0?[1-9])/(?:[0-9]{2})?[0-9]{2}$/**

    - Solution 6: Match **dd/mm/yyyy**, requiring leading zeros:

        **/^(3[01]|[12][0-9]|0[1-9])/(1[0-2]|0[1-9])/[0-9]{4}$/**

    - Solution 7: Match any of these date formats with greater accuracy, allowing leading zeros to be omitted:

        **/^(?:(1[0-2]|0?[1-9])/(3[01]|[12][0-9]|0?[1-9])|(3[01]|[12][0-9]|0?[1-9])/(1[0-2]|0?[1-9]))/(?:[0-9]{2})?[0-9]{2}$/**

    - Solution 8: Match any of these date formats with greater accuracy, requiring leading zeros:

        **/^(?:(1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])|(3[01]|[12][0-9]|0[1-9])/(1[0-2]|0[1-9]))/[0-9]{4}$/**

- **Discussion**

    You might think that something as conceptually trivial as a date should be an easy job for a regular expression. But it isn't, for two reasons.

- dates are such an everyday thing, humans are very sloppy with them.
- regular expressions work character by character rather than deal directly with numbers

    If you're going to validate an input, `^` and `$` are both what you should not use. Conversely, you should use a variation regex like: **/\b(1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])/[0-9]{4}\b/**.

### Validate Traditional Date Formats, Excluding Invalid Dates

- **Problem**

    How about weed out some invalid dates, such as Feb 31st.

- **Solution**

    One solution is to use code to validate what you have captured, but if you just use one regular expression, you can create a complex one like this:

    **/^(?:(0?2)/([12][0-9]|0?[1-9])|(0?[469]|11)/(30|[12][0-9]|0?[1-9])|(0?[13578]|1[02])/(3[01]|[12][0-9]|0?[1-9]))/((?:[0-9]{2})?[0-9]{2})$/**

    Respectively represents for:

    - February (29 days every year)

        **(0?2)/([12][0-9]|0?[1-9])**

    - 30-day months:

        **(0?[469]|11)/(30|[12][0-9]|0?[1-9])**

    - 31-day months

        **(0?[13578]|1[02])/(3[01]|[12][0-9]|0?[1-9]))**

    - year

        **((?:[0-9]{2})?[0-9]{2})**

- **Discussion**

    As it will be a complex regular expression, it's recommended to use code to do filtering for you rather than to create such a complex regex. If you do want to build this, you can have a analysis about it and use `|` to separate all cases.

### Validate Traditional Time Formats

- **Problem**

    How to validate times in various traditional time formats, such as **hh:mm** and **hh:mm:ss** in both 12-hour and 24-hour formats.

- **Solution**
    - Hours and minutes, 12-hour clock:

        **/^(1[0-2]|0?[1-9]):([0-5]?[0-9])( ?[AP]M)?$/**

    - Hours and minutes, 24-hour clock:

        **/^(2[0-3]|[01]?[0-9]):([0-5]?[0-9])$/**

    - Hours, minutes and seconds, 12-hour clock:

        **/^(1[0-2]|0?[1-9]):([0-5]?[0-9]):([0-5]?[0-9])( ?[AP]M)?$/**

    - Hours, minutes and seconds, 24-hour clock:

        **/^(2[0-3]|[01]?[0-9]):([0-5]?[0-9]):([0-5]?[0-9])$/**

- **Discussion**

    Validating times is considerably easier than validating dates. Every hour has 60 minutes, and every minute has 60 seconds. This means we don't need any complicated alternations in the regex.

    If you want to search all the time, you can use like regular expressions like this: **/\b(2[0-3]|[01]?[0-9]):([0-5]?[0-9])\b/g**.

### Validate ISO 8061 Dates and Times

- **Problem**

    Match dates and/or times in the official ISO 8601 format, which is the basis for many standardized date and time formats.

- **Solution**
    - **Dates**
        - Match **YYYY-MM-DD** or **YYYYMMDD** but not **YYYY-MMDD** or **YYYYMM-DD**:

        **/^([0-9]{4})(-?)(1[0-2]|0[1-9])\2(3[01]|0[1-9]|[12][0-9])$/**

        - Match original date like **2008-243**:

        **/^([0-9]{4})-?(36[0-6]|3[0-5][0-9]|[12][0-9]{2}|0[1-9][0-9]|00[1-9])$/**

    - **Weeks**
        - Match weeks of the year such as **2008-W35**:

        **/^([0-9]{4})-?W(5[0-3]|[1-4][0-9]|0[1-9])$/**

        - Match week dates like **2008-W35-6**:

        **/^([0-9]{4})-?W(5[0-3]|[1-4][0-9]|0[1-9])-?([1-7])$/**

    - **Times**
        - Match hours and minutes with optional colon(`:`):

        **/^(2[0-3]|[01][0-9]):?([0-5][0-9])$/**

        - Match hours, minutes, and seconds like **17:21:59** with optional colon(`:`):

        **/^(2[0-3]|[01][0-9]):?([0-5][0-9]):?([0-5][0-9])$/**

        - Time zone designator (e.g., **Z, +07** or **+07:00**) with optional colons and minutes:

        **/^(Z|[+-](?:2[0-3]|[01][0-9])(?::?(?:[0-5][0-9]))?)$/**

        - Hours, minutes, and seconds with time zone designator (e.g., **17:21:59+07:00**) with optional colons and minutes:

        **/^(2[0-3]|[01][0-9]):?([0-5][0-9]):?([0-5][0-9])(Z|[+-](?:2[0-3]|[01][0-9])(?::?(?:[0-5][0-9]))?)$/**

    - **Date and Times**
        - Calendar date with hours, minutes, and seconds (e.g., **2008-08-30 17:21:59** or **20080830 172159**) with required spaces between the date and the time, but optional hyphens and colons:

        **/^([0-9]{4})-?(1[0-2]|0[1-9])-?(3[01]|0[1-9]|[12][0-9]) (2[0-3]|[01][0-9]):?([0-5][0-9]):?([0-5][0-9])$/**

        - A more complicated solution is needed if we want to match date and time values that specify either all of the hyphens and colons, or none of them:

        **/^(?:([0-9]{4})-?(1[0-2]|0[1-9])-?(3[01]|0[1-9]|[12][0-9]) (2[0-3]|[01][0-9]):?([0-5][0-9]):?([0-5][0-9])|([0-9]{4})(1[0-2]|0[1-9])(3[01]|0[1-9]|[12][0-9]) (2[0-3]|[01][0-9])([0-5][0-9])([0-5][0-9]))$/**

    - **XML Schema dates and times**
        - Date, with optional time zone (e.g., **2008-08-30** or **2008-08-30+07:00**) but required hyphens:

        **/^(-?(?:[1-9][0-9]*)?[0-9]{4})-(1[0-2]|0[1-9])-(3[01]|0[1-9]|[12][0-9])(Z|[+-](?:2[0-3]|[01][0-9]):[0-5][0-9])?$/**

        - Time, with optional fractional seconds and time zone (e.g., **01:45:36** or **01:45:36.123+07:00**):

        **/^(2[0-3]|[01][0-9]):([0-5][0-9]):([0-5][0-9])(\.[0-9]+)?(Z|[+-](?:2[0-3]|[01][0-9]):[0-5][0-9])?$/**

        - Date and time, with optional fractional seconds and time zone (e.g., **2008-08-30T01:45:36** or **2008-08-30T01:45:36.123Z**).

        **/^(-?(?:[1-9][0-9]*)?[0-9]{4})-(1[0-2]|0[1-9])-(3[01]|0[1-9]|[12][0-9])T(2[0-3]|[01][0-9]):([0-5][0-9]):([0-5][0-9])(\.[0-9]+)?(Z|[+-](?:2[0-3]|[01][0-9]):[0-5][0-9])?$/**

- **Discussion**

    ISO 8601 defines a wide range of date and time formats. The regular expressions presented here cover the most common formats, but most systems that use ISO 8601 only use a subset. For example, in XML Schema dates and times, the hyphens and colons are mandatory (強制要求的). To make hyphens and colons mandatory, simply remove the question marks after them. To disallow hyphens and colons, remove the hyphens and colons along with the question mark that follows them.

    None of the regexes here attempts to exclude invalid day and month combinations, such as February 31st. To do this, you can considering using code to filter for you.

### Limit Input to Alphanumeric Characters

- **Problem**

    How to limit users' responses to one or more alphanumeric English characters (letters A–Z and a–z, and digits 0–9).

- **Solution**

    **/^[A-Za-z0-9]+$/**

- **Discussion**

    When we want to limit the input to ASCII characters, we can use regular expressions like **/^[\\x00-\\x7F]+$/**.

    Or limit input to ASCII non-control characters and line breaks by using **/^[\\n\\r\\x20-\\x7E]+/**.

    Or limit input to shared ISO-8859-1 and Windows-1252 characters by using **/^[\\x00-\\x7F\\xA0-\\xFF]+$/**.

### Limit the length of Texts

- **Problem**

    To test whether a string is composed of between 1 and 10 letters between A to Z.

- **Solution**

    **/^[A-Z]{1,10}$/**

- **Discussion**

    If you want to limit the length of an arbitrary (任意的) pattern, you can considering using a positive lookahead at the beginning of the pattern to ensure that the string is within the target length range like: **/^(?=[\\S\\s]{1,10}$)[\\S\\s]&#42;/**. It is important that the `$` anchor appears inside the lookahead because the maximum length test works only if we ensure that there are no more characters after we've reached the limit.

    If you want a regex to match any string that contains between 10 and 100 non-whitespace character: **/^\\s&#42;(?:\\S\\s&#42;){10,100}$/**. By default, `\s` matches all Unicode white-space, and `\S` matches everything else.

    Or if you want to limit the number of words: **/^\\W&#42;(?:\\w+\\b\\W&#42;){10,100}$/**. In JavaScript, `\w` will only match the ASCII characters A-Z, a-z, and &#95;, which means that it cannot correctly count words that contain non-ASCII letters and numbers. If you do want to count those words that contain, there's a possible workaround, which is to reframe he regex to count whitespace rather than word character sequences: **/^\\s&#42;(?:\\S+(?:\\s+|$)){10,100}$/**. In many cases, this will work the same as the previous solutions, although it's not exactly equivalent. For example, one difference is that compounds joined by a hyphen, such as "far-reaching", will now be counted as one word instead of two. The same applies to words with apostrophes, such as "don't".

### Limit the Number of Lines in Text

- **Problem**

    How to check whether a string is composed of five of fewer lines, without regard for how many total characters appear in the string?

- **Solution**

    **/^(?:&#91;&#94;\\r\\n&#93;&#42;(?:\\r\\n?|\\n)){0,4}&#91;&#94;\\r\\n&#93;&#42;$/**

- **Discussion**

    We can't simply omit this class and change the preceding quantifier to `{0,5}`, because then the text would have to end with a line break to match at all. So long as the last line was empty, it would also allow matching six lines, since six lines are separated by five line breaks. That's not good.

### Validate Affirmative (肯定的) Responses

- **Problem**

    How to check a configuration option or command-line response for a positive value? For example, you want to provide some flexibility in the accepted responses, so that **true**, **t**, **yes**, **y**, **okay**, **ok**, and **1** are all accepted in any combination of uppercase and lowercase.

- **Solution**

    **/^(?:1|t(?:rue)?|y(?:es)?|ok(?:ay)?)$/**

### Validate ZIP Codes

- **Problem**

    How to validate a ZIP code (U.S. portal code)? For example, match **12345** and **12345-6789**.

- **Solution**

    **/^[0-9]{5}(?:-[0-9]{4})?$/**

### Validate Canadian Postal codes

- **Problem**

    What if Canadian postal codes?

- **Solution**

    **/^(?!.&#42;[DFIOQU])[A-VXY][0-9][A-Z] ?[0-9][A-Z][0-9]$/**

### Validate U.K. Postal Codes

- **Problem**

    What if postal codes of U.K.?

- **Solution**

    **/^[A-Z]{1,2}[0-9R][0-9A-Z]? [0-9][ABD-HJLNP-UW-Z]{2}$/**

### Reformat Names From "FirstName LastName" to "LastName, FirstName"

- **Problem**

    How to convert people's names from the "FirstName LastName" format to "LastName, FirstName" for use in an alphabetical listing? Besides, names may contain a suffix, which is one of the values "Jr", "Jr.", "Sr", "Sr.", "II", "III", or "IV", with an optional preceding comma.

- **Solution**

    ```js
    function formatName(name) {
        return name.replace(/^(.+?) ([^\s,]+)(,? (?:[JS]r\.?|III?|IV))?$/i, '$2, $1$3');
    }
    ```

### Validate Password Complexity

- **Problem**

    If you're tasked with ensuring that any passwords chosen by users need to meet a complexity requirements

- **Solution**

    There're several code example that show how to validate password with complex requirements:

    - **Length bwetween 8 and 32 characters**

    ```js
    function validate(password) {
        return /^[\s\S]{8,32}$/.test(password);
    }
    ```

    - **ASCII visible and space characters only**

    ```js
    function validate(password) {
        return /[\x20-\x7E]+/.test(password);
    }
    ```

    - **One or more uppercase letters**

    ```js
    function validate(password) {
        return /[A-Z]/.test(password);
    }
    ```

    - **One or more lowercase letters**

    ```js
    function validate(password) {
        return /[a-z]/.test(password);
    }
    ```

    - **One or more number**

    ```js
    function validate(password) {
        return /[0-9]/.test(password);
    }
    ```

    - **One or more special characters**

    ```js
    function validate(password) {
        return /[ !"#$%&'()*+,\-./:;<=>?@[\\\]^_`{|}~]/.test(password);
    }
    ```

    - **Disallow three or more sequential identical characters like 111111**

    ```js
    function validate(password) {
        return !/([\s\S])\1\1/.test(password);
    }
    ```

- **Discussion**

    Using JavaScript to validate passwords in a web browser can be very beneficial for users, but make sure to also implement validation on the server, so that users are not able to disable JavaScript or to use custom scripts to circumvent (迴避) client-side validation.
