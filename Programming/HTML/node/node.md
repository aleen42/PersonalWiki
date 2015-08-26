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

Properties/Methods|Types/Returned types|Descriptions
------------------|--------------------|------------
nodeName|String|the name of the node
nodeValue|String|the value of the node
nodeType|Number|the type of the node
ownerDocument|Document|the owner document of the node
firstChild|Node|the first node in the childNodes
lastChild|Node|the last node in the childNodes

<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
