##Assembly Language (彙編語言)	[Back](./../Embedded_System.md)

- 這裡著重討論ARM處理器彙編指令集

### 1. Overview

Code|Description
----|-----------
MOV R0, #15| 立即數15放入寄存器R0 
MOV R0, R1, R2| R0 <= R1 + R2
LDR R0, [R4]| 從R4取出地址然後在那個地址上取出數據放入R0, R0 <= [R4]
ADD R0, R1, R2, LSL #1| R2左移一位後與R1相加並放入R0
LDR R0, [R1, #4]| R0 <= [R1 + 4]
LDR R0, [R1, #4]!| R0 <= [R1 + 4], R1 <= R1 + 4
LDR R0, [R1], #4| R0 <= [R1], R1 <= R1 + 4
LDR R0, [R1, R2]| R0 <= [R1 + R2]
BL proc| 跳轉到子程序proc執行, 執行完返回(L標誌: 帶返回的跳轉)
STMFD R13! {R0 - R4}| 把R0到R4壓入到頭指針為R13的堆棧中, FD標誌滿棧遞減, 即每次壓入地址減少
LDMFD R13!, {R0 - R4} | 把R0到R4彈出棧

### 2. Shift

Code|Description
----|-----------
MOV R0, R1, LSL #1| R1左移一位並放入R0
MOVS R0, R1, LSL #1| R1左移一位並放入R0後, 更新狀態標誌位
MOVS R0, R1, LSR #1| R1右移一位並放入R0後, 更新狀態標誌位
MOVS R0, R1, ASR #1| R1算術右移一位並放入R0後, 更新狀態標誌位
MOVS R0, R1, ROR #1| R1循環右移一位並放入R0後, 更新狀態標誌位
MOVS R0, R1, RRX| R1循環右移一位並放入R0後, 更新狀態標誌位

### 3. Arithmetic

Code|Description
----|-----------
ADDS R0, R2, R4| (64位相加) R2加上R4後, 把低32位放入R0.
ADC R1, R3, R5| (64位相加) R3加上R5後, 把高32位放入R1, 且加上低位的進位
SUBS R0, R2, R4| (64位相減) R2減去R4後, 把低32位放入R0.
SBC R1, R3, R5| (64位相加) R3減去R5後, 把高32位放入R1, 且減去低位的借位
RSB R0, R1, R2| R2減去R1後, 值放入R0
RSB R0, R1, #6| 6減去R1後, 值放入R0
RSC R0, R1, R2| R2減去R1再減去借位後, 值放入R0

### 4. Logic

Code|Description
----|-----------
AND R0, R0, #0xF| R0與0xF相與後放入R0
ORR R0, R0, #9| R0與9相或後放入R0
EOR R0, R0, #0xF| R0與0xF相異或後放入R0
BIC R0, R0, #9| R0第0位和第3位清零後放入R0

### 5. Compare

Code|Description
----|-----------
CMP R1, #10| R1減去10後影響CPSR標誌位
ADDGT R0, R0, #5| 若R1>10, 則R0加上5
CMN R0, R1| R0-(-R1), 影響CPSR標誌位
CMN R0, #10| R0-(-10), 影響CPSR標誌位
TST R1, #3| 檢查第0位和第1位是否為1, 影響條件標誌位
TEQ R1, R2| R1與R2按位異或, 影響CPSR標誌位

### 6. Multiply

Code|Description
----|-----------
MUL R0, R1, R2| R1乘以R2後, 值放入R0
MULS R0, R1, R2| R1乘以R2後, 值放入R0並更新狀態標誌位
MLA R0, R1, R2, R3| R1乘以R2再加上R3後, 值放入R0
MLAS R0, R1, R2, R3| R1乘以R2再加上R3後, 值放入R0並更新狀態標誌位
