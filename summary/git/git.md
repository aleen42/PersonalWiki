## Git 開發流程	[Back](./../summary.md)

<img src="./logo.jpg">

<br />
<br />

### Branch(分支概念)

<img src="./branch.png">

- **master**分支: 存放項目發行(Released)時代碼的分支
- **dev**分支: 從master分支衍生出來的一條用於Debug的分支. (當master分支開發到某個版本後, 基於該分支需要開發另一個版本, 那麼我們會有一條dev分支).
- **Function**分支(**功能名**+**開發人員姓名**):
	- 從dev分支衍生出來, 特定用於開發一個功能.
		- 多個人協同開發: 像黑色分支, 建立屬於自己的開發分支, 而有一個人作為主導開發(如黑色部分中間那條分支).
		- 單個人開發: 只需要一條黑色分支即可
	
<br />
<br />

### Developing Process(開發過程)

- **①**. 新版本**項目負責人**新建一條dev分支
- **②**. 功能開發**主導人**針對一個功能從dev分支新建一條Function分支進行開發. (注: 以**Function_name**命名)
- **③**. 針對開發情況:
	- 單人開發該功能: 只需要該條Function分支即可
	- 多人開發該功能: 需要建立多條Function_xxx分支來開發. (注: 以**Function_name**+**Developer_name**命名, 各開發人員只需要拉屬於自己的分支下來本地進行開發, 並用該分支進行代碼上傳即可)
- **④**. 功能開發完成後, **主導人**把幾個人協同開發的代碼合併到一條分支後, 統一合併到Function分支並進行相應的衝突處理, 然後debug該Function分支.
- **⑤**. 當Function分支可運行並完成功能後, **主導人**提交並合併到dev分支, 進行debug和衝突處理.
	- Function分支的提交格式:
	```
Title:
Description:
		1.
		2.
		3.
Summary:
```

- **⑥**. 迭代②~⑤, 開發多個新功能
- **⑦**. **項目負責人**若測試dev分支正常運行且功能完成, 則可合併dev分支到master分支, 相應進行衝突處理.
	

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
