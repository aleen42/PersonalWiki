## How to set ssh with asymmetric keys on servers [Back](./qa.md)

### 1. Generate asymmetric keys **private/public**

#### Linux/Mac

```bash
ssh-keygen -t ed25519 -o -a 100 -C "comment here"
ssh-keygen -t rsa -b 4096 -o -a 100 -C "comment here"
```

- **t**: types of key
- **C**: used to tag who the certification belongs to
- **passphrase**: the password to protect private key, which can be empty.

*Notice that: In general, keys will be saved in the `.ssh` directory of the root, in which `id_rsa` is the private one while `id_rsa.pub` is the public one*

#### Windows

In Windows, we can use **PuTTY** to generate private/public keys: