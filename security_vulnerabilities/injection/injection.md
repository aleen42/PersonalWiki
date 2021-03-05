## Injection [Back](../security_vulnerabilities.md)

Injections are also known as code injections, which means that the attackers can sent some invalid data to the web applications to make it do something unexpected. The most common example around such a vulnerabilities is the **SQL query consuming untrusted data**.

```js
const query = `select * from accounts where id = '${param.id}'`;
```

Such a query can be exploited by calling up the web application with passing `'or'1'=1` to `param.id` , causing the return of all data on the database table.

The core of a code injection vulnerability is the lack of validation of inputted parameters:

> Anything that accepts parameters as input can potentially be vulnerable to a code injection attack.

To avoid SQL injections, **OWASP** has recommended that:

> Keep data separated from commands and queries.

1. Prefer to using a safe API, which has avoided the use of the interpreter entirely, or provided a parametrized interface, or even migrated to use Object Relational Mapping tools (ORMs).
2. Prefer to use positive or "whitelist" server-side input validation.
3. Try to escape special characters using the specific escape syntax for the interpreter when querying.
4. Take some LIMIT and other SQL controls within queries for mass data.

To make it simple, there are two main core we need to know:

1. Separation of data from the web application logic.
2. Settings to limit data exposure (暴露) when there are successful injection attacks.

Finally, pay more attention to such a kind of vulnerability, as it may results in mass disclosure (揭露) of confidential information.
