具体过程：在三方环境下，两个待分享秘密是$v$与$u$

拥有随机比特为$x_1,x_2,x_3 \in \{0,1\}$，$y_1,y_2,y_3 \in \{0,1\}$，且满足$x_1 \oplus x_2 \oplus x_3 = 0$， $y_1 \oplus y_2 \oplus y_3 = 0$

$p_1:(x_1,a_1)$，其中，$a_1=x_3 \oplus v$；$(y_1,b_1)$，其中，$b_1=y_3 \oplus u$；

$p_2:(x_2,a_2)$，其中，$a_2=x_1 \oplus v$；$(y_2,b_2)$，其中，$b_2=y_1 \oplus u$；

$p_3:(x_3,a_3)$，其中，$a_3=x_2 \oplus v$；$(y_3,b_3)$，其中，$b_3=y_2 \oplus u$；

即：$p_i:(x_i,a_i=x_{i-1} \oplus v)$, $(y_i,b_i=y_{i-1} \oplus v)$

- **对于XOR（addition）运算：$v \oplus u$**

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
  
  
  
- **对于AND（multiplication）运算：$v \wedge u$也可表示为$uv$**

​	选择correlated randness $\alpha, \beta, \gamma$，满足$\alpha \oplus \beta \oplus \gamma =0$

各方计算

$r_1=x_1y_1 \oplus a_1b_1 \oplus \alpha$                 $p_1 \overset{r_1}{\rightarrow} p_2$

$r_2=x_2y_2 \oplus a_2b_2 \oplus \beta$                 $p_2 \overset{r_2}{\rightarrow} p_3$

$r_3 = x_3y_3 \oplus a_3b_3 \oplus \gamma$                 $p_3 \overset{r_3}{\rightarrow} p_1$

此时，$p_1(r_1,r_3)$，$p_2(r_2,r_1)$，$p_3(r_3,r_1)$，完成了对$r_1,r_2,r_3$的分享

$$\begin{align*}
 r_1 \oplus r_2 \oplus r_3 & =  (x_1y_1 \oplus a_1b_1 \oplus \alpha) \oplus (x_2y_2 \oplus a_2b_2 \oplus \beta) \oplus (x_3y_3 \oplus a_3b_3 \oplus \gamma)\\
  &= x_1y_1 \oplus x_2y_2 \oplus x_3y_3 \oplus (a_1b_1 \oplus a_2b_2 \oplus a_3b_3) \oplus (\alpha \oplus \beta \oplus \gamma)
\end{align*}$$

其中：

$a_1b_1 = (x_3 \oplus v) (y_3 \oplus u) = x_3y_3 \oplus x_3u \oplus y_3v \oplus uv$

$a_2b_2 = (x_1 \oplus v) (y_1 \oplus u) = x_1y_1 \oplus x_1u \oplus y_1v \oplus uv$

$a_3b_3 = (x_2 \oplus v) (y_2 \oplus u) = x_2y_2 \oplus x_2u \oplus y_2v \oplus uv$

所以：

$$\begin{align*}
 r_1 \oplus r_2 \oplus r_3 & = x_1y_1 \oplus x_2y_2 \oplus x_3y_3 \oplus (x_3y_3 \oplus x_3u \oplus y_3v \oplus uv) \oplus (x_1y_1 \oplus x_1u \oplus y_1v \oplus uv) \oplus (x_2y_2 \oplus x_2u \oplus y_2v \oplus uv) \oplus (\alpha \oplus \beta \oplus \gamma)\\
\end{align*}$$

可通过化得到$r_1 \oplus r_2 \oplus r_3 = uv$

> 用到两条运算律$a \oplus a =0$, $a \oplus 0 = a $
