具体过程：在三方环境下，两个待分享秘密是$v$与$u$

拥有随机比特为$x_1,x_2,x_3 \in \{0,1\}$，$y_1,y_2,y_3 \in \{0,1\}$，且满足$x_1 \oplus x_2 \oplus x_3 = 0$， $y_1 \oplus y_2 \oplus y_3 = 0$

$p_1:(x_1,a_1)$，其中，$a_1=x_3 \oplus v$；$(y_1,b_1)$，其中，$b_1=y_3 \oplus u$；

$p_2:(x_2,a_2)$，其中，$a_2=x_1 \oplus v$；$(y_2,b_2)$，其中，$b_2=y_1 \oplus u$；

$p_3:(x_3,a_3)$，其中，$a_3=x_2 \oplus v$；$(y_3,b_3)$，其中，$b_3=y_2 \oplus u$；

即：$p_i:(x_i,a_i=x_{i-1} \oplus v)$, $(y_i,b_i=y_{i-1} \oplus v)$

- 对于XOR（addition）运算：$v \oplus u$

  各方在本地计算：

  $p_1$：$x_1 \oplus y_1 = z_1$与$a_1 \oplus b_1 = c_1$

  $p_2$：$x_2 \oplus y_2 = z_2$与$a_2 \oplus b_2 = c_2$

  $p_3$：$x_3 \oplus y_3 = z_3$与$a_3 \oplus b_3 = c_3$

  可进一步得到 $c_1=a_1 \oplus b_1 = (x_3 \oplus v) \oplus (y_3 \oplus u) = (x_3 \oplus y_3) \oplus(v \oplus u) = z_3 \oplus (v \oplus u)$

  同时也能得到$z_3 \oplus z_1 \oplus z_2 = 0$（后面有用）

  $c_2 = z_1 \oplus (v \oplus u)$	

  $c_3 = z_2 \oplus (v \oplus u)$	

  （即，各方得到了$v \oplus u$的份额）

  $c_1 \oplus c_2 \oplus c_3 = z_3 \oplus (v \oplus u) \oplus z_1 \oplus (v \oplus u) \oplus z_2 \oplus (v \oplus u) = (z_3 \oplus z_1 \oplus z_2) \oplus (u \oplus v) = u \oplus v$

  上述方案没有实现门限
