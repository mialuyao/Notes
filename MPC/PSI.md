# traditional PSI
方法一：paillier homomorphic encryption; polynomial representation of sets
参与方A的集合$S^{(A)}=\{s_1^{(A)},s_2^{(A)},...,s_v^{(A)},\}$， 同时是多项式$\rho(x)$的根
$$
\rho(x) =(x-s_1^{(A)})(x-s_2^{(A)})...(x-s_v^{(A)})=\sum_{i=0}^va_ix^i\\
\forall i, 0\le i \le v
$$
使用公钥加密系数，得到$E_{pk_A}(a_i)$，发送给参与方B

参与方B的集合$S^{(B)}=\{s_1^{(B)},s_2^{(B)},...,s_w^{(B)},\}$，同态加密得到
$$
v_j=E_{pk_A}(r_j*\rho(s_j^{(B)})+s_j^{(B)})\\
\forall j, 1 \le j \le w
$$
其中，$r_j$是随机值，发送给A

如果双方集合中有相同元素，则会以密文的形式体现在结果中， 即若$s_i^{(A)}=s_j^{(B)}$，有
$$
v_j=E_{pk_A}(s_j^{(B)})=E_{pk_A}(s_i^{(A)})
$$
得到的是密文，其余不同的元素，无法得到。

安全性可以结合已知的困难问题进行构造。

最后，A拿出私钥解密，双方即可得到交集部分。

由于只有A的私钥才能揭开加密内容，因此，B无法知道其他数据

由于加入了随机数，因此A即使用私钥对非交集部分进行解密，也无法得出任何有价值的数据。

**==改进1==**

问题：多项式的复杂度与其次数呈线形关系，expensive

改进：在B侧，使用哈希表将A的数据分解成小的子集。

双方首先固定哈希函数。参与方A将每个子集表示成低次数的多项式，并将其加密后发送给B，B进行处理，消耗更小

通信复杂度为$O(v+w)$

A的计算复杂度$O(v+w)$

B的计算复杂度$O(wloglogv)$

**==方法二==**
**kissner2005privacy**

两方环境下，对应集合为$I=\{A,B\}$，使用多项式$\rho^{(I)}$进行加密，并将$E_{pk}(\rho^{(I)})$发送给对方。

收到后，选择一个随机多项式$\gamma^{(I)}$，与之相乘

例如A方计算$E_{pk}(\rho^{(A)} \cdot \gamma^{(B)})$，B方计算$E_{pk}(\rho^{(B)} \cdot \gamma^{(A)})$，再计算同态加
$$
E_{pk}(\rho^{(A)} \cdot \gamma^{(B)}+\rho^{(B)} \cdot \gamma^{(A)})
$$
解密得到$\delta=\rho^{(A)} \cdot \gamma ^{(B)}+\rho^{(B)} \cdot \gamma ^{(A)}$

若$\delta(s_i^{(I)})=0$，则$s_i^{(I)}$即为交集



> 使用ZKP将安全性提高到恶意敌手攻击下



private equality test**DBLP:conf/crypto/NielsenNOB12**：使得双方检查他们的元素是否相等，可以并行处理

**==方法三==**

permutation-based hashing protocol

$e=e_1 ||e_2$ be the bit representation of an element, where $|e_1|=\text{log}_2h$, $h$ is the total number fo bins in a hash table. $h$ be a power of two.

$Q(\cdot)$ 是一个随机函数，输入范围为 $[0,h-1]$

当插入一个元素$e$到哈希表中，计算它的地址为$j=e_1 \oplus Q(e_2)$，储存$e_2$在那个地址。<u>不需要插入整个元素，储存的更短</u>



# delegated PSI

设计的目的在于用户并不信任云

分类

- **只支持one-off PSI delegation**。用户将数据加密后发送给云，云计算交集。每次计算，用户都需要对数据进行再加密，delegation 是one-off的。用户需要在本地保持数据副本（keep a copy of the data），每次都需要先下载下来再重加密。
- **支持repeated PSI delegation。**用户将加密数据外包给云，此操作制作一次。云对加密数据进行计算。用户无需重复上传且在本地保留副本。



用户协商一个私钥$k$，一个keyed 哈希函数$H(\cdot)$，将$m$bits string 映射到$m+l$bits string

用户A 的原集合为$S^{(A)}$，计算$S'^{(A)}=\{H(s_1^{(A)},...,H(s_v^{(A)})\}$

用户B的原集合为$S^{(B)}$，计算
$$
S'^{(B)}=\{s_1^{(B)} \oplus H(s_1^{(B)}),...,s_w^{(B)} \oplus H(s_w^{(B)})\}
$$
将$S'^{(A)}$和$S'^{(B)}$发送给云

云计算集合
$$
S^{(C)}=\{s_1'^{(B)} \oplus s_1'^{(A)},...,s_1'^{(B)} \oplus s_v'^{(A)},...,\\
s_2'^{(B)} \oplus s_1'^{(A)},...,s_2'^{(B)} \oplus s_v'^{(A)},...,s_w'^{(B)} \oplus s_1'^{(A)},...,s_w'^{(B)} \oplus s_v'^{(A)}\}
$$
对于$s_j^{(C)} \in S^{(C)}$，云计算是否前$l$个比特都是0，如果是的话，考虑代表剩余$m$个毕业的值$z_j$是交集中的元素。云将明文发送给用户



### 基于RSA的PSI

同时使用了同态乘法特性

用户首先共同计算RSA参数，$N=pq$，$(b+d)e=f \text{mod}((p-1)(q-1)) $

没有参与方知道$p$和$q$

云获得$e$

用户A获得$b,f$，用户B获得$d,f$

用户A，B分别计算集合，并将其发送给云
$$
S'^{(A)}=\{(s_1^{(A)})^b,...,(s_v^{(A)})^b\}\\
S'^{(B)}=\{(s_1^{(B)})^d,...,(s_v^{(B)})^d\}
$$
云计算一个新的集合
$$
S^{(C)}=\{(s_1'^{(B)} \cdot s_1'^{(A)} )^e,...,(s_1'^{(B)} \cdot s_v'^{(A)} )^e,...,\\(s_2'^{(B)} \cdot s_1'^{(A)} )^e,...,(s_2'^{(B)} \cdot s_v'^{(A)} )^e,...,(s_w'^{(B)} \cdot s_1'^{(A)} )^e,...,(s_w'^{(B)} \cdot s_v'^{(A)} )^e\}
$$
如果$s_1^{(A)}=s_2^{(B)}$，则有$s_1^{(C)}=(s_1^{(A)})^{e(b+d)}$

A找到交集，有$S^{"(A)}=\{(s_1^{(A)})^f,...,(s_v^{(A)})^f\}$，对比$S^{(C)}$中的元素

A与云对$S^{"(A)},S^{(C)}$进行传统交互式PSI，同理B

缺点 ：每次都需要进行参数对选择，并且需要再加密元素。如果一开始A和B计算，之后A和C计算，则云会计算B和C是否有相同元素



### 结合bloom filters

可信方产生公钥和私钥参数，分发给其他方

用户A产生bloom filter，并插入集合元素。加密bloom filter的每个bit，并发送给云。

用户B构造w个bloom filters $BF^{(B)}_j$，将每个集合元素插入$s_j^{(B)}$插入到对应的bloom filter。



### 几种特性

**多用户下载云计算的部分结果**

结合pseudorandom permutations（PRP）

用户们实现下协商一个私钥$k$和PRP$f_k(\cdot)$，每一方$I$持有的集合为$S^{(I)}$，计算得到$S'^{(I)}=\{f_k(s_1^{(I)},...,f_k(s_v^{(I)}\}$，并将其发送给云。

由于所有参与方使用的都是相同的密钥，因此云可以在外包集合中发现相同元素，并将其返回给用户。



 **检查云是否提供了错误的结果**

**Find a witness**



## repeated PSI delegation

只需要将加密的数据外包给云一次，用户无需保留本地副本，或者下载重加密

**liu2014encrypted**

基于hash和公私钥加密

每个用户$I,I \in \{A,B\}$，首先产生三个向量：
$$
\vec{\mathbf{t}}^{(I)}=[P_{sk}(s_1^{(I)}),...,P_{sk}(s_w^{(I)})], \\
\vec{\mathbf{e}}^{(I)}=[h(s_1^{(I)})+r_1^{(I)},...,h(s_w^{(I)})+r_w^{(I)}],\\\
\vec{\mathbf{d}}^{(I)}=[P_{sk}(r_1^{(I)}),...,P_{sk}(r_w^{(I)})], \\
$$
其中，$r_i^{(I)}$随机选择，用户将这三个向量外包给云。

当用户A需要计算与B的交集时

- 下载整个向量$\vec{d}^{(A)}$，解密得到$r_i^{(A)}$

- 选择单个随机值$b$，$g_i^{(A)}=b+r_i^{(A)}$

- 将$\vec{\mathbf{g}}^{(A)}=[g_1^{(A)},...,g_w^{(A)}]$和$E_{pk_B}(b)$发送给云

- 云将$\vec{\mathbf{d}}^{(B)}$和$E_{pk_B}(b)$发送给用户B

- 用户B解密，计算$\vec{\mathbf{g}}^{(B)}=[g_1^{(B)},...,g_w^{(B)}]$，$g_i^{(B)}=b+r_i^{(B)}$，并将$\vec{\mathbf{g}}^{(B)}$发送给云

- 根据$\vec{\mathbf{g}}^{(A)}$和$\vec{\mathbf{g}}^{(B)}$，计算
  $$
  \vec{\mathbf{g}}^{(C_1)}=[e_1^{(A)}+g_1^{(B)},...,e_1^{(A)}+g_w^{(B)},...,e_w^{(A)}+g_1^{(B)},...,e_w^{(A)}+g_w^{(B)}] \\
  \vec{\mathbf{g}}^{(C_2)}=[e_1^{(B)}+g_1^{(A)},...,e_1^{(B)}+g_w^{(A)},...,e_w^{(B)}+g_1^{(A)},...,e_w^{(B)}+g_w^{(A)}]
  $$
  

- 计算得到$\vec{\mathbf{g}}^{(C_3)}, g_i^{(C_3)}=P_{sk}(s_i^{(A)})$当且仅当$|g_i^{(C_1)}-g_i^{(C_2)}|=0$，将其发送给A即可解密。

$\rightarrow$产生的几个问题：

1. 每次计算都需要授权，每个用户都需要下载加密向量，等价于先上传后下载
2. $b$是 one-time pad的
3. 先计算AB之间的，再计算BC之间的，云可能计算出AC之间的==！！设计算法时需要注意这种问题的存在，需要给出足够的安全性证明==

