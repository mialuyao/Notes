其核心思想是发送方不知道接收方接受了哪条消息，接收方除了接收到的消息外无法获得其他消息。

具体算法的构造需要**结合其他密码学知识**，比如基于什么底层困难问题，双方需要生成的内容就不一样。

### $OT_1^2$

<u>**基于离散对数问题**</u>

Alice有$v_0,v_1$和密钥$s,r_0,r_1$;

Bob有$i \in \{0,1\}$和密钥$k$，想要获得$v_i$;

Alice和Bob事先统一$g \in \mathbb{Z}_p$，其中$g$是大整数，$p$是大素数。

**具体过程：**

1. Alice$\rightarrow$ Bob: $g^s$

   > 由于离散对数问题的存在，Bob即使知道$g,g^s$也无法破解$s$。

2. Bob基于$i$生成 $L_i= \begin{cases} g^k & \text{if  } i=0 \\ g^{s-k} &\text {if } i=1\end{cases}$

3. Bob $\rightarrow$ Alice:$L_i$

   > 由于离散对数问题的存在，Alice即使知道$g,g^k$也无法破解$k$,从而无法判断Bob发来的是$g^k$还是$g^{s-k}$，也就无法知道$i$。

4. Alice生成$C_0,C_1$

   1. $C_0=(g^{r_0},(L_i)^{r_0} \oplus v_0)$ ,$\oplus$表示 bitwise XOR
   2. $C_1=(g^{r_1},(g^s/L_i)^{r_1} \oplus v_1)$

5. Alice $\rightarrow$ Bob: $C_0,C_1$

   > 由于离散对数问题的存在，Bob即使知道$g,g^{r_0},g^{r_1}$也无法破解$r_0,r_1$。

6. Bob解密$v_i$

   1. $i=0$

      1. Bob解密获得$v_0$

         $C_0[0]^k \oplus C_0[1] = (g^{r_0})^k \oplus (L_i)^{r_0} \oplus v_0=  (g^{r_0})^k \oplus (g^k)^{{r_0}}  \oplus v_0 =v_0$

      2. Bob无法获得$v_1$

         因为$C_1[1]=(g^s/L_i)^{r_1} \oplus v_1=g^{(s-k)r_1} \oplus v_1$，Bob不知道$s,r_1$

   2. $i=1$

      1. Bob解密获得$v_1$

         $C_1[0]^k \oplus C_1[1] = (g^{r_1})^k \oplus (L_i)^{r_1} \oplus v_1=  (g^{r_1})^k \oplus (g^k)^{{r_1}}  \oplus v_1 =v_1$

      2. Bob无法获得$v_0$

         因为$C_0[1]=(g^s/L_i)^{r_0} \oplus v_0=g^{(s-k)r_0} \oplus v_0$，Bob不知道$s,r_0$

      3. 从而Bob只能解密$v_i$不能解密$v_{i-1}$

**<u>基于大整数困难问题</u>**

基于RSA的OT

|                              | Alice                                                        |               | Bob                       |                                    |
| ---------------------------- | ------------------------------------------------------------ | ------------- | ------------------------- | ---------------------------------- |
| 待发送消息$m_0,m_1$          |                                                              |               |                           |                                    |
| 产生RSA密钥对，发送公钥给Bob | d                                                            |               |                           |                                    |
| 产生RSA密钥对，发送公钥给Bob | N，e                                                         | $\rightarrow$ | N，e                      |                                    |
| 产生随机字符串               | $x_0,x_1$                                                    | $\rightarrow$ | $x_0,x_1$                 |                                    |
|                              |                                                              |               | $k,b$                     | 选择$b \in {0,1}$，产生随机比特$k$ |
|                              | $v$                                                          | $\leftarrow$  | $v=(x_b+k^e)\text{mod} N$ |                                    |
|                              | $k_0 = (v-x_0)^d \text{mod} N $<br />$k_1 = (v-x_1)^d \text{mod} N$ |               |                           |                                    |
|                              | $m_0'=m_0+k_0$<br />$m_1'=m_1+k_1$                           | $\rightarrow$ |                           |                                    |
|                              |                                                              |               | $m_b=m_b'-k$              |                                    |



