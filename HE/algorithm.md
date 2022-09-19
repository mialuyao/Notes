# Paillier算法

具有加法同态性

- 密钥生成

  - 随机选择两个质数$p$和$q$满足$\left|p\right|=\left|q\right|=\tau$

  - 计算$N=pq$,$\lambda=lcm\left(p-1,q-1\right)$, lcm表示最小公倍数

  - 随机选择$g\in \mathbb{Z}^*_{N^2}$，满足$gcd(L(g^\lambda modN^2),N)=1$， 下标表示该整数集合里有多少个元素：$L(x)=\frac{x-1}{N}$

  - $pk=(N,g)$

  - $sk=\lambda$

-  加密

  整数$m\in \mathbb{Z}_N$，随机数$r\in \mathbb{Z}_N^*$

  $C=E(m)=g^mr^N mod N^2$

- 解密

  $m=\frac{L(C^\lambda modN^2)}{L(g^\lambda modN^2)}mod N$

- 加法同态

  对明文$m_1,m_2\in\mathbb{Z}_N$

  $E(m_1)=g^{m_1}r^N_1modN^2$

  $E(m_2)=g^{m_2}r^N_2modN^2$

  $E(m_1)E(m_2)=g^{m_1+m_2}(r_1r_2)^N mod N^2=E(m_1+m_2mod N)$







# ElGamal 加密方案

基于离散对数问题的公钥加密方案，加密运算是随机的，即同一明文在相同密钥加密下，所得到的密文是不一样的。

$r$是加密过程中选的一个随机数，$g$是一个生成元，$h$是公钥

密文形式： $c=(c_1,c_2)=(g^r,h^r*m)$

有两个密文：$c_1=(g^{r_1},h^{r_1}*m)$，$c_2=(g^{r_2},h^{r_2}*m)$

相乘可得到：$c=(g^{r_1}*g^{r_2},h^{r_1}*m_1*h^{r_2}*m_2)=(g^{r_1+r_2},h^{r_1+r_2}*m_1*m_2)$

