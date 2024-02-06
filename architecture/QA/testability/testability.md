## Testability	[Back](./../QA.md)
- Testability(可測試性)衡量一個系統是否容易測試出bug.


##Scenarios(場景)

<img src="./scenario_list.png">

- example:

<img src="./testability_scenario.png">



##Tatics(策略)

<img src="./testability_tactics.png">

### 1. Manage Input/Output
- Record/Playback: 記錄下測試結果/重建測試的過程 (半自動化/自動化測試)
- Separate interface from implementation: 通過對接口分離, 從而對統一接口測試不同的實現代碼
- Specialize access routes/interfaces: 提供專門的方法或接口用於測試(如查看數據庫中的表)

### 2. Internal Monitoring
- Built-in Monitors: 在IDE中設置斷點
