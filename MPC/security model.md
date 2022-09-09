腐化行为由敌手执行$Adv$

- 按照属性分类：

  - 被动/主动

    - 被动passive（也叫半诚实）：$Adv$可以监控被腐化的参与方并获得腐化方是所有信息，但不控制其行为，腐化方仍旧依照协议执行操作。

    > 多个腐化方可能会发起合谋攻击；
    >
    > 理想世界中的攻击者视角只包含发送到可信方的输入和从可信方接收到的输出，因此必须能够使用这些信息生成一个视角，和真实世界中的攻击者视角看起来一样。
    >
    > 此攻击者在理想世界中生成了一个真实世界中的“仿真”攻击者视角，故称其为仿真者（simulator），能生成这样一个仿真者，就能证明攻击者在现实世界中实现的所有攻击效果都可以在理想世界中实现。
    >
    > 协议在现实世界中给出的输出概率分布与理想功能函数给出的输出概率分布相同（因为理想世界中输出的概率分布不依赖于攻陷参与方集合，即**无论攻陷了多少参与方，所有参与方都会诚实执行协议**）

    参与方在计算过程中的行为是可信的，但是无法保证参与方的**存储环境**在未来一定不会遭到攻击。

    - 主动active（恶意）：$Adv$对被腐化的参与方进行完全控制，可以执行任意操作

    > 安全性考虑两个附加因素：
    >
    > - 对诚实参与方输出的影响：
    >
    >   现实世界中，攻击者的攻击行为可能会使两个诚实参与方得到不同的输出，因为**恶意参与方可以输出任何想输出的结果**，但理想世界中所有参与方都应该得到相同的输出。
    >
    > - 输入提取：
    >
    >   在现实世界中无法明确定义恶意参与人的输入，因此在理想世界中需要知道将哪个输入提供给可信执行方。无论攻击者在现实世界中实施哪种攻击行为，也可通过为攻陷参与方选择适当的输入从而在理想世界中实现，让仿真者选择攻陷参与方的输入，此过程称为输入提取，仿真者要从现实世界中的攻击者行为中提取有效的理想世界的输入，来解释输入对现实世界造成的影响。
    >
    >   大多数安全性证明只需考虑黑河仿真过程，即仿真者只能访问现实世界中实现攻击的预言机，不能访问攻击代码本身。

  - 静态/自适应
    - 静态static：所有腐坏行为都发生在协议启动之前
    - 自适应adaptive：腐坏行为在协议期间动态发生（在协议期间的任何时候选择一个新的参与方进行腐坏）

定义安全性时，罗列安全检查清单过于繁琐，采用**现实-理想范式**，引入定义明确、涵盖所有安全性要求的“理想世界”，通过论述现实世界与理想世界的关系来定义安全性。

- 理想世界

  - 存在一个完全可信的第三方

  - 参与方通过安全信道将输入发送给可信第三方，

  - 由可信第三方完成函数的计算，并将输出发送给参与方

    攻击者可以控制任意一个或多个参与方，但不能控制可信参与方

- 现实世界

  - 不存在可信方

  - 相互交互来执行一个真实协议

    攻击者可以攻陷参与方，攻陷参与方可以遵循协议规则执行协议，也可以任意偏离协议规则执行协议。

协议是安全的$\Rightarrow$在现实世界中的攻击效果=在理想世界中的攻击效果

​					$\Rightarrow$对于任意一个现实世界的敌手$\mathcal{A}$，都存在一个理想世界中的敌手$\mathcal{S}$，使得$\mathcal{S}$在理想世界执行中的输入/输出联合分布与$\mathcal{A}$在现实世界中的输入/输出联合分布计算不可区分