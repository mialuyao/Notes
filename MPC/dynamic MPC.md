# Evolving Homomorphic Secret Sharing for Hierarchical Access Structures

通常情况下，分享方的数量$n$和访问结构是提前知道的。

但在很多场景下这些假设是打折扣的，比如：

- 最终的集合往往小于$n$
- 访问结构会随着时间变化，迫使reshare

在现实环境下，希望系统是可以evolving

evolving secret sharing 是可行的一种方案，但是不支持对shares的计算。

同态secret sharing允许对shares进行计算，并且通信量小，但是不具有evolving



$\Rightarrow$ **main idea**

- 给出了evolving homomorphic SS的概念，满足上述两种条件。
- 给出了两种方案
  - Hierarchical access structure$\rightarrow$支持乘法
  - Partially hierarchical access structure$\rightarrow$支持低次多项式的计算



$\Rightarrow$ **Details**

- evloving：可以增加服务器的数量但是不需要再次分享
- homomorphic：服务器间无需通信即可对份额进行计算
- hierarchical access structure：门限值可以根据不同数量的服务器进行改变。当新的服务器增加时可以调整安全级别。

- 使用哈希函数将服务器的ID映射到有限域上（从而支持了无限数量的服务器）
- 使用integrals
- 方案1
  - 使用伪随机函数来保持在不同素数域上份额的一致性
  - 每个服务器可以得到2-3个值而不是一个。
- 方案2
  - 协议分为两个阶段
    - setup阶段
      - 在秘密输入前，随机值提前分布
    - Online阶段
      - 第t方加入协议会得到一个大小为$O(\log{t})$的分享	



$\Rightarrow$ **提出的方案**

Hierarchical  access structure视为几个门限结构的离散状态，$(k_1,|P_1|)$-threshold, $(k_2,|P_1 \cup P_2|)$-threshold, $(k_l,|\cup^l_{m=1} P_m|)$-threshold

**方案1: 基于hierarchical secret sharing的方案**

Evolving disjunctive hierarchical access structure 增加了一条：$|A \cap \bigcup^j_{m=1}P_m|>k_j$新增加的部分与原来服务器的交集大于门限值

- 第t个计算方的随机身份为$ID_t$
- 第$i$个用户输入$x_1$，分享给$P_1$中的服务器，产生次数为$k_1$的多项式$P_{i,1}(\chi)=\sum_{j=1}^{k_1}a_j\chi^j$,$a_j$为随机系数，$a_{k_i}=x_i$
  - 当$P_1$中的第$t$个服务器到达，获得shares为$s_{i,t}=P_{i,1}(h(ID_t))$

- $P_m$中的第一个服务器到达，输入的用户生成次数为$k_m$ 的多项式；对于$t\in P_m$，当t个计算完成，得到分享为$s_{i,t}=P_{i,m}(h(ID))$

Reconstruction



**方案2：Multi-generation of Shamir's Scheme**

结合Shamir's SS和伪随机函数，允许计算服务器存储不止一个份额

对于所有服务器，$1 \le j \le k_1$表示第一代；$k_{m-1}<j\le k_m$表示第m代

- 当第一个服务器到来，第$i$个输入的用户产生次数为$k_0$的多项式$P_{i,1}$， $p_1>k_2$，$P_{i,1}(0)=x_i$
- 对于$1\le t \le k_2$，分享$s_{i,t}$包括$P_{i,1}(t)$和随机比特串$r_{i,t}$，在第1和第2轮的时候给到第$t$个服务器
- 对于$j \ge 2$， 当第$k_{j-1}+1$个服务器到来，输入的用户同意计算伪随机函数。产生一个次数为$k_{j-1}$的多项式$P_{i,j}$，其中$P_{i,j}(0)=x_i$
- 对于$j \ge 2$和$k_{j-1}+1 \le t \le k_{j+1}$，分享$s_{i,t}$包括$P_{i,j}(t)$和随机比特串$r_{i,t}$给到第$j$层和第$j+1$层服务器。

多项式$P_{i,j}$可以从之前的$j-1$代的伪随机值产生





假设有$n$个输入的用户。

计算方一开始假设有$m_1$个，后来增加到了$m_2$，$m_3,...,m_l$个。

> 原方案
>
> 共有$nm_1$个消息从$n$个输入的用户发送到$m_1$个服务器中
>
> 服务器间的**重分享**是有必要的，$m_im_{i+1}$个消息从第$i$个服务器集合发送到$i+1$个服务器集合。
>
> 发送的总消息数为$nm_1+m_1m_2+...+m_{l-1}m_l$
>

**本方案**

不需要重分享，份额只从输入的用户发送到了新增加到服务器。

只需要通信量为$nm_1+n(m_2-m_1)+...+n(m_l-m_{l-1})=nm_l$

并且已经收到份额的服务器不需要在线。



$\Rightarrow$ **future work**

- first scheme

1. 每个服务器的份额很小，但是share size很大，由于素数$p$很大。

如果可以提供素数域的大小，share siza可以减小。

可以将多项式积分到不同的素数域，使用多变量的中国剩余定理而不是线性系统。

2. 任意$d$个集合无法包括所有方，但$d$个输入时的乘法性。

使用预计算的乘法三元组来解决不受次数多乘法。

这需要服务器间的一些交互。

- Second scheme

门限值的选取





> **DBLP:conf/tcc/KomargodskiNY16**首先提出参与方集合不是提前知道的，并且可能是无限的。
>
> 特别的，参与方是一个一个到达的，无论何时一个参与方到达，和已经到达的参与方间没有通信（分发秘密的人只需要发一个share给新加入的一方）。
>



> evolving access structure的定义
>
> 发布者一开始知道可够，但是没有参与方数量的上线。数量的改变是单调的（monotone），也就是说，参与方只能增加，合格的集合依旧是合格的。
>
> 对evolving access structure的研究的目的是减小第$t$个的share size
>

------





# Fluid MPC

**原方案中：全部的参与方都需要全程参与协议的执行**

**本文提出的方案： dynamic participation model用户具有离线和重新加入的灵活性**

------

static MPC的问题：对于大型、长时间的计算任务，要求参与方参与整个过程可能不合理，因为参与者的计算资源或他们可以一次性投入计算的时间可能有限；现实情况是，一些参与方会离线或者去执行其他任务。

$\Rightarrow$ fluid MPC：支持动态参与，即参与方加入、离开计算不会影响协议的执行，

具体地：

- 不再需要参与方全程参与
- 允许参与方在协议执行中参与

由于计算方不再需要大量的计算资源，因此计算方的资源消耗很低，从而可以产生一个轻量级隐私保护分布式计算系统。

------

**Motivation:**

- 获得最大流动性
- 服务器每个epoch的计算独立于函数/电路的尺寸

------

模型选择中的问题：

- 特定epoch中，服务器的身份何时如何固定

- 系统的流失率的要求（高流失率意味着无论参与方的计算能力和可利用性如何，都可以参与协议，参与方之间的相关性小）
- 攻击者的腐败模型和协议参与者的动态交互是什么样的？

------

在应用方面

- fluid MPC更适用于涉及到需要较深的电路需要长时间计算的场景。在这种场景下，暂时地罗列出动态计算资源有利于隐私保护计算，这些计算资源可能无法进行static计算。

- 在资源受限的计算下更灵活。

------

具体地贡献为：

- 提供了fluid MPC的formal treatment，探索不同可能的模型选择；

- 构造了在大多数诚实环境下的information-theoretic fluid MPC协议，获得了maximal fluidity；

  > maximal fluidity指每一轮一方可以收到或者发送消息后离开

  - 首先将经典的半诚实协议BGW以一种简单的方式转换成了Fluid-BGW，协议获得了工作的分工，意味着每个协议需要的工作独立于电路的深度。
  - 为了获得恶意敌手写的安全性，拓展additive attack到fluid MPC环境下。对半诚实协议的任意恶意敌手策略无法再爱电路的中间导线上注入加法值。
    - 使用此构造了一个高效的compiler，将半诚实fluid-MPC转化到恶意敌手攻击可终止的安全性。两个主要的特性是
      - 保留了底层半诚实协议的流动性
      - 在底层协议的通信复杂性只有2的乘法开销（对于在大的域上的电路）

- 在多网络环境下进行了测试；

------

**未来的研究方向**：

- 效率方面

  - 本文构造了一个恶意安全的编译器，保留了底层半诚实协议的流动性，只需要很小的常数乘法消耗。**未来针对具体高效的流动MPC协议的设计只需要关注半诚实安全**。

  - 本文的半诚实流动MPC协议基于经典的BGW协议，但是这些协议使用摊销技术（amortization techniques），内在的需要各方去保留较大的隐私状态（与电路规模成比例）。**未来需要设计适用于大规模计算的更高效的半诚实流动MPC协议**。

- 安全方面

  - 本文考虑了大多数诚实模型，敌手只能腐化一个协议中的少数服务器。**未来研究方案为设计的协议更具有挑战性，敌手可腐化一半服务器或者全部服务器**。
  - 本文考虑以终止的方式获得安全性。但终止是毁灭性的（在具体场景下不实用）。**未来研究方向为保证输出交付。**

------

**proactive security model：**

模型化分布式计算中的持续攻击、参与方间的不断腐坏和恢复

$\rightarrow$ Mobile adversary:

-  不受腐化总数的限制；
-  在不同阶段可以腐化部分用户；
-  参与方定期重启到干净状态以减少损坏的数量

从不同角度考虑动态模型，motivation是不一样的

1. proactive MPC(PMPC)
   - 考虑slow-moving 攻击者，以计算机病毒🦠为模型，参与者被固定在协议的某个阶段
2. fluid MPC: 
   - 动态性来源于参与者离开和加入协议
   - 获得最大流动性的同时减小每个epoch的计算复杂性
   - 还有一个volunteer servers的概念，计算与可用资源成正比
   - 参与方的隐私状态大小也是关键点

------

**Transferable-MPC**

参与方计算输入的部分输出，将这些份额转移给其他方来继续计算以保持隐私性

 $\rightarrow$ 每部分计算需要涉及到多轮交互，无法满足fluidity,成员无法实现动态流动

------

2篇在区块链方向的文章考虑了动态计算环境，使用秘密共享

DBLP:conf/tcc/BenhamoudaG0HK020

DBLP:conf/pkc/GoyalKMPS22：协议在每个epoch的hand-off阶段公布

------

本文考虑**client-server 模型**

模型分为三个阶段：input-execution-output

用户以隐私保护的方式分享输入给初始协议的服务器，一旦计算开始，用户和初始服务器就推出执行协议。

其余服务器，即使在input阶段没有出现，可以在协议执行阶段通过注册以执行协议的一部分加入。

- **input stage**

- **execution stage**

  - Divide into a sequence of epochs

    每个epoch，一个协议的服务器负责做一部分计算，之后将状态转移到新的协议（**本文，每个epoch只需要一轮通信，只用来传递状态**）

    - **computation phase** 服务器执行计算，
      - intepolate the shares-of-shares to obtain a degree t sharing of full intermediary state
      - 本地evaluate each gate
      - compute a t-out-of-n SS
    - **hand-off phase** 在$S^l$中的服务器将状态(one share)转移到下一个协议$S^{l+1}$中的服务器

- **output stage**

![截屏2021-12-18 下午4.06.09](/Users/wangluyao/Library/Application Support/typora-user-images/截屏2021-12-18 下午4.06.09.png)

每个epoch分为2个阶段：

- computation phase：执行$S^l$协议
- hand-off：将$S^l$的状态转移到$S^{l+1}$（在epoch$l$ Hand-off的开始阶段，每个人都意识到协议$S^{l+1}$

fluidity是指单个epoch中通信轮数

maximal fluidity是指单个epoch只通信一轮（即computation phase阶段不通信，hand-off阶段通信）

考虑攻击者只能腐败每个协议中的一小部分服务器，那么状态就无法以一种一对一的方式传递。

原因：$t$-out-of $n$秘密共享，协议$S^i$中的每一个服务器传递状态给协议$S^{i+1}$中的制定一个服务器，伪造者将看到$2t$个转移状态的分享值，$t$个从$S^i$，t个从$

------

**主要的挑战**

- **fluidity**

  指协议在每个epoch交互的轮数，最大流动性即每个epoch只交互一次，那么就需要computation 阶段是没有交互的，hand-off阶段完成一轮交互。

- **small state complexity  更小的状态复杂度**

  > 协议的状态复杂性是指每一方的private state很大，通常与电路尺寸成比例。

  在fluid MPC中，两个epoch间需要转移状态，协议的状态复杂性与通信复杂性相关，若与电路大小成正比，则无法在fludity上取得优势。

- **secure state transfer 更安全的状态转移**

  $t$-out-of $n$秘密共享，协议$S^i$中的每一个服务器传递状态给协议$S^{i+1}$中的制定一个服务器，伪造者将看到$2t$个转移状态的分享值，$t$个从$S^i$，t个从$S^{i+1}$

方案的设计就是在这三者进行平衡

------

**将半诚实BGW优化成fluid MPC**

在BGW方案中

- 加法门：本地计算
- 乘法门
  - 在本地对份额进行乘法，得到次数为$2t$的多项式
  - 对次数为$2t$的多项式进行$t$-out-of-$n$分享，即得到了share-of-share（此处需要1轮的通信）

优化的关键点在于次数的约减过程同时重新随机化了状态，因此只需要一轮通信即可完成两个目标。

在每个epoch中，服务器在每一层运行所有门。具体地，在每个epoch：

- computation phase：

  - 在$S^l$状态的服务器对前一个协议收到的份额（share-of-share）进行差值，得到梯度为$t$的分享作为中间状态
  - 本地运行在$l$层的每一个门
  - 计算整个状态持有的$t$-out-of $n$分享

- hand-off phase:

  - 在$S^l$的服务器发送每个分享的一个份额给$S^{l+1}$中的活跃服务器

  <img src="/Users/wangluyao/Library/Application Support/typora-user-images/image-20220411141213794.png" alt="image-20220411141213794" style="zoom: 33%;" />

考虑的是每个协议可以腐化$t$个服务器，这与经典场景中总共腐化$t$方不同。敌手在腐化协议$S^l$的前$t$个和$S^{l+1}$的后$t$个具有优势。

> 前$t$个和后$t$个如何区分

由于计算shares-of-shares本质上是再次随机化了状态，在hand-off阶段的epoch$l$最后，敌手意识到

- 在epoch$l$的hand-off阶段，$nt$个shares-of-shares发送给了最后$t$个腐化的服务器

- 在$S^l$的前$t$个腐化的服务器发送了$(n-t)*t$ Shares-of-shares给$S^{l+1}$中$(n-t)$个诚实的服务器

  （这与常规BGW没有差异，敌手拥有的关于$S^{l+1}$中$(n-t)$个诚实服务器的状态只与他们单独状态的$t$个份额有关，保证了隐私性 ）

> 假设每一层有$n$个服务器

------

**获得恶意安全的方法**

- 传统方法：Gate-by-gate check 方法 vss，但是需要额外的交互，无法获得最大流动性

- 新方法：consolidated checks，整个电路检查一次。

  基于线性的MPC协议对于additive attack是安全的，意味着任何恶意敌手的策略等同于对电路的每条线注入additive error。

  将电路编译成另外一个电路可以自动发现错误，例如运行一个半诚实协议在AMD电路来得到恶意安全。

  半诚实、最大流动性MPC协议可以运行在此类电路上。但是，转换的开销很大。

  ------

  对于电路的每一个shared wire值$z$，各方计算$z$的MAC值的份额。协议最后，参与方验证所有MAC的有效性。

  各方在协议开始产生一个single、secretMAC密钥$r$，计算$\text{MAC}(r,z)=rz$。

  如果敌手对$z$注入additive error $\delta$来逃避检查，势必会对MAC注入一个对应additive error$\hat{\delta}=r\delta$。

  由于$r$是统一分布的，所有服务器都不知道，因为只会在域范围内以可以忽略的概率发生。

  验证MAC需要揭露密钥$r$，这只在协议的最后做，太早揭露则允许敌手伪造。

  为了有效验证MAC，参与方以浓缩检查的方式完成协议：产生随机系数$\alpha_k$，计算wire值的线性组合，MAC值为$u=\sum_{k \in [|C|]} \alpha_k*z_k$和$v=\sum_{k \in [|C]} \alpha_k*rz_k$

  最后在揭露输出分享之前，重构密钥$r$，交互验证是否$v=ru$
  
  ------
  
  将上述机制应用到fluid MPC中：输出阶段，各方交互产生$\alpha_k$的分享，本地计算线性组合，重构$r$，进行equality验证。

------

**增加计算线性组合**

为了将consolidated check运用到fluid MPC，需要一个方法计算上述汇总值，不需要在输出阶段进入整个中间计算。

服务器通过协议计算$u$和$v$，可以通过将每一个协议对应与前一个协议评估的电路的部部分$u$和$v$合并到部分总和中。

协议$S^l$要做的事

- 评估在$l$层上的门
- 计算在$l$层上门的MAC
- 计算在$l-1$层之前的所有门的部分线性组合

在第$i$层电路的第$k$个门的输出表示为$z_k^i$。

服务器在$l$层的电路$S^l$也收到$S^{l-1}$的份额$u_{l-2}=\sum _{i \le{l-2}} \sum_{k \in[w]} \alpha_k^i *z_k^i $ 和$v_{l-2}= \sum _{i \le{l-2}} \sum_{k \in[w]} \alpha_k^i *r z_k^i$（此过程发生在hand-off阶段，$\alpha_k^i$是输出门的值）

在$l$层的computation phase，计算$u_{l-1}=u_{l-2}\sum_{k \in[w]} \alpha_k^{i-1} *z_k^{i-1} $和$v_{l-1}=v_{l-2}\sum_{k \in[w]} \alpha_k^{i-1} *rz_k^{i-1} $

但是对所有$\alpha_k^l$分享再传递很复杂，如是由服务器统一生成则不符合fluid（因为流动性可能会让$j$位置产生变动）

解决方法：考虑一个协议，$S^{j-1}$的服务器产生一个随机值并分享它，发送一个份额到$S^j$的每一个服务器，使用Vandermonde matrix组合得到正确的$\alpha_k^j$的正确分享。

------

**编译器**

运行当前层的电路门，计算前一层的MAC值，累加得和。

输入阶段：用户产生秘密随机MAC密钥$r$的分享，秘密随机值$\beta,\alpha_1,...\alpha_w$.

协议过程中：服务器累加计算$u=\sum_{l\in [d]} \sum_{k \in [w]}(\alpha_k(\beta)^l)*z_k^l$和$v=\sum_{l\in [d]} \sum_{k \in [w]}(\alpha_k(\beta)^l)*rz_k^l$

协议组后，参与方验证$v=ru$

------

**fluid MPC**

计算模型：client-server model，服务器的位置无需提前固定

各方使用点对点和广播通道，并且假设完全同步的消息通道，敌手不能控制消息的发送。

协议执行具像化为一个交互式图灵机$\varepsilon$，即环境

**动态计算模型：**

input stage：$\varepsilon$在协议开始将输入给客户，客户预处理他们的输入，并将其传递给服务器进行计算。

Execution stage：服务器进行函数计算

Output stage：客户重构函数的输出，之后交给$\varepsilon$

用户只参与了输入，输出阶段，需要输入输出阶段的计算复杂度独立于函数的深度。

主要的任务是将计算任务下放给服务器，但密集型计算的输入输出阶段无法实现这一目的。

<img src="/Users/wangluyao/Library/Application Support/typora-user-images/image-20220414102351126.png" alt="image-20220414102351126" style="zoom: 40%;" />



在每个epoch阶段，只有$S^l$的部分服务器参与计算

**协议的模型选择**，考虑三方面：形式，大小，可能与其他协议的交叉。

形式的两个选择：

- static：服务器需要提前提交资源。过于限制。
- on-the-fly：epoch$l+1$的协议在epoch$l$的hand-off阶段决定，并且每个人都知道

在epoch$l$，如果在协议的开始，$\varepsilon$提供一个指定的输入给一方，		

在动态环境下的两种协议选择

- volunteer committee

  本质上任何人都可以加入计算。

  实现方式：在$f_{committee}$设置取样函数$Sample$作为identity function；

  ​				epoch$l+1$中一方被包括了当且仅当它在epoch$l$中发送了一个指定给$f_{committee}$

  缺陷：敌手可能会滥用通过权来腐化部分参与者

  需要优化，设置限制

- elected committees

  抽样功能，以一定的概率

  是一种半公开的系统，使用一个合适的采样函数，选择过程可能保证每个协议的腐败数量保持在一个阈值。

**参与者的动态性**

服务器是活跃的：只有它属于$S^l \cup s^{l+1}$

协议$S^l$是活跃度：epoch$l-1$的hand-off阶段的开始和epoch$l$的hand-off阶段的结束

服务器在线：活跃或者主动监听广播通信

为了减少参与者的在线时间，理想状态下服务器只能活跃的时候在线。

**协议大小**

每个epoch允许不同尺寸的协议。需要$\varepsilon$去决定多少参与方提供了指定输入。

**协议重叠**

不作限制，一个服务器可以在多个epoch协议中

------

![image-20220414161302206](/Users/wangluyao/Library/Application Support/typora-user-images/image-20220414161302206.png)





------

**定义：R-adaptive Adversary**

$\mathcal{A}$为R-adpaptive adversary，若环境$\varepsilon$在协议开始可以腐坏用户中的一个集合$T$，并用追溯影响的方式以适应性的方式腐坏服务器。

在epoch $l$中，环境$\varepsilon$从集合$S^l$中适应性地选择腐化服务器$T^l \subset [n_l]$中的一个集合，$T^l$是$S^l$的一个规范映射。

当$\varepsilon$腐坏了服务器，$\mathcal{A}$在epoch$l$中可以获得整个过去的状态，代表自己发送消息。

$\varepsilon$可以腐坏的服务器集合，对应的追溯影响由腐坏门限$\tau$决定，$\tau$满足$\forall l,|T^l|<\tau*n_l$

> 什么是追溯影响（retroactive effect），如何追溯？

腐坏用户$\overset{追溯}\rightarrow$腐坏服务器





------

**weak privacy 弱隐私**：它在真实执行中的的截断视角可以被模拟器在理想世界中模拟（例如，它的视角包括最后一轮通信），模拟器不会查询腐败方的可信功能输入，则称协议获得了恶意敌手下的弱隐私性。

执行步骤：

1. 可信方发送$l$(所在层数）给模拟器，初始化一个只能添加的列表$Corrupt^l$
2. 模拟器发送$(j,i)$，$j$指epoch的编号($j \le l$)，$i$指被腐坏的服务器的编号。收到后，可信方将$i$增加到列表$Corrupt^j$。这一步在不同时期重复。
3. $Sim$发送$continue$给可信方，可信方对$l$进行累加。（也可以发送$abort$给可信方）

**additive attacks 附加攻击**：如果协议中敌手的任意恶意策略等同于对电路中的每一个线上增加任意值，那么就称敌手可以抵抗恶意敌手的附加攻击。这些附加值独立于诚实方的输入，直观上，这意味着诚实方输入的隐私性可以保证，但是无法保证正确性。

------

**线性协议linear protocol**

两个属性

- 消息：各方交换的每条消息要么被计算为其主要输入的任意函数，要么被计算为其传入消息的线性组合。
- 输出：每一方的输出是其输入信息的线性组合

电路以gate-by-gate的方式运行

在Fluid MPC下，定义线性协议有两个集合方，第一个集合输入，另一方得到输出。并且增加了一个结构要求：线性协议分为三个阶段：

- computation phase: 第一个集合的参与方相互通信
- hand-off phase：两个集合的参与方相互通信
- output phase：第二个集合的参与方计算输出

linear-based protocol + Fluid MPC通用框架

- input stage：在第一个committee的用户和服务器执行一个linear protocol，允许客户秘密分享他的输入
- execution stage：每个committee运行一层电路，对于一层中的每个门$S^l$中方服务器运行门并将份额传递给$S^{l+1}$的服务器，committee$S^l$和$S^{l+1}$计算linear protocol。最后一个committee将门的份额发送给客户。
- output stage：收到输入，重构。

------

> 问题：**Fluid方案中**
>
> **如果初始方案是honest majority setting, 诚实方均退出了协议，则协议终止？**
>
> **如果初始方案是semi-honest的，**

------

在Shamir的方案中，每一个用户在一个域上产生一个多项式，但是多项式的次数是固定的，这意味着方案的门限若没有重新分享则无法被更改，服务器的数量也受到限制。







# Secure Multi-party Computation for Cloud-based Control

<img src="/Users/wangluyao/Library/Application Support/typora-user-images/image-20220317170109034.png" alt="image-20220317170109034" style="zoom: 33%;" />

一整个系统由多个子系统组成

setup方持有系统模型和参数

控制决策取决于cloud controller

控制输入由虚拟的actuator实施











# Le Mans

Fluid MPC只考虑大多数诚实的情况

本文将其拓展到了大多数参与方在任意点可以被腐化的环境下（**dishonest majority**)

具体地：提出了SPDZ协议的变种，支持动态参与。

- 描述了SPDZ的通用预处理，允许n方计算correlated randomness
- 补充了动态SPDZ在线阶段
  - 转换了每个乘法的在线阶段，在使用三元组去乘前先验证$c$；
  - 由于一个恶意方对$c$引入了错误，需要增加一个**验证过程**；

- 预处理协议高效使用pseudorandom correlation generators。参与方的存储和通信消耗几乎独立于函数

支持fluid 在线阶段



关注online阶段参与方的动态变化

每一轮发送一个消息和离线之前，一个不同的协议加入来接收前一个协议的消息



分为四个阶段：

- preprocessin: 产生三元组；之后参与计算的用户要活跃一下，之后可以离线。
- input; 
- execution：以epoch的方式进行处理，每个epoch中的成员固定；包含两个部分，computation phase和hand-off phase（同fluid MPC）。
- output 









Fluid SPDZ-----一种类SPDZ在线阶段支持fluidity。

基于构造的通用预处理，所有参与方$P_{main}$都参与。

在在线阶段，以部分用户$P_{curr} \in P_{main}$开始，这个协议之后会以dynamic的方式进行（dynamic SPDZ的协议在在线阶段的一开始就固定了）。

epoch中的当前协议为$P_{curr}$。

  几个支持模块：

- 简单重分享：对协议$P_{curr}$的加法值$[x]^{p_{curr}}$重分享到$P_{next}$

  - 为了减少通信，假设在setup阶段，每一对参与者分析一个PRG种子。

- 重分享MACs：key-switching 过程

  简单重分享无法保证状态在转移过程中的安全性





在不诚实环境下，大多数MPC协议使用MAC基于认证秘密共享，例如SPDZ和BDOZ协议。

这些协议依赖于一个预处理过程，使用公钥风格的加密，产生大量相关随机值（<u>指的是三元组吗？待确认</u>）在在线阶段使用。

但这意味着每一方都需要维持一个大的状态（<u>持有很多三元组？</u>），且与函数的复杂性相关。

那么在fluid MPC中，希望协议转移，整个状态也能安全的转移（<u>三元组也转移？这样可以减少三元组的消耗，并且和函数大小独立开，减少了通信复杂度</u>）



通用预处理过程：

在SPDZ中，各方需要预处理三元组。

在预处理阶段，之后在某个节点需要参与计算的所有参与方都需要参与，但是之后就可以下线了。

本文考虑产生部分三元组，$c$是未认证的，得到$a,b$去重新构造$c$。

但由于$c$没有认证，因此无法和SPDZ一样使用在线阶段

$\Rightarrow$改进了在线阶段，在每个乘法阶段，使用乘法三元组之前先验证$c$；由于恶意方可能在$c$上加入错误，增加了一个verification phase来检验乘法的正确性。各方计算一个电路的随机版本，每一条线乘上一个秘密的随机的值$r$。在计算的最后阶段，各方运行一个batch verfication 过程来检验两个计算的一致性。

最大流动性在线阶段：通用预计算过程允许任何协议获得一个乘法三元组，最后用MAC去验证。这带来了一个问题：MAC密钥的一致性。当前协议$P_{curr}$需要reshare他们的状态包括MAC密钥$\Delta_{P{curr}}$给下一个协议$P_{next}$。但是$P_{next}$需要在相同的MAC密钥下验证三元组。另一方面，预处理过程允许在另一个密钥$\Delta_{p_{next}}$下获得三元组。为了避免这个问题，$P_{curr}$需要重新分享剩下的电路运算中需要的所有三元组。$P_{next}$需要使用他们中的一些，重分享给下一个协议。这增加了通信量。

$\Rightarrow$解决方法Key-switching，允许$P_{curr}$在单轮转移一个份额$[x]$给$P_{next}$，同时转移$P_{next}$的MAC key。

Switch key的过程中，一个挑战是如何验证open value 的MAC（<u>SPDZ中使用的是batch MAC，此处无法使用，理由是需要存储large state，指三元组？</u>）

Fluid SPDZ和proactive MPC之间的区别是敌手的动机和行为。在proactive方案中，敌手通常有“corruption budget“，限制敌手任意腐蚀参与方。































# dynamic MPC 报告

当前的MPC方案需要所有参与方参与协议执行的全程，因此需要复杂的功能的提升。

动态参与模型（dynamic participation model）是指参与方拥有离线和重新加入的灵活性。

> “MPC-as-a-service”范式：将MPC部署到volunteer-operated 网络中，例如区块链，其动态性是本身就存在的。

## fluid MPC

指参与方可以动态加入和离开计算。需要每个参与方需要参与的最小协议数急流动性fluidity，衡量标准是必须在线的通讯轮数。







$A_{\alpha},\alpha \in \wedge$都是开集







美密21对fluid MPC选用shamir

对秘密的分享方便使用fluid，但是GC不适用

提供计算能力的场景是动态的

公有链挖矿

区块链代替联邦学习中的服务器，



联邦学习个性化

用户不同资源的能力

结合无线通信场景

原先传浮点数，但是小数等不同，90%的都不传，只传了整数

评价模型的质量，可解释AI

串行编程，并行编程难

**数据提供方和所谓的计算方做结合**

**数据提供方要不要动态**

**联邦场景**







# YOSO

serverless computing 

无服务器架构可以提供额外的好处，即通过向攻击者隐藏协议中涉及的物理机器直到它们完成工作，从而提高对有针对性的拒绝服务攻击的抵抗力。

然而，实现这种保护需要协议只使用无状态方，每一方只发送一条消息，并且不需要再次说话。这种协议风格最著名的例子可能是比特币中使用的 Nakamoto 共识协议：一个节点可以通过运行本地彩票（挖矿）来赢得生产下一个区块的权利，同时保持隐蔽。一旦赢得了权利，它就会通过发送一条消息来执行。之后，物理实体不再需要发送更多消息







# Updatable PSI

现有的方案are designed for static datasets ，并且只能上传一次到云端

想要解决的问题是，对于云端数据集的更新，不发生数据的泄漏，再实现PSI。

现有的解决方案，要对更新后的数据集再次进行PSI计算，只能本地更新后再加密重新上传云端，这毫无疑问产生了额外的开销。

针对云端的PSI处理，称为delegated PSI，与之相对的传统PSI，是对本地数据集进行求解。

> locol datasets 和static datasets有无区别

delegated PSI又可进一步细分为：one-off和repeated delegation of PSI

- One-off：无法重新使用外包的加密数据，需要本地重新加密数据
- repeated delegation：用户只需外包存储加密数据一次，数据拥有者同意可进行任意次计算



> 研究思路：delegated PSI的框架



为什么需要support dynamic data？

There are numerous PSI application that rely on frequently updated datasets, which is vital for the PSI schemes to efficiently support update on the outsourced private datasets. Otherwise, they would impose large communication, storage and computation costs,when big data needs to be updated regularly.

It is a trivial secure way to update outsouced private data is to download the entire data, locally update them and re-upload them to the cloud, which is not efficient.

A delegated PSI protocol that can do so, more efficiently without sacrificing the privacy of the data or the efficiency of the PSI computation, would be desirable.



传统的PSI在云环境下并不适用，计算任务外包给云，但是云并不是完全可信的 ，但同时，希望能够完全利用云的存储和计算能力，同时可以保护数据隐私。

在delegated PSI场景下，primary security and functional requirements 必须满足

- Security requirements

  - 隐私及结果的保护

    云无法计算出用户的数据元素、数据交集、结果接收者无法获得交集以外的信息

  - 获得计算认证

    没有所有计算方的统一，没有参与方可以获得结果

  - 结果正确性的验证

- functional requirements

  - 云支持数据存储和PSI计算

    数据外包给云一次，本地进行删减，无需反复重新上传、下载外包的数据

  - Non-interactive setup

    参与方在各个时间点，独立的准备和上传数据，无需交互

  - efficiency

    efficiency in both computation and communication is desirable in general

  - support dynamic data

## traditional PSI

**freedman2004efficient**

主要方法：paillier homomorphic encryption; polynomial representation of sets

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



**==方法二：==**

两方环境下，对应集合为$I=\{A,B\}$，使用多项式$\rho^{(I)}$进行加密，并将$E_{pk}(\rho^{(I)})$发送给对方。

收到后，选择一个随机多项式$\gamma^{(I)}$，与之相乘

例如A方计算$E_{pk}(\rho^{(A)} \cdot \gamma^{(B)})$，B方计算$E_{pk}(\rho^{(B)} \cdot \gamma^{(A)})$，再计算同态加
$$
E_{pk}(\rho^{(A)} \cdot \gamma^{(B)}+\rho^{(B)} \cdot \gamma^{(A)})
$$
解密得到$\delta=\rho^{(A)} \cdot \gamma ^{(B)}+\rho^{(B)} \cdot \gamma ^{(A)}$

若$\delta(s_i^{(I)})=0$，则$s_i^{(I)}$即为交集



> 使用ZKP将安全性提高到恶意敌手攻击下



## 使用OPRF去构造PSI

> Two-party protocol between sender $S$ and receiver $R$ for securely computing a pseudorandom  function $f_k()$
>
> - ==Functionality: $(k,x) \rightarrow (\perp, f_k(x))$==
>
> - key distributed by sender
> - input $x$ contributed by $R$
> - $R$ learns $f_k(x)$, $S$ learns nothings

**使用OPRF构造朴素的PSI算法：**

- A构造$n$个不经意伪随机函数的种子$K_i$
- B为Y中的每一个元素$y$，执行一个对应OPRF，得到集合$H_B=\{F(K_i,y_i)|y_i \in Y\}$
- A为X中的每一个元素x，执行每一个不经意伪随机函数，得到集合$H_A=\{F(K_i,x)|x \in X\}$
- $A \overset{KA}{\rightarrow} B $，B求交集$H_A \cap H_B$，在将交集映射回Y，即可得到X与Y的交集。

$\rightarrow $问题：集合$H_A$的大小为$O(n^2)$

$\rightarrow$将集合大小限制在$O(n)$：使用cuckoo hashing

> cuckoo hashing
>
> - 对key值hash，生成两个hash key值，hashk1和 hashk2, 如果对应的两个位置上有一个为空，那么直接把key插入即可。
> - 否则，任选一个位置，把key值插入，把已经在那个位置的key值踢出来。
> - 被踢出来的key值，需要重新插入，直到没有key被踢出为止。
>
> 哈希函数是成对的，分别映射到两个位置，一个是记录的位置的，另一个是备用位置（用来处理碰撞）
>
> > https://coolshell.cn/articles/17225.html
> >
> > https://lrita.github.io/2020/02/11/cuckoo-hashing-filter/

**使用cuckoo hashing构造PSI**

- A，B双方共同选择三个哈希函数$h_1,h_2,h_3$
- B将持有的$n$个元素Y，使用cuckoo hashing，





# CHURP

proactive secret sharing for dynamic committees

使用双变量多项式$B(x,y)$满足$B(0,0)=s$，份额是一元多项式，$B(x,i),B(i,y)$，其中$i$是节点索引。
