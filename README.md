<div align="center">

# Algorithm OF 1032

### An Adaptive Multi-Policy Search Framework for Efficient Searching in Sorted Arrays

A research-oriented adaptive searching framework that dynamically selects specialized search policies based on an estimated target position within a sorted array.

---

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=for-the-badge)
![Version](https://img.shields.io/badge/Version-6-success?style=for-the-badge)
![Research](https://img.shields.io/badge/Research-Algorithm-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

# Overview

Algorithm OF 1032 is an adaptive searching framework designed for **sorted arrays**.

Instead of relying on a single search algorithm throughout execution, the framework first estimates the approximate location of the target element and dynamically selects the most appropriate search policy.

The framework combines:

- Relative Position Estimator (RPE)
- Policy Manager (PM)
- Binary Search Engine (BSE)
- Head-Oriented Search Policy (HOP)
- Tail-Oriented Search Policy (TOP)

This modular architecture separates prediction, decision-making, and search execution into independent components, allowing different regions of the search space to be handled by specialized policies.

---

# Framework Architecture

<p align="center">

<img src="paper/figures/Fig1_Framework.png" width="850">

</p>

---

# Key Features

- Adaptive multi-policy search framework
- Dynamic policy selection
- Relative Position Estimation
- Configurable policy thresholds
- Modular architecture
- Constant-time policy selection
- Experimental benchmarking
- Complexity analysis
- IEEE-style research paper
- Open-source implementation

---

# Framework Components

## Relative Position Estimator (RPE)

Predicts the normalized position of the target using an interpolation-inspired estimation formula.

---

## Policy Manager (PM)

Receives the estimated position and dynamically selects the most suitable search policy.

---

## Binary Search Engine (BSE)

Handles searches where the predicted target lies near the middle region of the array.

---

## Head-Oriented Search Policy (HOP)

Specialized search policy designed for targets predicted near the beginning of the array.

---

## Tail-Oriented Search Policy (TOP)

Specialized search policy designed for targets predicted near the end of the array.

---

# Repository Structure

```text
Algorithm-of-1032
│
├── README.md
├── LICENSE
├── CHANGELOG.md
├── CITATION.cff
├── complexity.md
├── Rejected.md
│
├── paper
│   ├── Algorithm_OF_1032.pdf
│   ├── Algorithm_OF_1032.docx
│   └── figures
│
├── source
│   ├── Algorithm_OF_1032_V6.cpp
│   ├── benchmark.cpp
│   └── comparison.cpp
│
├── benchmark
│
├── versions
│
└── docs
```

---

# How It Works

```text
Input Target
      │
      ▼
Relative Position Estimator
      │
      ▼
Policy Manager
      │
 ┌────┼────┐
 ▼    ▼    ▼
HOP  BSE  TOP
      │
      ▼
 Search Result
```

---

# Experimental Evaluation

The proposed framework was experimentally evaluated using multiple benchmark datasets consisting of sorted integer arrays.

### Evaluation Metrics

- Correctness
- Iterations
- Comparisons
- Policy Selection
- Estimated Position

The framework achieved **100% correctness** across all benchmark test cases.

---

# Complexity Analysis

| Component | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Relative Position Estimator | **O(1)** | **O(1)** |
| Policy Manager | **O(1)** | **O(1)** |
| Binary Search Engine | **O(log n)** | **O(1)** |
| Head-Oriented Search Policy | **O(√n)** | **O(1)** |
| Tail-Oriented Search Policy | Experimental Analysis | **O(1)** |
| **Overall Framework** | **O(1) + T<sub>SelectedPolicy</sub>(n)** | **O(1)** |

A detailed theoretical analysis is available in **complexity.md**.

---

# Version History

| Version | Major Contribution |
|----------|-------------------|
| V1 | Initial Jump Search Improvements |
| V2 | Hybrid Jump + Binary Search |
| V3 | Multi-Policy Search |
| V4 | Policy Manager |
| V5 | Relative Position Estimator |
| **V6** | Final Adaptive Multi-Policy Framework |

For detailed changes, see **CHANGELOG.md**.

---

# Research Paper

The complete IEEE-style research paper is available in the **paper/** directory.

The paper includes:

- Abstract
- Introduction
- Related Work
- Problem Statement
- Proposed Framework
- Complexity Analysis
- Experimental Evaluation
- Results and Discussion
- Limitations
- Future Work
- Conclusion

---

# Experimental Results

The benchmark suite evaluates the framework using multiple sorted datasets and compares its behavior with Binary Search.

Metrics include:

- Correctness
- Iterations
- Comparisons
- Policy Selection
- Estimated Position

The benchmark implementation is located in:

```text
source/benchmark.cpp
```

Experimental datasets are available in:

```text
benchmark/
```

---

# Installation

Clone the repository

```bash
git clone https://github.com/NayanSadariya/Algorithm-of-1032.git
```

Enter the project directory

```bash
cd Algorithm-of-1032
```

Compile

```bash
g++ source/Algorithm_OF_1032_V6.cpp -o algorithm
```

Run

```bash
./algorithm
```

---

# Citation

If you use Algorithm OF 1032 in your research, please cite this repository.

```text
Nayan Sadariya,
Algorithm OF 1032: An Adaptive Multi-Policy Search Framework for Efficient Searching in Sorted Arrays,
GitHub Repository,
2026.
```

A machine-readable citation is also available in **CITATION.cff**.

---

# Roadmap

Future development includes:

- Formal proof of Tail-Oriented Search Policy complexity
- Adaptive threshold optimization
- Machine learning-based policy selection
- Parallel implementation
- Distributed search support
- Large-scale benchmarking
- Additional search policies

---

# License

This project is licensed under the **MIT License**.

See the **LICENSE** file for details.

---

# Acknowledgements

The development of Algorithm OF 1032 followed an iterative research process involving multiple prototype versions, experimental evaluations, rejected approaches, and architectural refinements before arriving at the final adaptive multi-policy framework.

Special thanks to the open research community and the authors of classical searching algorithms whose work provided the theoretical foundation for this research.

---

# Author

<div align="center">

## Nayan Sadariya

Computer Science Engineering Student

Research Interests

Algorithms • Data Structures • Artificial Intelligence • System Design • Software Engineering

GitHub

https://github.com/NayanSadariya

---

### Algorithm OF 1032

**Version 6 — Final Research Implementation**

Adaptive Multi-Policy Search Framework

© 2026 Nayan Sadariya

</div>