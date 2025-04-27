

## 📖 Project Overview
This project is a simple **interpreter** written in C language.  
It reads a file containing variable assignments and evaluates them.  
The interpreter displays the results sorted using:
- **Binary Search Tree (BST)** — printed in *inorder* traversal.
- **Heap Sort** — using a *minimum heap*.

---

## 🚀 How to Use
1. **Run the program.**
2. **Enter the filename** that contains the source code instructions (example: `test.txt`) or **press `Ctrl+Z`** to exit.
3. The program reads, checks, and interprets the instructions.
4. **Output**:
   - Variables sorted *inorder* (BST by variable name).
   - Variables sorted using *heap sort* (by variable value).


**Program output:**
- Inorder traversal of variables.
- Heap sorted variables.

---

## ⚙️ System Description

- **Expression Evaluation:**
  - The Right-Hand Side (RHS) expressions are **converted from infix to postfix** using **stacks**.
  - The postfix expression is then evaluated to compute the result.

- **Storage of Variables:**
  - Variables are stored in a **Binary Search Tree (BST)** where:
    - **Key**: Variable Name (can be **any length**).
    - **Value**: Computed Value (can be **float or int**).
  - Insertion or update of variables is handled using a `put(k, v)` function:
    - If the key **already exists**, the **value is updated**.
    - If the key **does not exist**, a **new key/value pair is inserted**.

- **Sorting:**
  - **By Variable Name:** Done using an **inorder traversal** of the BST.
  - **By Variable Value:** Done using a **heap sort algorithm** on an array of nodes.

- **Supported Numbers:**
  - Supports **both integer and floating-point numbers**.
  - Numbers may consist of **one or more digits**.

- **Data Structures Used:**
  - **Arrays**
  - **Stacks**
  - **Binary Search Trees (BST)**
  - **Heaps**

---

## ❗ Error Handling
The interpreter can detect and handle the following errors:
- **Invalid Symbol** in the expression.
- **Missing equal sign `=`** between LHS and RHS.
- **Invalid LHS expressions**:
  - Left-hand side must contain **only one variable**.
  - Example: `x+y=5` generates an error.
- **Invalid RHS expressions**:
  - Example: `(x+y)/(3+1` generates an error (missing closing bracket).
- **Undefined Variables** used on the RHS.
- **Invalid Variable Names** (invalid characters or format).

> If errors are found, the interpreter **guides the user to correct them** before continuing.

---

## 🧪 Sample Test Cases

- **Missing equal sign (`=`):**
  - Input: `x 5+2`
  - Output: Error message indicating missing `=`.
- **Invalid LHS expression:**
  - Input: `x+y=5`
  - Output: Error: Left-hand side must be a single variable.
- **Invalid RHS expression:**
  - Input: `z=(x+y)/(3+1`
  - Output: Error: Invalid expression (missing `)`).
- **Undefined variable usage:**
  - Input: `y=x+3` (where `x` was not yet defined)
  - Output: Error: Undefined variable `x`.

---

## 🔥 Functional Testing Example
- **Overwriting an existing variable:**
  - Input:
    ```
    x=5+2
    x=x*2
    ```
  - Output:
    - Correctly updates the value of `x`.
    - Displays updated results using BST (inorder) and Heap Sort (by value).

---

## 📋 Limitations
- Variable names in LHS must be **single variable** (no expressions).
- Basic math operations supported (`+`, `-`, `*`, `/`).
- The interpreter expects **clean, correctly formatted input** or will display errors.

---

## ✅ Summary
This project demonstrates a simple but powerful interpreter that:
- Validates expressions,
- Handles variable storage and updates,
- Supports both floats and integers,
- Evaluates expressions using infix-to-postfix conversion,
- Stores variables efficiently in a BST,
- Sorts output using BST inorder and Heap Sort.

