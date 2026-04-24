# Arduino Breadboard Setup - Editorial

## **Problem Overview**
You are given a breadboard with **N columns** and **M rows** of holes. Each column has **M holes**, and all holes in the same column are electrically connected. You place **one LED per column**, meaning the state of each LED (ON/OFF) is determined by the electrical signal in its column.

You are also given **Q queries**, each representing an attempt to connect two holes (from different columns) using a jumper cable. If either hole is already occupied, the connection fails. Otherwise, the columns become electrically connected, meaning their LEDs must share the same state.

After each query, you must compute the number of valid LED configurations (modulo $10^9 + 7$).

---

## **Key Insights**

### **1. Initial State**
- Each column is independent, so the number of possible configurations is $2^N$ (each LED can be ON or OFF independently).

### **2. Effect of Connections**
- When two columns are connected, they must have the same state (ON or OFF), reducing the number of independent choices.
- If a connection fails (due to occupied holes), the configuration remains unchanged.

### **3. Final Answer**
- The number of valid configurations is $2^k$, where $k$ is the number of **connected components** (groups of columns that must share the same state).

---

## **Approach**

### **1. Union-Find (Disjoint Set Union - DSU)**
- **Purpose**: Track connected components of columns.
- **Additional Data**: Maintain a bitmask for each column to track available holes (since a hole can only be used once).

### **2. Handling Queries**
- For each query:
  - Check if the holes are free.
  - If they are, merge the columns and update the number of connected components.
  - The answer after each query is $2^{\text{components}} \mod 10^9 + 7$.

### **3. Efficiency**
- **DSU with Path Compression and Union by Size** ensures near-constant time per operation.
- **Total Time Complexity**: $O(Q \alpha(N))$, where $\alpha$ is the inverse Ackermann function (effectively constant).

---

## **Solution Steps**

### **1. Initialization**
- Start with $2^N$ configurations (each column is independent).
- Initialize DSU to track connected components and available holes.

### **2. Processing Queries**
- For each query:
  - Check if the holes are free.
  - If they are, merge the columns and update the number of connected components.
  - Update the answer by dividing by 2 (using modular inverse) since merging reduces the number of independent choices.

### **3. Output**
- After each query, print the current number of valid configurations.

---

## **Complexity Analysis**

- **Time Complexity**: $O(Q \alpha(N))$, where $\alpha$ is the inverse Ackermann function (effectively constant).
- **Space Complexity**: $O(N)$ for storing DSU structures.

---

## **Final Notes**

- **Modular Arithmetic**: Since $2^{10^5}$ is too large, we compute the answer modulo $10^9 + 7$.
- **Modular Inverse**: The modular inverse of 2 is $500000004$ (since $2 \times 500000004 \equiv 1 \mod 10^9 + 7$).

This approach efficiently handles the constraints while ensuring correctness.