## Route Configuration [Back](./../react_router.md)

A route configuration is basically a set of instructions (指令) to tell a router how to **match the URL**, and what code to run when it does.

For example, here we will render different components with React Router to match different URLs.

**URL**|**Components**
:-:|:---------
`/`|`App`
`/about`|`App -> About`
`/inbox`|`App -> Inbox`
`/inbox/messages/:id`|`App -> Inbox -> Message`


