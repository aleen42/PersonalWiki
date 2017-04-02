## The structure of providers in Coremail	[Back](./../coremail.md)

Before talking about the structure of providers in Coremail systems, we may need to know where such a system apply to?

Coremail system is generally applied to several cases:

- an email system with huge amounts of users
- hosting email system
- email systems of enterprises

Providers means the running and managing part of a whole Coremail system, which should be single. In a provider, there will be multiple organizations, supporting multiple domains. For users in such a system, Coremail has provided different levels of servers (COS), which is enumerable, to maintain resources.

> Provider
>> Organizations
>>> Organization Units (Departments)
>>>> Users (entity, non-entity)

Any user will have a level of service (COS), which can also be used to identified users.
