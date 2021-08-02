## How to analyse an algorithm	[Back](./../AlgorithmnMenu.md)

### 1. Overview

Main **thoughts** of designing algorithms:

- [**DC**](./DC/DC.md)
- [**DP**](./DP/DP.md)
- [**Greedy**](./Greedy/Greedy.md)
- [**Search**](./Search/Search.md)
- [**Random**](./Random/Random.md)


```math:fontSize=16
\begin{darray}{cc}
    DC(Device\ and\ Conquer)\implies DP(Dynamic\ Programming) \implies & Greedy \\
    & \Darr  \\
    & Search \\
    & \Darr  \\
    & Random \\
\end{darray}
```

Sometimes, the **performance** of an algorithm matters so much, when the size of a problem **n** is so big.

<p align="center"><img src="./overhead.png" width="650px" /></p>

It is not always true for high performance, when an algorithm depends on what is more important like the following items:

- modularity(模塊性)
- correctness(正確性)
- maintainability(可維護性)
- functionality(功能性)
- robustness(健壯性)
- user-friendliness(用戶友好性)
- programmer time(編程效率)
- simplicity(簡潔度)
- extensibility(可擴展性)
- reliability(可靠度)

There are **three** kinds of analysis:

- Worst-case(考慮該類問題的最優解, 關注最壞情況下的最好情況)
- Average-case
- Best-case(虛假的)

There are **three** notations of **time**

- ***θ*** (drop **low-order** terms, and ignore **leading** constants)

```math:fontSize=16
T(n)=\theta(g(n))\Longleftrightarrow c_1g(n)\le T(n)\le c_2g(n)
```

```math:fontSize=16
\begin{split}
T(n) &= 3n^3 + 90n^2 - 5n + 6046 \\
     &= 3n^3 + 90n^2 - 5n + \theta(1) \\
     &= 3n^3 + 90n^2 - \theta(n) \\
     &= 3n^3 + \theta(n^2) \\
     &= \theta(n^3)
\end{split}
```

- ***Ω***

```math:fontSize=16
T(n)=\Omega(g(n))\Longleftrightarrow T(n)\ge c_1g(n)
```

- ***O***

```math:fontSize=16
T(n)=O(g(n))\Longleftrightarrow T(n)\le c_2g(n)
```

### 2. Recursive Algorithm

- Substitution: 猜想 (通常通過畫Recursive Tree來給出猜想) 並證明
	- guess
	- verify

        ```math:fontSize=16
        \begin{split}
        eg1.\ T(n) = T(⌈n / 2⌉) + 1 &\Longrightarrow T(n) = O(lgn) \\
        to\ verify\ T(n) &\le clgn \\
        assume\ that\ T(⌈n / 2⌉) &\le clg(⌈n / 2⌉) \\
        then\ T(n) &\le clg(⌈n / 2⌉) + 1 \\
        &\lt clg(n / 2 + 1) + 1 \\
        &= clg(n + 2) - clg2 + 1 \\
        &= clg(n + 2) - c + 1 \\
        cause\ there\ is\ a\ low\ ordered\ term\ 2 \\
        then\ to\ verify\ T(n) &\le clg(n - b) \\
        assume\ that\ T(⌈n / 2⌉) &\le clg(⌈n / 2⌉ - b) \\
        then\ T(n) &\le clg(⌈n / 2⌉ - b) + 1 \\
        &\lt clg(n/2 + 1 - b) + 1 \\
        &= clg(n + 2 - 2b) - clg2 + 1 \\
        &= clg(n + 2 - 2b) - c + 1 \\
        &\le clg(n - b) \\
        then \begin{cases}
          n + 2 - 2b \le n - b \\
          -c + 1 \le 0
        \end{cases} &\Longrightarrow \begin{cases}
          b \ge 2 \\
          c \le 1
        \end{cases} \\
        then\ T(n) \le clg(n - b）&\le clgn \\
        then\ T(n) &= O(lgn) 
        \end{split}    
        ```

		```math:fontSize=16
        \begin{split}
        eg2.\ T(n) = 3T(⌊n / 2⌋) + n &\Longrightarrow T(n) = O(n ^ {lg3}) \\
        to\ verify\ T(n) &\le cn ^ {lg3} \\
        assume\ that\ T(⌊n / 2⌋) &\le c(⌊n / 2⌋) ^ {lg3} \\
        then\ T(n) &\le 3c(⌊n / 2⌋) ^ {lg3} + n \\
        &\le 3c(n / 2) ^ {lg3} + n \\
        &= cn ^ {lg3} + n \\
        cause\ there\ is\ a\ low\ ordered\ term\ n \\
        then\ to\ verify\ T(n) &\le c(n ^ {lg3} - n) \\
        assume\ that\ T(⌊n / 2⌋) &\le c(⌊n / 2⌋) ^ {lg3} - c(⌊n / 2⌋) \\
        then\ T(n) &\le 3c(⌊n / 2⌋) ^ {lg3} - 3c(⌊n / 2⌋) + n \\
        &\le 3c(n / 2) ^ {lg3} - 3c(n / 2) + n \\
        &= cn ^ {lg3} - \frac 3 2 cn + n \\
        &\le cn ^ {lg3} - cn \\
        then\ - \frac 3 2 cn + n \le -cn &\Longrightarrow c \ge 2 \\
        then\ T(n) \le cn ^ {lg3} - cn &\le cn ^ {lg3} \\  
        then\ T(n) &= O(n ^ {lg3})
        \end{split}
        ```

	- solve
- Recursive Tree: 通過畫出遞歸樹來求解開銷

<img src="./recursive_tree.png" width="80%">

```math:fontSize=16
T(n) = f(n) + af(n / b) + a ^ 2 f(n / b ^ 2) + ... + a ^ {log_bn-1} f(n / b ^ {log_bn - 1}) + O(n ^ {log_ba})
```

- Master:

    ```math:fontSize=16
    T(n) = aT(n / b) + f(n)  
    ```

    ```math:fontSize=16
    T(n) = \theta(n ^ {log_ba}),\ if\ f(n) = O(n ^ {log_ba - \varepsilon}),\ \varepsilon > 0
    ```

    ```math:fontSize=16
    T(n) = \theta(n ^ {log_ba}lg ^ {k + 1}n),\ if\ f(n) = O(n ^ {log_ba}lg ^ k n)
    ```

    ```math:fontSize=16
    T(n) = \theta(f(n)),\ if\ f(n) = O(n ^ {log_ba + \varepsilon}),\ \varepsilon > 0\ and\ af(n / b) \le cf(n),\ c \lt 1
    ```
