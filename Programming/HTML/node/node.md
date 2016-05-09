## Layers of nodes [Back](./../HTML.md)

- In **Dom**,
	- **Document**: the **top** node
	- **DocumentType**: `<!DOCTYPE>`
	- **DocumentFragment**: can store other nodes like Document.TE
	- **Element**: contents between a tag(nodes with **properties** and **sub-nodes**).
	- **Attr**: a pair of properties and values
	- **Text**: contents between a tag in **XML**(nodes with only text inside).
	- **CDataSection**: `<![CDATA[]]>`, can only conclude nodes of **text**.
	- **Entity**: define an entity like `<!ENTITY foo "foo">`.
	- **EntityReference**: a reference to an entity like `&nbsp;`.
	- **ProcessingInstruction**: stand for a PI, like `<?target data?>`.
	- **Comment**: XML comment.
	- **Notation**: symbols in Document Type Definition(DTD).

- **Properties** or **Methods** of nodes:
	- **NodeList**: a list of child nodes
	- **NamedNodeMap**: a map of paired keys with **attributes** and **values**

Properties/Methods|Types/Returned types|Descriptions
------------------|--------------------|------------
nodeName|String|the name of the node
nodeValue|String|the value of the node
nodeType|Number|the type of the node
ownerDocument|Document|the owner document of the node
firstChild|Node|the first node in the list - **childNodes**
lastChild|Node|the last node in the list - **childNodes**
childNodes|NodeList|a list of all the child nodes
previousSibling|Node|the previous brother node
nextSibling|Node|the next brother node
attributes|NamedNodeMap|conclude the Attr which can represent the properties of this node
hasChildNodes()|Boolean|return true when there is a child node
appendChild(Node)|Node|add a node into the list - **childNodes**
removeChild(Node)|Node|remove a node from the list - **childNodes**
replaceChild(newnode, oldnode)|Node|replace an oldnode from the list - **childNodes** with the newnode
insertBefore(newnode, refnode)|Node|add a newnode into the list - **childNodes** before the refnode

