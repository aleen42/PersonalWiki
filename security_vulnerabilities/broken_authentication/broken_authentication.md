## Broken Authentication [Back](../security_vulnerabilities.md)

A broken authentication vulnerability can allow an attacker to use manual and/or automatic mediums to try to gain control over any account he/she wants in a system -- or even worse -- to gain complete control over the system.

Such a vulnerability always happens when a system has a bad session management, like lost of timeout mechanism. The second most common case is allowing user to brute force (暴力破解) username and password combination.

According to OWASP, a web application contains a broken authentication vulnerability if it:

1. Allow automated attacks with a list of username and passwords.
2. Allow brute force or other automated attacks.
3. Allow default, weak, or well-known passwords, like "123456".
4. Uses weak or ineffective password recovery processes, such as "knowledge-based answers".
5. Uses plain text, weakly encrypted or hashed passwords.
6. Miss or use ineffective multi-factor authentication.
7. Exposes Session IDs in the URL.
8. Without using a temporarily session for the login process.
9. Without checking whether the session is valid anywhere.

In order to avoid broken authentication vulnerabilities, make sure the developers apply to the best practices of website security and support them by providing access to **external security audits** and enough time to properly **test the code** before deploying to production.

As for technical recommendations:

1. Implement multi-factor authentication when possible to avoid brute force, automated attacks, or stolen credential re-use attacks.
2. Do not deploy default credentials, particularly for administrators.
3. Implement a sufficient complicated password policies to avoid weak passwords.
4. Limit or increasingly delay failed login attempts. Sometimes we can use some blacklists strategy to mark down some invalid login attempts.
5. Hide session IDs, and design an entire session manager to create, destroy sessions when necessary.
