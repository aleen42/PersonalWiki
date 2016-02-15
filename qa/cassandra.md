## What is Cassandra [Back](./qa.md)

<img src="./cassandra_banner.jpg">

- **Cassandra** is a ideal database used for social network. It combines **Dynamo** of *Amazon* with **BitTable** of *Google*, which is based on Column Family(列簇).
- Some characteristics:
    - **Dynamo**:
        - Symmetric(對稱的) P2P framework
            - Without special node(solving the problem of SPOF(單點失效))
        - Distributed Management based on Gossip
        - Store data with distributed hash tables.
            - pluggable partition(可插拔分區)
            - pluggable topologies(可插拔拓撲)
            - pluggable store strategics(可插拔存放策略)
        - Configurable(consistency)
    - **BigTable**:
        - Column Family Data Model
            - configurable, 2-levels maps, super column family
        - SSTable
            - Append-only commit log
            - Mentable(buffer and sort)
            - Unmodifiable SSTable files
        - Integrated **Hadoop**

#### Data Model

- Column: the minimum components of a data, and it's composed of **Name**, **Value**, and **Timestamp**.
- *Notice: name and value should be byte[], which a string of any length.*

```json
{
    /** this is a column */
    name: "email"
    value: "aleen42@vip.qq.com"
    timestamp: 1455517240
}
```

- SuperColumn: the name is same as Column, while the value is a set of columns. In additionally, they don't have timestamps.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
