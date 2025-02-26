# Image-Compression

## Overview

Image-Compression is a tool designed to compress images into a custom ".samuel" file format, aiming to store images more compactly. This project combines interests in image processing and software engineering, providing a platform to practice building a larger project with multiple interdependent parts.

## Features

- **Custom Compression Format**: Compress images into a custom ".samuel" file format.
- **Domain Transformation**: Transform images to a new domain (e.g., Fourier domain) for efficient compression.
- **Multiple Compression Levels**: Support for various compression levels to balance quality and file size.
- **Unit Testing**: Comprehensive unit tests to ensure code reliability.
- **OO Design**: Object-oriented design principles for maintainable and scalable code.
- **Interface**: Command-line interface for easy interaction with the tool.

## Goals

- Practice C++ programming.
- Implement object-oriented design.
- Develop unit tests for code reliability.
- Create a user-friendly interface.

## Compression Strategy

The tool transforms images into a new domain where only a few important values are retained, discarding the rest. This process is similar to the JPEG compression technique. The retained values are then used to reconstruct the image, achieving a state close to the original.



## Code Documentation 

here is an figure of the class diagram (WIP)

![Class Diagram](class_diagram.png)

## **Discrete Cosine Transform (DCT) Implementation**

### **Overview**
This section explains the **Discrete Cosine Transform (DCT)** and its implementation in `DCT.cpp`.  
DCT is widely used in image and signal compression (e.g., **JPEG compression**) to convert signals from the **spatial domain** to the **frequency domain**, allowing more efficient data representation.

---

### **1. Mathematical Foundation**

#### **DCT-II Transformation**

The **DCT-II**, which is commonly used in compression algorithms, transforms an input signal $ x[n] $ of length $ N $ into frequency coefficients $ X[k] $:

$$
X[k] = \sum_{n=0}^{N-1} x[n] \cdot C(k, n)
$$

Where:

$$
C(k, n) = \alpha(k) \cos \left( \frac{\pi (2n + 1) k}{2N} \right)
$$

The normalization factor $ \alpha(k) $ is:

$$
\alpha(k) =
\begin{cases}
\sqrt{\frac{1}{N}}, & k = 0 \\
\sqrt{\frac{2}{N}}, & k \geq 1
\end{cases}
$$

This equation tells us how to compute the frequency coefficients $ X[k] $ by taking a weighted sum of the input signal $ x[n] $, with each weight being a cosine function at the $ k^{th} $ frequency.

#### **Inverse DCT (IDCT)**

The **Inverse DCT (IDCT)** reconstructs the original signal from the frequency coefficients:

$$
x[n] = \sum_{k=0}^{N-1} X[k] \cdot C(k, n)
$$

---

### **2. Matrix Representation in Code**

In the code, the DCT operation is implemented using **matrix-vector multiplication**. This means that the DCT is represented as a matrix, where each element of the matrix corresponds to a **cosine basis function**. 

The **DCT matrix** is computed as follows:

$$
\text{DCTMatrix}[i][j] = \alpha(i) \cdot \cos \left( \frac{\pi (2j + 1) i}{2N} \right)
$$

Where:
- $ \text{DCTMatrix}[i][j] $ corresponds to the **element at the $i^{th}$ row and $j^{th}$ column** in the matrix.
- $ \alpha(i) $ is the normalization factor for the $i^{th}$ row.
- $ \cos \left( \frac{\pi (2j + 1) i}{2N} \right) $ is the cosine function determining the transformation for each coefficient.

This matrix transforms the input signal from the **spatial domain** to the **frequency domain**.

In the implementation, the input signal is treated as a vector $ x $ of length $ N $, and the **DCT matrix** is multiplied by this vector to obtain the transformed frequency coefficients:

$$
X = \text{DCTMatrix} \times x
$$

Similarly, the **inverse DCT** is performed by multiplying the **inverse of the DCT matrix** (which is the transpose of the original matrix) with the frequency coefficients to recover the signal:

$$
x = (\text{DCTMatrix})^{T} \times X
$$



## Dependencies

- CMake 3.11 or higher
- OpenCV
- GoogleTest



## References

- [JPEG Compression Video](https://www.youtube.com/watch?v=0me3guauqOU)