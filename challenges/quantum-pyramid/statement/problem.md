---
title: "Quantum Pyramid"
author: "Raouf Ould Ali"
difficulty: "Hard"
---

# Quantum Pyramid

Raouf is building his own quantum computer, but as you may know, qubits are really hard to implement and very unstable. For his first prototype — the **SpeedMachine** — he uses qubits alongside classical bits. Each cell of the pyramid-shaped machine is a *register* consisting of 31 classical bits and 1 qubit at the least-significant position. The 31 classical bits and the qubit together represent a 32-bit integer, where the qubit holds the LSB. A qubit behaves like a normal bit, except it can also be in a **superposition** of 0 and 1 simultaneously (denoted $=$).

You can see a SpeedMachine with 6 input integers in the figure below:

\begin{figure}[h]
\centering
\includegraphics[width=0.35\textwidth]{challenges/quantum-pyramid/statement/illustration.png}
\caption{Quantum Pyramid Structure}
\end{figure}

The SpeedMachine of size $n$ has $n$ rows. The bottom row (row 1) is loaded with the input sequence of $n$ integers. Each register in every other row reads the two registers directly below it and computes their **maximum over the 31 classical bits only** (the qubit is not part of the comparison). The qubit of the resulting register is then set as follows:

- If the two registers below have **different** classical bit values, the qubit simply follows the qubit of whichever register had the larger classical value.
- If the two registers below have **equal** classical bit values, then:
  - if both qubits below are $0$, the new qubit is $0$;
  - if both qubits below are $1$, the new qubit is $1$;
  - otherwise (at least one qubit is $=$ or the two qubits differ), the new qubit is $=$ (superposition).

When a register is **observed** (read), its value collapses as follows: if the qubit is $0$ or $1$, the observed integer is exactly $(c \ll 1) \mid q$, where $c$ is the 31-bit classical value and $q \in \{0,1\}$. If the qubit is $=$, the register can collapse to either $(c \ll 1)$ or $(c \ll 1) \mid 1$, and **both** possible values are reported.

## Input

The first line contains two integers $n$ and $Q$ — the size of the SpeedMachine and the number of queries.

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ — the input sequence loaded into row 1.

Each of the next $Q$ lines contains two integers $k$ and $r$ — a query asking for the value stored in the register at row $r$, column $k$.

## Output

For each query, print either one integer (if the qubit is not in superposition) or two integers separated by a space in increasing order (if the qubit is in superposition $=$), representing all possible observed values.

## Constraints

- $1 \le n \le 10^5, \quad 1 \le Q \le 10^5$
- $0 \le a_i < 2^{32}$
- $1 \le r \le n, \quad 1 \le k \le n - r + 1$

## Example

**Input:**
```
5 3
2 3 1 2 1
1 4
2 2
4 2
```

**Output:**
```
2 3
3
2
```

## Explanation

Each input value is split into 31 classical bits (upper part) and 1 qubit (LSB):

- $a_1 = 2 = \mathtt{10}_2$: classical $= 1$, qubit $= 0$
- $a_2 = 3 = \mathtt{11}_2$: classical $= 1$, qubit $= 1$
- $a_3 = 1 = \mathtt{01}_2$: classical $= 0$, qubit $= 1$
- $a_4 = 2 = \mathtt{10}_2$: classical $= 1$, qubit $= 0$
- $a_5 = 1 = \mathtt{01}_2$: classical $= 0$, qubit $= 1$

Building the pyramid upward (notation: $\mathtt{c[q]}$ where $c$ = classical bits, $q$ = qubit):

**Row 2:**
- $k=1$: $\max(1,1)=1$, equal, qubits $0$ and $1$ differ $\Rightarrow$ $\mathtt{1[=]}$
- $k=2$: $\max(1,0)=1$, differ, inherit qubit of $a_2$ $\Rightarrow$ $\mathtt{1[1]}$
- $k=3$: $\max(0,1)=1$, differ, inherit qubit of $a_4$ $\Rightarrow$ $\mathtt{1[0]}$
- $k=4$: $\max(1,0)=1$, differ, inherit qubit of $a_4$ $\Rightarrow$ $\mathtt{1[0]}$

**Row 3:**
- $k=1$: $\max(1,1)=1$, equal, qubits $=$ and $1$ $\Rightarrow$ $\mathtt{1[=]}$
- $k=2$: $\max(1,1)=1$, equal, qubits $1$ and $0$ differ $\Rightarrow$ $\mathtt{1[=]}$
- $k=3$: $\max(1,1)=1$, equal, qubits $0$ and $0$ $\Rightarrow$ $\mathtt{1[0]}$

**Row 4:**
- $k=1$: $\max(1,1)=1$, equal, qubits $=$ and $=$ $\Rightarrow$ $\mathtt{1[=]}$
- $k=2$: $\max(1,1)=1$, equal, qubits $=$ and $0$ $\Rightarrow$ $\mathtt{1[=]}$

Now answering the queries:

- **Query 1** ($k=1$, $r=4$): register $\mathtt{1[=]}$, classical $=1$, qubit $==$ $\Rightarrow$ observed values $2$ and $3$. Output: **2 3**
- **Query 2** ($k=2$, $r=2$): register $\mathtt{1[1]}$, classical $=1$, qubit $=1$ $\Rightarrow$ observed value $3$. Output: **3**
- **Query 3** ($k=4$, $r=2$): register $\mathtt{1[0]}$, classical $=1$, qubit $=0$ $\Rightarrow$ observed value $2$. Output: **2**