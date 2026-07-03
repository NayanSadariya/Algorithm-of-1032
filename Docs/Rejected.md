# Rejected Ideas

This document records every major idea considered during the development of Algorithm OF 1032 but later rejected. These ideas are preserved for future research and to document the design process.

---

# R1 - Fixed Jump Sizes

## Idea

Use predefined jump percentages such as:

- 50%
- 20%
- 10%

depending on the remaining search interval.

## Reason for Rejection

The thresholds were completely heuristic.

There was no mathematical justification for selecting these percentages, making the algorithm difficult to analyze and generalize.

---

# R2 - Binary Search After Every Jump

## Idea

Perform one adaptive jump and immediately switch to Binary Search inside the discovered block.

## Reason for Rejection

This removed the adaptive nature of the algorithm.

The algorithm quickly became a variation of Binary Search instead of maintaining its own identity.

---

# R3 - Partition Threshold

## Idea

Switch to Binary Search whenever the remaining interval became less than a fixed percentage of the original array.

Example:

10% of original size.

## Reason for Rejection

The threshold was arbitrary.

Different array sizes required different thresholds, making the approach difficult to justify theoretically.

---

# R4 - Confidence-Based Jump Formula (Version 1)

## Idea

Compute a confidence value and directly convert it into a jump distance.

## Reason for Rejection

The confidence calculation effectively duplicated the behaviour of the Progress-Based policy.

It introduced additional calculations without creating genuinely different search behaviour.

---

# R5 - Future Cost Formula

## Idea

Estimate the future search cost and choose jumps that minimized that estimate.

## Reason for Rejection

The derived equation mathematically simplified into behaviour almost identical to Selection Policy 1.

The idea was therefore not considered a distinct policy.

---

# R6 - Aggressiveness Policy

## Idea

Assign an aggressiveness score to determine whether the algorithm should perform larger or smaller jumps.

## Reason for Rejection

Aggressiveness depended entirely on search progress, making it another reformulation of the Progress-Based policy rather than a new approach.

---

# R7 - Self-Evaluating Policy

## Idea

Measure whether the previous jump was good or bad and adapt future jumps accordingly.

## Reason for Rejection

The evaluation could only be performed after the comparison.

The information was unavailable when selecting the next comparison point, making it unsuitable as a true Selection Policy.

---

# R8 - Decision Quality Metric

## Idea

Develop a mathematical score describing the quality of every comparison before performing it.

## Reason for Rejection

Every proposed formulation depended on information unavailable before the comparison or reduced to already existing metrics.

No practical formulation was obtained.

---

# R9 - Candidate Evaluation Policy

## Idea

Generate multiple candidate positions from different policies and choose the best one.

## Reason for Rejection

There was no objective method to evaluate candidate quality before performing the comparison.

The policy therefore required unavailable information.

---

# R10 - Uniform Expected Utility

## Idea

Assume every target position is equally probable and choose the comparison point with maximum expected reduction.

## Reason for Rejection

Under a uniform probability assumption, the expected reduction became identical for all candidate positions.

The policy therefore provided no useful decision criterion.

---

# R11 - Pure Hybrid Policy

## Idea

Create a third policy that switched between Policy 1 and Policy 2 using manually selected thresholds.

## Reason for Rejection

The switching conditions were entirely heuristic.

The idea was postponed until sufficient benchmark data could justify the thresholds experimentally.

---

# R12 - Policy Selection by Actual Target Position

## Idea

Choose different policies depending on whether the target was near the beginning, middle or end of the array.

## Reason for Rejection

The actual target position is unknown before the search begins.

Using this information would make the algorithm impossible to implement.

---

# R13 - Relative Position Estimation as a Search Algorithm

## Idea

Directly search using the estimated target position.

## Reason for Rejection

This approach closely resembled Interpolation Search.

Instead, the relative position estimate was retained only as a policy-selection mechanism for future versions.

---

# Current Status

The current implementation (Version 4) contains:

- Selection Policy 1
- Selection Policy 2
- Selection Policy 3 
- Relative Position Estimation
- Threshold-Based Policy Selection

Future improvements will only be accepted if they solve a limitation not already addressed by the existing policies.