##ATAM (Architecture Tradeoff Analyse Method, 架構權衡分析法) [Back](./../Architecture.md)
- 評價軟件體系結構初稿是否滿足需求.
- ATAM更多強調質量屬性的評估, 其主要目標是為了識別風險, 分析設計, 明確權衡點並寫入文檔.
- 權衡(Tradeoff): 指多個質量屬性之間的取捨, 從而滿足需求.
- **四個概念**
	- 風險: 潛在問題, 若發生則會降低某些質量屬性的部分.
	- 非風險: 可以提高質量, 幫助實現目標的部分
	- 關鍵點/敏感點: 若改變則產生對質量屬性很大影響的部分.
	- 權衡點: 會影響多餘一個質量屬性的部分.

### 1. Purpose of ATAM
- 1. 引導涉眾發現系統中的權衡點, 風險等信息:
	- helps stakeholders to **ask the right questions** to discover potentially **problematic** architectural decisions.
	- discovered **risks** can be made the focus of mitigation(緩解) activities.
	- **tradeoffs** can be explicitly identified and documented.
- 2. 如果能預知風險, 則可在後期加以注意和控制

### 2. Benefits
- 1. 識別風險
- 2. 澄清質量屬性需求
- 3. 改進文檔
- 4. 記錄結構化設計決定
- 5. 增進溝通

### 3. Phase

<img src="./phases.png">

- Phase0: 前期準備
	- 成立核心的評估小組(包含多方面的角色)
- Phase1: 技术评估(Technical Evaluation)
	- 以技術方面的涉眾為基礎, 對體系結構進行技術性評估
	- 1. Present the ATAM: 讓各方瞭解ATAM的基本內容
	- 2. Present business drivers: 讓客戶描述系統的商業目標
	- 3. Present architecture: 讓Architect展示體系結構的概要, 架構師, 項目經理和市場代表一起描述此系統帶來的價值
	- 4. Identify architectural approaches: 確認體系結構中對實現質量需求產生決定作用的部分
	- 5. Generate quality attribute utility tree: 畫出效用樹來理清質量屬性要求.

	<img src="./utility_tree.png">

## Software Architecture Evaluation Methods
	- SAAM(Software Architecture Analysis Method) Founded on Complex Scenarios(SAAMCS)
		- consider the **complexity** of evaluation scenarios as the most important risk assessment factor.
	- Extending SAAM by Integration in the Domain(ESAAMI)
		- integrates SAAM with **domain-specific** and **reuse-based** software development processes.
	- SAAM for Evolution and Reusability(SAAMER)
		- focus specifically on the quality attributes of **evolution** and **reusability**.
	- Scenario-based Architecture Reengineering(SBAR)
		- utilize scenarios, simulation, mathematical modeling, and experience-based reasoning for assessing quality attributes. And also incorporates an architecture desgin method.
	- Architecture Level Prediction of Software Maintenance(ALPSM)
		- analyse maintainability using scenarios, called **change scenarios**, which represent **maintenance** tasks.
	- Software Architecture Evaluation Model(SAEM)
		- is based on **formal** and **rigorous** quality requirments.


<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
