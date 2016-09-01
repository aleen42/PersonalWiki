## React + Redux [Back](./../redux.md)

Actually Redux has no relation to React, but most people will use it with React, because in React, you can describe your UI with **state**, which can be managed by Redux.

### Installation

React bindings are not included in Redux by default. You need to install them explicitly:

```bash
npm install react-redux --save
```

### Presentational and Container Components

React bindings for Redux embrace the idea of **separating presentational and container components**.

|**Presentational Components**|**Container Components**
---:|:------------------------|:-----------------------
**Purpose**|How things look (markup, styles)|How things work (data fetching, state updates)
**Aware of Redux**|No|Yes
**To read data**|Read data from props|Dispatch Redux actions