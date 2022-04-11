用$f$表示在域$\mathbb{F}$上的算术电路

门：

- addition $g(a,b)=a+b$
- multiplication $g(a,b)=a*b$

<img src="https://github.com/mialuyao/Notes/blob/main/MPC/circuit.png" alt="image-20220402155231860" style="zoom: 10%;" />

理解为参与者$P_1$的输入为$x$，输出为$y$，中间部分为电路，由各个不同的加法门电路、乘法门电路组成。

输入值使用次数为$t$的随机多项式掩盖。

> Shamir's secret sharing scheme
>
> 分享秘密$s$，采用 $(t,n)$ 门限方案
>
> - 选择一个次数为$t$的多项式，常数项为$s$,$p(x)=s+p_1x+...+p_tx^t$
> - 参与方$P_i$收到$(\alpha_i,p(\alpha_i))$

BGW协议分为三部分

- 输入分享阶段

  - 每一方$P_i$持有输入$x_i$
    - 选择一个次数为$t$的随机多项式$g_i(x)$，满足$g_i(0)=x_i$
    - 每一方$P_j$收到的份额为$g_i(\alpha_j)$
    - 最后每一方$P_i$持有份额为$g_1(\alpha_i),...g_n(\alpha_i)$

- 电路实现

  - 加法门

    - 输入$g_a(x)$,$g_b(x)$；输出$h_{a+b}(x)$

    - 表示为：$f_{add}((g_\alpha(\alpha_1),g_b(\alpha_1)),...(g_\alpha(\alpha_n),g_b(\alpha_n)))=(h_{a+b}(\alpha_1),...,h_{a+b}(\alpha_n))$

    - 计算方式：各方在本地**无需交互**即可计算$g_a(\alpha_i)+g_b(\alpha_i)$（对于两个输入$a,b$，计算方$P_i$可在本地计算出收到的份额之和）

      > 误区：一个门电路有两个输入，一个完整的电路是有多个门电路的，需要对每一个门电路的输出值进行秘密共享，并不是指只有两方参与两方的值输入

  - 乘法门

    - 输入$g_a(x),g_b(x)$；输出$h_{a+b}(x)$

    - 表示为：$f_{mult}((g_a(\alpha_1),g_b(\alpha_1)),...(g_a(\alpha_n),g_b(\alpha_n)))=(h_{a*b}(\alpha_1),...,h_{a*b}(\alpha_n))$
      或者可线性表示为 $ab=\lambda_1 h(\alpha_1)+...+\lambda_n h(\alpha_n)$， 

    - 计算方式：

      - 直接计算存在的问题

        - 多项式的次数增加
        - $h$不是随机的了

      - 对于$ P_i$方

        - 每一方计算$h(\alpha_i)=g_a(\alpha_i)*g_b(\alpha_i)$

        - 使用多项式$H_i(x)$分享$h(\alpha_i)$

          > 即再构造一个多项式$H_i(x)$，使得$H_1(0)=h(\alpha_1)$，多项式$H_i(x)$的次数为$t$

        - 输出$H(x)=\lambda_1 H_1(\alpha_i)+... +\lambda_n H_n(\alpha_i)$

          > 这边可得到$H(0)=\lambda_1H_1(0)+...+\lambda_nH_n(0)=\lambda_1h(\alpha_1)+...+\lambda_nh(\alpha_n)=ab$

        > - 思路
        >
        >   - 首先以矩阵乘法的方式表示出$h$
        >   $$\begin{pmatrix}
        >   1 & \alpha_1 & \alpha_1^2 & \cdots & \alpha_1^{2t} \\\
        >   1 & \alpha_2 & \alpha_1^2 & \cdots & \alpha_2^{2t}\\\ \vdots \\\
        >   1& \alpha_n & \alpha_n^2 & \cdots & \alpha_n^{2t} \\\
        >   \end{pmatrix}\begin{pmatrix}
        >   ab\\\
        >   h_1\\\ \cdots \\\
        >   h_{2t}\\\
        >   \end{pmatrix}=\begin{pmatrix}
        >   h(\alpha_1)\\\
        >   h(\alpha_2)\\\ \cdots \\\
        >   h(\alpha_n)\\\
        >   \end{pmatrix}$$
        >
        >   第一个矩阵的行对应每个参与方构造的多项式的系数
        >
        >   第二个矩阵对应得到的乘法多项式的系数
        >
        >   第三个矩阵为得到的多项式
        >
        >   对此等式进行变换
        >   $$\begin{pmatrix}
        >   ab\\\
        >   h_1\\\ \cdots \\\
        >   h_{2t}\\\
        >   \end{pmatrix}=\begin{pmatrix}
        >   \lambda_1 & \cdots &\lambda_n\\\
        >   \vdots\\\
        >   \cdots \\\
        >   \end{pmatrix}\begin{pmatrix}
        >   h(\alpha_1)\\\
        >   h(\alpha_2)\\\ \vdots\\\
        >   h(\alpha_n)\\\
        >   \end{pmatrix}$$
        >
        >   即左右乘上多项式系数组成的矩阵的逆
        >
        >   这里有一个reminder：对于任意多项式$h(x)$，次数$t<n$，存在常数$\lambda1,...\lambda_n$满足$\lambda_1 *h(\alpha_1)+...+\lambda_n*h(\alpha_n) = h(0)=a*b$

    电路的计算是gate-by-gate的

- 输出重构

  - 每一方$P_i$持有份额$g_{y_1}(\alpha_i),...,g_{y_n}(\alpha_i)$

    - $P_1$可以得到$y_1$
    - $P_2$可以得到$y_2$
    - ...

  - 将$g_{y_j}(\alpha_1),...,g_{y_j}(\alpha_n)$发送给$P_j$，$P_j$重构$y_j$

    > 这边理解为相互发送份额

<img src="https://github.com/mialuyao/Notes/blob/main/MPC/secret-sharing.png" alt="image-20220402164410079" style="zoom: 33%;" />
