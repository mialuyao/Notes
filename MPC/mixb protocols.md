#  方案分类

## 2-party

- **Fairplay**
  -  first work showed **practical feasibility** of MPC by provide an implementation of **Yao's protocol**
- **TASTY**
  - First mixed -protocol framework combine Yao'GC and HE
- **ABY**
  - based on OT
  - Baidu 的**PrivC**对两方算术和姚氏分享协议进行了重新部署

## 3-and 4-and party

- ABY$^3$
- BLAZE（对ABY$^3$的改进）
- ASTRA（对ABY$^3$的改进）
- Trident（4方）
- Sharemind
  - integer arithmetic and boolean operations

上述only allow up to a single corruption, **MOTION** provides full-threshold security



## N-party

- FairplayMP
  - extension of Fairplay
  - Implement the **BMR protocol** with the **setup phase** computed using the honest-majority **BGW** protocol

- SPDZ
  - based on arithmetic sharing in prime fields
- SPDZ$_{2^k}$
  - integer computation modulo $2^k$
- MP-SPDZ
  - Conversion between arithmetic anf boolean sharing



# Motion

## B2A

$\left \langle\mathbf{x}\right \rangle^B \rightarrow \left \langle x \right \rangle^A$

- Straightforward : Additive Masking

  - 随机掩盖值增加到布尔表示的输入值中
  - 结果以算术的方式重构与再分享，同时减去掩盖值

  ​	$r \in _R \mathbb{Z}_{z^l}$的份额对$(\left \langle r \right \rangle^A,\left \langle \mathbf{r} \right \rangle^B )$

  转化过程：$\left \langle \mathbf{t} \right \rangle^B \leftarrow \left \langle \mathbf{x} \right \rangle^B - \left \langle \mathbf{r} \right \rangle^B$	

  ​					$t \leftarrow Rec^B(\left \langle t\right \rangle^B)$

  ​					$\left \langle t \right \rangle^A \leftarrow Share ^A(t)$

  ​					$\left \langle x\right \rangle^A  \leftarrow \left \langle t\right \rangle^A +\left \langle r\right \rangle^A$

  ==通信轮数：至少$\Omega(\log l)+1$==

- Optimized：使用shared bits

  ​		$r \in _R \{0,1\}$的份额对$(\left \langle r \right \rangle^A,\left \langle \mathbf{r} \right \rangle^B )$

  ​	$(\left \langle r_i \right \rangle^A,\left \langle \mathbf{r}_i \right \rangle^B )$，其中$i=0,...l-1$

​			$\left \langle \mathbf{x}\right \rangle^B=(\left \langle x_0\right \rangle^B,...,\left \langle x_{l-1}\right \rangle^B)$，其中$\left \langle x_0\right \rangle^B$是least significant bit

​			for $i=0,...,l-1$

​					$\left \langle t_i\right \rangle^B \leftarrow \left \langle x_i\right \rangle^B \oplus \left \langle r_i\right \rangle^B$

​					$t_i \leftarrow Rec^B(\left \langle t_i\right \rangle^B)$

​					$\left \langle x_i\right \rangle^A \leftarrow t_i+\left \langle r_i\right \rangle^A - 2t_i\left \langle r_i\right \rangle^A$

​					$\left \langle x\right \rangle^A \leftarrow \sum_{i=0}^{l-1}2^i\left \langle x_i\right \rangle^A$

​		==通信轮数：只需要交互一轮在重构$t_i$，需要传递$N(N-1)l$ bits和$l$ Shared bits==

> ​				如何证明正确性？

​	

## B2Y

直接方法：

$\left \langle x \right \rangle_i^Y \leftarrow Share_i^Y(\left \langle x \right \rangle_i^B)$

各方计算 $\left \langle x \right \rangle^Y \leftarrow \oplus _{j=1} ^N \left \langle x_i \right \rangle^Y$

==通信轮数：2轮，总共消耗$N(N-1)(N_k+1)$ bits, $O(N^3k)$==

------

BMR Sharing

$P_i$持有$\left \langle x \right \rangle_i^B, \lambda_w^i, k_{w,0}^i, k_{w,1}^i \oplus R^i$，满足$\lambda_w=\oplus_{j=1}^N \lambda_w^j$

公开 $\alpha_i \leftarrow \left \langle x \right \rangle_i^B \oplus \lambda _w^i$

计算$\alpha \leftarrow \oplus_{j=1}^N \alpha_j$

公开 $k_{w,\alpha}^i$

$\left \langle x\right \rangle ^Y:=(\lambda_w^1,...,\lambda_w^N,(\alpha,k_{w,\alpha}^1,...,k_{w,\alpha}^N))$

其中，$\alpha=\oplus_{j=1}^N \alpha_j=\oplus_{j=1}^N \left \langle x \right \rangle_i^B \oplus \lambda _w^j =x \oplus \lambda_w$



## Y2B

$\left \langle x\right \rangle^Y = (\lambda_x^1,...,\lambda_x^N;(\alpha,k_{x,\alpha}^1,...,k_{x,\alpha}^N))$

$\alpha = x \oplus \lambda_x$

$\left \langle \alpha \oplus x \right \rangle^B = (\lambda_x^1,...,\lambda_x^N)$

各方计算 $\left \langle x \right \rangle^B \leftarrow \left \langle \alpha \oplus x \right \rangle ^B \oplus \alpha$

==通信轮数：本地计算==

## A2Y

$\left \langle x_i \right \rangle^Y \leftarrow Share_i^Y(\left \langle x \right \rangle_i^A)$

$\left \langle x \right \rangle^Y \leftarrow \sum_{j=1}^N \left \langle x_j \right \rangle^Y$

==通信轮数：2轮，总共需要evaluation $N-1$个在BMR中的加法电路，共计$O(lN)$个加法门==

## A2B

A2Y 再Y2B



## Y2A

常规法：Y2B B2A

优化方法：

$\left \langle \mathbf{t} \right \rangle^Y \leftarrow \left \langle \mathbf{x} \right \rangle^Y - \left \langle \mathbf{r} \right \rangle^Y$

$t \leftarrow Rec^Y(\left \langle \mathbf{t} \right \rangle)^Y$

$\left \langle t \right \rangle^A \leftarrow Share^A(t)$

$\left \langle x \right \rangle^A \leftarrow \left \langle t \right \rangle^A + \left \langle r \right \rangle^A$

==通信消耗：在在线阶段无需通信，improve the setup phase by a factor of $O(N)$ in communication at the expense of more communication rounds in the setup phase==







# ABY$^3$

采用了三台服务器结构，将秘密分成三份分别存储在三台服务器上

对于秘密$x,y$

$[[x]]=(x_1,x_2,x_3)$

$[[y]]=(y_1,y_2,y_3)$

对于加法：

- 服务器A：$(x_1,y_1)$

- 服务器B：$(x_2,y_2)$

- 服务器C：$(x_3,y_3)$

  $[[z]]=[[x]]+[[y]]=(x_1+x_2+x_3)+(y_1+y_2+y_3)$

对于乘法：

- 服务器A：$(x_1,y_1,z_1)$, $(x_3,y_3,z_3)$
- 服务器B：$(x_1,y_1,z_1)$, $(x_2,y_2,z_2)$
- 服务器C：$(x_2,y_2,z_2)$, $(x_3,y_3,z_3)$

采用replicated secret sharing来解决密文乘法的问题，如此，各服务器可在本地计算



为了之后进行其他计算，将结果进行一次通信。

任意两台服务器可以重构秘密

安全性方面，考虑了三方计算，只允许至多存在一台服务器腐败。

考虑了两种挑战：

- 浮点数计算精度问题。同乘因子转换为整数，但大量连续的乘法计算导致显著误差；
  - 浮点数转换为定点数，采用布尔电路计算乘法（二进制秘密共享或者混淆电路），从而带来可观的通信开销
- 二进制（二进制秘密共享）和算术计算（算术秘密共享）来回切换的计算瓶颈







