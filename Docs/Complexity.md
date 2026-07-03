# Algorithm OF 1032
## Complexity Analysis (Version 6)

---

# Overview

Algorithm OF 1032 is an adaptive multi-policy search framework designed for searching sorted arrays.

Instead of relying on a single search strategy, the framework first estimates the relative position of the target using an interpolation-based estimator and then dynamically selects the most appropriate search policy.

The framework consists of:

- Relative Position Estimator (RPE)
- Policy Manager
- Policy 0 – Binary Search Engine (BSE)
- Policy 1 – Tail-Oriented Search Policy (TOP)
- Policy 2 – Head-Oriented Search Policy (HOP)

Only one search policy executes for each query.

---

# Relative Position Estimator (RPE)

The Relative Position Estimator computes

estimate = (target − first) / (last − first)

Operations performed:

- One subtraction
- One division
- Two boundary checks

No iteration depends on the input size.

### Time Complexity

O(1)

### Space Complexity

O(1)

---

# Policy Manager

The Policy Manager performs

- One call to RPE
- Two threshold comparisons
- One policy dispatch

No loops are executed.

### Time Complexity

O(1)

### Space Complexity

O(1)

---

# Policy 0
## Binary Search Engine (BSE)

Classical iterative Binary Search.

### Best Case

O(1)

### Average Case

O(log n)

### Worst Case

O(log n)

### Space Complexity

O(1)

---

# Policy 2
## Head-Oriented Search Policy (HOP)

Each iteration computes

jump = √remaining

The recurrence relation is approximately

T(n) = T(n − √n) + 1

which yields

### Best Case

O(1)

### Average Case

O(√n)

### Worst Case

O(√n)

### Space Complexity

O(1)

---

# Policy 1
## Tail-Oriented Search Policy (TOP)

The jump distance is computed as

jump = remaining × (remaining / originalSize)

which simplifies to

jump = remaining² / originalSize

The corresponding recurrence is

T(n) = T(n − n²/N) + 1

where N denotes the original array size.

This adaptive interval reduction does not currently have a formally derived closed-form asymptotic solution.

### Best Case

O(1)

### Average Case

Determined experimentally.

### Worst Case

Formal mathematical proof pending.

### Space Complexity

O(1)

---

# Overall Framework

Algorithm OF 1032 performs

1. Relative Position Estimator
2. Policy Manager
3. Exactly one search policy

Therefore

T(n)

=

O(1)

+

T(selected policy)

The constant-time prediction and policy selection overhead does not affect the asymptotic complexity.

---

# Final Complexity Summary

| Component | Best Case | Average Case | Worst Case | Space |
|-----------|-----------|--------------|------------|-------|
| Relative Position Estimator | O(1) | O(1) | O(1) | O(1) |
| Policy Manager | O(1) | O(1) | O(1) | O(1) |
| Binary Search Engine | O(1) | O(log n) | O(log n) | O(1) |
| Head-Oriented Search Policy | O(1) | O(√n) | O(√n) | O(1) |
| Tail-Oriented Search Policy | O(1) | Experimental | Formal Proof Pending | O(1) |

---

# Final Complexity of Algorithm OF 1032

## Best Case

O(1)

---

## Average Case

O(1) + Complexity of Selected Policy

Since the framework dynamically selects one of the available search policies, the average-case complexity depends on

- prediction accuracy,
- input distribution,
- and the selected policy.

Accordingly, the average-case behaviour is evaluated experimentally rather than represented by a single asymptotic bound.

---

## Worst Case

O(1) + Worst Case of Selected Policy

Since the worst-case complexity of the Tail-Oriented Search Policy has not yet been formally established, the overall worst-case complexity of Algorithm OF 1032 also remains formally unproven.

---

## Space Complexity

O(1)

---

# Final Result

| Metric | Complexity |
|---------|------------|
| Best Case | **O(1)** |
| Average Case | **O(1) + Selected Policy Complexity** |
| Worst Case | **Formal Proof Pending** |
| Space Complexity | **O(1)** |

---

# Future Work

Future research will focus on deriving a formal asymptotic analysis of the Tail-Oriented Search Policy. Once established, a complete theoretical worst-case complexity for the entire Algorithm OF 1032 framework can also be formally proven.