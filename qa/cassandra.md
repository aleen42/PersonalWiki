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

- **Column**: the minimum components of a data, and it's composed of **Name**, **Value**, and **Timestamp**.
- *Notice: name and value should be byte[], which a string of any length.*

```json
{
    /** this is a Column */
    name: "email"
    value: "aleen42@vip.qq.com"
    timestamp: 1455517240
}
```

- **SuperColumn**: the name is same as Column, while the value is a set of columns. In additionally, they don't have timestamps.

```json
{
    /** this is a SuperColumn */
    name: "addresses"
    /** the value can contains infinite Columns */
    value: {
        street: { name: "street", value: "xxx xxx xxx Road", timestamp: 1455517515 },
        city: { name: "city", value: "Foshan", timestamp: 1455517515 },
        zip: { name: "zip", value: "528031", timestamp: 1455517515 }
    }
}
```

- Both **SuperColumn Family** and **Column Family** describe a set of SuperColumn and Column.
- Sorting:
    - *Notice: in Cassandra, data is sorted by Column name by default.*
    - Configurable:
        - Set `CompareWith` Attribute (Column Family)
        - Set CompareSubColumnsWith (SuperColumn Family)
    - Value for configuration:
        - BytesType
        - UTF8Type
        - LexicalUUIDType
        - TimeUUIDType
        - AsciiType
        - Column name

#### Partition Strategics

- In Cassandra, **Token** is the key point for partitions, and there is a unique token for each node, describing the range of data in which.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
