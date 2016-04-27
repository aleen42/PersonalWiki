## How to set ssh with asymmetric keys on servers [Back](./qa.md)

#### Generate asymmetric keys **private/public**

##### Linux

```bash
ssh-keygen -t ed25519 -o -a 100 -C "comment here"
ssh-keygen -t rsa -b 4096 -o -a 100 -C "comment here"
```

- **t**: types of key
- **C**: used to tag who the certification belongs to
- **passphrase**: the password to protect private key, which can be empty.

*Notice that: In general, *