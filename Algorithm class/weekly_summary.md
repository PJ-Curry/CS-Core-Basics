# Algorithm Class 每周复习总结

> 生成时间：2026-05-27 15:02。`.cpp` 文件名已经整理成英文 ASCII，方便编译器识别；代码内容没有改动。

## 每周做了什么

| 周次 | 文件 | 复习重点 |
| --- | --- | --- |
| 第 1 周 | `Bank_Gift_1.cpp`<br>`Stable_Matching_1.cpp`<br>`Ticket_Payment_1.cpp` | 课程基础练习：稳定匹配、简单贪心、数值计算和方案比较。 |
| 第 2 周 | `P1080_Kings_Game_2.cpp`<br>`P2949_Work_Scheduling_2.cpp` | 贪心算法：排序策略、任务调度、优先队列/交换思想。 |
| 第 3 周 | `P1195_Pocket_Sky_3.cpp`<br>`P2504_Clever_Monkey_3.cpp`<br>`P3371_Shortest_Path_Easy_3.cpp`<br>`P4779_Shortest_Path_Standard_3.cpp`<br>`Floyd_3.cpp` | 图论基础：Floyd、Dijkstra、最短路、最小生成树、并查集和连通性。 |
| 第 4 周 | `P1546_Agri_Net_4.cpp`<br>`P1828_Sweet_Butter_4.cpp`<br>`P2820_LAN_4.cpp`<br>`P5767_Optimal_Bus_4.cpp` | 图论应用：最小生成树、最短路建模、交通/网络类问题。 |
| 第 5 周 | `P1616_Crazy_Herb_5.cpp`<br>`P1757_Group_Knapsack_5.cpp`<br>`P1833_Sakura_5.cpp`<br>`P1855_Squeeze_kkksc03_5.cpp`<br>`P2871_Charm_Bracelet_5.cpp` | 背包动态规划：完全背包、分组背包、混合背包、二维费用背包。 |
| 第 6 周 | `P1048_Herb_Gathering_6.cpp`<br>`P1216_Number_Triangles_6.cpp`<br>`P1352_Party_Without_Boss_6.cpp`<br>`P1880_Stone_Merging_6.cpp` | 动态规划进阶：01 背包、数字三角形、树形 DP、区间 DP。 |
| 第 7 周 | `P1129_Matrix_Game_7.cpp`<br>`P1873_EKO_Cutting_Trees_7.cpp`<br>`P3355_Knight_Coexistence_7.cpp`<br>`P3382_Ternary_Search_7.cpp`<br>`P4646_Flood_7.cpp` | 建模与优化：二分图匹配、二分/三分搜索、图建模和网络流前置思路。 |
| 第 8 周 | `P1004_Number_Grid_8.cpp`<br>`P1006_Paper_Pass_8.cpp`<br>`P1086_Peanut_Picking_8.cpp`<br>`P1605_Maze_8.cpp` | 网格类问题：多路径 DP、DFS 回溯、模拟和贪心。 |
| 第 9 周 | `P3376_Max_Flow_9.cpp`<br>`P3381_Min_Cost_Max_Flow_9.cpp` | 网络流模板：最大流、最小费用最大流。 |
| 第 10 周 | `P14578_Lower_Bounded_Feasible_Flow_10.cpp`<br>`P14579_Lower_Bounded_Max_Flow_10.cpp`<br>`P14580_Lower_Bounded_Min_Flow_10.cpp` | 上下界网络流：无源汇可行流、有源汇最大流、有源汇最小流。 |
| 第 11 周 | `P1251_Napkin_Plan_11.cpp`<br>`P2754_Star_Transfer_11.cpp`<br>`P4012_Deep_Sea_Robot_11.cpp`<br>`P4016_Load_Balancing_11.cpp` | 网络流应用：餐巾计划、分层图/时间展开、深海机器人最大收益、负载平衡最小费用。 |

## 洛谷题号对应表

| 周次 | 题号 | 洛谷官方题名 | 本地文件 |
| --- | --- | --- | --- |
| 第 2 周 | [P1080](https://www.luogu.com.cn/problem/P1080) | [NOIP 2012 提高组] 国王游戏 | `P1080_Kings_Game_2.cpp` |
| 第 2 周 | [P2949](https://www.luogu.com.cn/problem/P2949) | [USACO09OPEN] Work Scheduling G | `P2949_Work_Scheduling_2.cpp` |
| 第 3 周 | [P1195](https://www.luogu.com.cn/problem/P1195) | 口袋的天空 | `P1195_Pocket_Sky_3.cpp` |
| 第 3 周 | [P2504](https://www.luogu.com.cn/problem/P2504) | [HAOI2006] 聪明的猴子 | `P2504_Clever_Monkey_3.cpp` |
| 第 3 周 | [P3371](https://www.luogu.com.cn/problem/P3371) | 【模板】单源最短路径（弱化版） | `P3371_Shortest_Path_Easy_3.cpp` |
| 第 3 周 | [P4779](https://www.luogu.com.cn/problem/P4779) | 【模板】单源最短路径（标准版） | `P4779_Shortest_Path_Standard_3.cpp` |
| 第 4 周 | [P1546](https://www.luogu.com.cn/problem/P1546) | [USACO3.1] 最短网络 Agri-Net | `P1546_Agri_Net_4.cpp` |
| 第 4 周 | [P1828](https://www.luogu.com.cn/problem/P1828) | [USACO3.2] 香甜的黄油 Sweet Butter | `P1828_Sweet_Butter_4.cpp` |
| 第 4 周 | [P2820](https://www.luogu.com.cn/problem/P2820) | 局域网 | `P2820_LAN_4.cpp` |
| 第 4 周 | [P5767](https://www.luogu.com.cn/problem/P5767) | [NOI1997] 最优乘车 | `P5767_Optimal_Bus_4.cpp` |
| 第 5 周 | [P1616](https://www.luogu.com.cn/problem/P1616) | 疯狂的采药 | `P1616_Crazy_Herb_5.cpp` |
| 第 5 周 | [P1757](https://www.luogu.com.cn/problem/P1757) | 通天之分组背包 | `P1757_Group_Knapsack_5.cpp` |
| 第 5 周 | [P1833](https://www.luogu.com.cn/problem/P1833) | 樱花 | `P1833_Sakura_5.cpp` |
| 第 5 周 | [P1855](https://www.luogu.com.cn/problem/P1855) | 榨取kkksc03 | `P1855_Squeeze_kkksc03_5.cpp` |
| 第 5 周 | [P2871](https://www.luogu.com.cn/problem/P2871) | [USACO07DEC] Charm Bracelet S | `P2871_Charm_Bracelet_5.cpp` |
| 第 6 周 | [P1048](https://www.luogu.com.cn/problem/P1048) | [NOIP 2005 普及组] 采药 | `P1048_Herb_Gathering_6.cpp` |
| 第 6 周 | [P1216](https://www.luogu.com.cn/problem/P1216) | [IOI 1994 / USACO1.5] 数字三角形 Number Triangles | `P1216_Number_Triangles_6.cpp` |
| 第 6 周 | [P1352](https://www.luogu.com.cn/problem/P1352) | 没有上司的舞会 | `P1352_Party_Without_Boss_6.cpp` |
| 第 6 周 | [P1880](https://www.luogu.com.cn/problem/P1880) | [NOI1995] 石子合并 | `P1880_Stone_Merging_6.cpp` |
| 第 7 周 | [P1129](https://www.luogu.com.cn/problem/P1129) | [ZJOI2007] 矩阵游戏 | `P1129_Matrix_Game_7.cpp` |
| 第 7 周 | [P1873](https://www.luogu.com.cn/problem/P1873) | [COCI 2011/2012 #5] EKO / 砍树 | `P1873_EKO_Cutting_Trees_7.cpp` |
| 第 7 周 | [P3355](https://www.luogu.com.cn/problem/P3355) | 骑士共存问题 | `P3355_Knight_Coexistence_7.cpp` |
| 第 7 周 | [P3382](https://www.luogu.com.cn/problem/P3382) | 三分 | `P3382_Ternary_Search_7.cpp` |
| 第 7 周 | [P4646](https://www.luogu.com.cn/problem/P4646) | [IOI 2007] flood 洪水 | `P4646_Flood_7.cpp` |
| 第 8 周 | [P1004](https://www.luogu.com.cn/problem/P1004) | [NOIP 2000 提高组] 方格取数 | `P1004_Number_Grid_8.cpp` |
| 第 8 周 | [P1006](https://www.luogu.com.cn/problem/P1006) | [NOIP 2008 提高组] 传纸条 | `P1006_Paper_Pass_8.cpp` |
| 第 8 周 | [P1086](https://www.luogu.com.cn/problem/P1086) | [NOIP 2004 普及组] 花生采摘 | `P1086_Peanut_Picking_8.cpp` |
| 第 8 周 | [P1605](https://www.luogu.com.cn/problem/P1605) | 迷宫 | `P1605_Maze_8.cpp` |
| 第 9 周 | [P3376](https://www.luogu.com.cn/problem/P3376) | 【模板】网络最大流 | `P3376_Max_Flow_9.cpp` |
| 第 9 周 | [P3381](https://www.luogu.com.cn/problem/P3381) | 【模板】最小费用最大流 | `P3381_Min_Cost_Max_Flow_9.cpp` |
| 第 10 周 | [P14578](https://www.luogu.com.cn/problem/P14578) | 【模板】无源汇上下界可行流 | `P14578_Lower_Bounded_Feasible_Flow_10.cpp` |
| 第 10 周 | [P14579](https://www.luogu.com.cn/problem/P14579) | 【模板】有源汇上下界最大流 | `P14579_Lower_Bounded_Max_Flow_10.cpp` |
| 第 10 周 | [P14580](https://www.luogu.com.cn/problem/P14580) | 【模板】有源汇上下界最小流 | `P14580_Lower_Bounded_Min_Flow_10.cpp` |
| 第 11 周 | [P1251](https://www.luogu.com.cn/problem/P1251) | 餐巾计划问题 | `P1251_Napkin_Plan_11.cpp` |
| 第 11 周 | [P2754](https://www.luogu.com.cn/problem/P2754) | [CTSC1999] 家园 / 星际转移问题 | `P2754_Star_Transfer_11.cpp` |
| 第 11 周 | [P4012](https://www.luogu.com.cn/problem/P4012) | 深海机器人问题 | `P4012_Deep_Sea_Robot_11.cpp` |
| 第 11 周 | [P4016](https://www.luogu.com.cn/problem/P4016) | 负载平衡问题 | `P4016_Load_Balancing_11.cpp` |

## 非洛谷课程练习

- 第 1 周：`Bank_Gift_1.cpp`
- 第 1 周：`Stable_Matching_1.cpp`
- 第 1 周：`Ticket_Payment_1.cpp`
- 第 3 周：`Floyd_3.cpp`

## 撤销说明

如果想撤销这次英文改名，可以在 PowerShell 中运行：

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\LENOVO\Documents\Codex\2026-05-27\edge-lab11\rollback_english_rename_20260527_150233.ps1"
```

撤销脚本会把文件名恢复到这次改名前的状态，并把这个总结文件移动到一个 `rollback_stash_时间` 文件夹里，不会直接删除。
