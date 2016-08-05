## Differences between URL and URI [Back](./qa.md)

- 概念常見於**Java**
- **URI**(Uniform Resource Identifier): 統一資源標識符, 用來唯一識別一個資源. (URI只是語義上的抽象概念, 可是絕對路徑或相對路徑)
- **URL**(Uniform Resource Locator): 統一資源定位器, 屬於URI的一種. 用於標識一個唯一資源,且指明如何定位這個資源的位置. (由於URL需要定位位置, 因此必須是絕對路徑)
	- absolute URL / relative URL: 只是區別是否包含scheme
	- URL一般格式: ```scheme://host:port/path?```
- **URN**(Uniform Resource Name): 统一资源命名, 通過名字來標識資源. 如: ```mailto:java-net@java.sun.com```
