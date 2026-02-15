## How to specify a ssh key for some git operations on a certain domain [Back](./qa.md)

Sometimes, the company you are working on will use a GitLab to manage their projects, on which you may have to submit code with ssh keys. So in the local git client, how can we specify a ssh key for some git operations for a certain domain, like **git.company.com**?

To do so, you may have to create a configuration file named `config` in the folder `~/.ssh/`:

```
Host git.company.com
    HostName git.company.com
    User git
    IdentityFile ~/.ssh/certain
```

In this file, it's apparent to see that the private key `certain` has been specified for git operations around projects on the domain **git.company.com**.
