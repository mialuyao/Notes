# 联邦学习

联邦学习中的多客户端联合数据训练时存在客户端**计算异质**和**统计异质**的问题

- 计算异质：客户端算力差异导致  $\Rightarrow$ 算力较慢的客户端会拖慢联邦学习的训练速度
- 统计异质：客户端数据集分布的不一致导致（客户端数据是非独立同分布的non-identically and Independently Distributed, non-IID） $\Rightarrow$难以收敛

现有FL优化方法在解决异质性问题上的局限性：

- 采用异步随机梯度下降法（ASGD）的联邦学习方法及其改进方法部分解决了计算异构问题；
- 采用同步随机梯度下降法（SSGD）的联邦学习方法及其改进方法部分解决了统计异构问题；

------

当客户端中存在算力较慢的客户端时，以上两种方法无法保证学习模型的快速收敛。

解决方法：

- 剔除速度较慢的客户端   $\Rightarrow$ 可能会降低模型的准确性
- 对客户端数据进行区分/聚类 $\Rightarrow$ 可能会让敌手知道哪些客户端拥有类似的训练数据



------

- 解决的是怎么样在一个分布式的环境下，各个参与方有各自的数据，如何将这些数据充分运用起来模型训练，又能满足各个参与方的隐私诉求。

- MPC要解决的的是多个参与方在不泄漏数据隐私的前提下，如何协作，完成对一个问题的求解。
- FL通过对不同本地模型的更新进行汇总，获得全局模型。

- 需要用到一些ML的模型建模：NN，逻辑回归、线性回归
- 多个数据源在分布式的条件下，希望仅通过**传递梯度**来保护数据隐私和完成模型训练（现已有成果针对基于梯度安全性的攻击）
- 传统的FL一般用加法同态加密系统





### **分布式学习和联邦学习的区别**

- distributed learning 

- federated learning

  - 集中式方法；
  - 多用户合作训练一个模型；
  - 原始数据无需转移至单个服务器或者数据中心；
  - 发送初识模型给各个节点；
  - 每个节点训练使用本地参数训练模型，在各自本地有一个模型的本地版本

- Federated Learning and Distributed Learning differ in three significant ways:
  - FL does not allow **direct raw data communication**. DL does not have any such restriction. （FL不允许进行直接原始数据交易）
  - FL employs the distributed computing resources **in multiple regions or organisations.** DL utilises a single server or a cluster in a single region, which belongs to **a single organisation**.（FL可在不同机构组织间进行，DL只在单个组织中进行）
  - FL generally takes advantage of encryption or other defence techniques to ensure data privacy or security. FL promises to safeguard the confidentiality and security of the raw data. There is less focus on safety in DL;（FL使用了更多的加密和数据保护技术）
  - Federated Learning leverages techniques from multiple research areas such as distributed systems, machine learning, and privacy. One can say that federated learning is an improvement on distributed learning system; （FL是DL的进阶版）

联邦学习允许模型在本地数据库上训练，并构建一个全局的调度器，通过对不同本地模型的更新进行汇总（即FedAvg算法），获得全局模型。

**Parameter-Server**

five phases:

- local training phase
- Upload phase
- Aggregate phase
- Download phase
- update phase 

<img src="/Users/wangluyao/Library/Application Support/typora-user-images/截屏2021-12-08 下午1.00.02.png" alt="截屏2021-12-08 下午1.00.02" style="zoom:33%;" />





训练数据集包括$(x,y)$，$x$代表输入特征，$y$达标理想输出值。

监督学习的训练数据包括输入特征和对应标签。

非监督学习只包含输入特征没有输出值。

半监督学习部分数据有输出值







每个用户的数据各式各样$\rightarrow$个性化

$\rightarrow$模型分为本地层和全局层

adapative personalized federated learning (APFL).  

> Deng Y, Kamani M M, Mahdavi M. Adaptive personalized federated learning[J]. arXiv preprint arXiv:2003.13461, 2020.

FedPer

> Deng Y, Kamani M M, Mahdavi M. Adaptive personalized federated learning[J]. arXiv preprint arXiv:2003.13461, 2020.

pFedMe

> T Dinh C, Tran N, Nguyen J. Personalized federated learning with moreau envelopes[J]. Advances in Neural Information Processing Systems, 2020, 33: 21394-21405.











### 挑战

1. 通信挑战
   1. 减少通信轮数$\rightarrow$本地更新
   2. 减小传输消息的大小$\rightarrow$压缩
2. 系统异构性
   1. 预计参与量低
   2. 包容异构硬件
   3. 对设备的鲁棒性
3. 统计异构
4. 隐私问题



网络形态：

- star network

  <img src="/Users/wangluyao/Library/Application Support/typora-user-images/image-20220601093957795.png" alt="image-20220601093957795" style="zoom: 33%;" />

- Decentralized topologies

  <img src="/Users/wangluyao/Library/Application Support/typora-user-images/image-20220601094055905.png" alt="image-20220601094055905" style="zoom: 33%;" />

  设备只与邻居进行通信

  分散式训练快于集中训练

处理系统异构的几个方向：

- 异步通信
- 活跃设备采用
- 容错







# Batch normalization

- 背景

  - 网络中层与层之间具有高度的关联性和耦合性。

  - 底层网络参数发生变化时

    - 每一层中的线性变换和非线性激活映射，其变化会随着网络层数的加深而被放大

    - 每一层的输入分布会发生变化，上层的网络需要调整以适应变化，加大模型训练的难度，此现象称为Internal Covariate Shift。

      > Internal Covariate Shift
      >
      > 定义：由于网络中参数变化而引起内部结点数据分布发生变化的过程
      >
      > 每一层的线性变化为$Z^{[l]}=W^{[l]}*input+b^{[l]}$，$l$表示层数；
      >
      > 非线性变换为$A^{[l]}=g^{[l]}(Z^{[l]})$，其中$g^{[l]}$表示激活函数
      >
      > 随着梯度下降的进行，$W^{[l]}$和$b^{[l]}$会被更新，$Z^{[l]}$,$A^{[l]}$随着发生变化。同时$A^{[l]}$又是第$l+1$层的输入，即$l+1$层也需要去适应此变化

- Internal Covariate Shift产生的问题

  - 上层网络需要不断调整以适应输入数据分布的变化，导致网络学习速度的降低
  - 容易陷入梯度饱和区，减缓网络收敛速度。

- 缓解ICS

  - 白化：对输入数据分布进行变化
    - 目的
      - 使得输入特征分布具有相同的均值和方差
      - 去除特征之间的相关性
    - 问题
      - 计算成本高——简化计算过程
      - 改变了网络每一层的分布——规范处理尽可能保留原始的表达能力

- Batch normalization的提出——简化+改进版白化

  - 思路
    - 对特征进行规范化，均值为0，方差为1
      - 问题：数据分布变稳定，但改变了原有数据的信息表达
        - 解决方法：引入两个可学习的参数$\alpha$和$\beta$，对规范化后的数据进行线性变换，即$\tilde{Z}_j=\gamma_j \hat{Z}_j+\beta_j$，$\gamma^2=\sigma^2,\beta=\mu$时，可以实现等价变化。
    - 增加线性变换，恢复数据本身的表达能力
  - 优势
    - 每层输入数据的分布相对稳定，加速模型学习速度
    - 使得模型对网络中的参数不那么敏感，简化调参过程

  

------

- cross-device

- cross-silo FL：客户更少，单个客户的数据量更多
