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

    In China, a phone number will always have a number `1` at the first, so to validate more phone numbers, you can use a variation like **/(?:\(?\+86\)?)?[\s-]&#42;(1\d{2})[\s-]&#42;(\d{4})[\s-]&#42;(\d{4})/g**. Of course, this regex will have a problem when matching more than 11 numbers, which is actually not a Chinese phone number. Considering this problem, I'll improve it by restrict its head and tail like: **/([^(\d]+)(?:\(?\+86\)?)?[\s-]&#42;(1\d{2})[\s-]&#42;(\d{4})[\s-]&#42;(\d{4})(?=[^\d]+?)/g**, and the corresponding replacement is `$1(+86) $2 $3 $4`.

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
