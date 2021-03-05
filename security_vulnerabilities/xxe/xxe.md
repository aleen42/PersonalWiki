## XML External Entities (XXE) [Back](../security_vulnerabilities.md)

According to Wikipedia,

> An **XML External Entity** attack is a type of attack against an application that parses **XML** input. This attack occurs when **XML** input containing a reference to an **external entity** is processed by a weakly configured **XML** parser.

Because most XML parsers are vulnerable to XXE by default, developers should ensure that applications does not have such a vulnerability.

According to OWASP, the XML External Entities (XXE) main attack vectors are:

- XML processors where hackers can upload XML or hostile content in a XML document
- vulnerable code
- vulnerable dependencies
- vulnerable integrations

If you want to know more about examples of XXE, you can check [here](https://www.bugcrowd.com/advice-from-a-bug-hunter-xxe/). And to prevent XXE, some ways are advised by OWASP:

1. Use less complex data formats such as JSON, and avoid serialization of sensitive data if possible.
2. Patch or upgrade all XML processors and libraries in use.
3. Disable XML external entity and DTD processing in all XML parsers in the application, as per the OWASP Cheat Sheet ["XXE Prevention"](https://github.com/OWASP/CheatSheetSeries/blob/94b68ada0be6e92da22b3838e79d9d2f258e1247/cheatsheets/XML_External_Entity_Prevention_Cheat_Sheet.md).
4. Implement positive server-side input validation, filtering to prevent hostile data within XML documents, headers, or nodes.
5. Verify that XML or XSL file upload functionality validates incoming XML using XSD validation.
6. SAST tools can help detect XXE in source code.
     *Note: code review is the best alternative in large, complicated applications with many integrations.*

If you want to prevent outside the XML processor itself, you can consider using:

1. API security gateways.
2. [Web Application Firewalls (WAFs)](https://sucuri.net/website-firewall/).
