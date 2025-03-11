# Image-Compression

# Introduction

To make the most of my time between assignments, I took on this personal project that combined my interest in image processing with software development. I developed a lossy image compression tool from scratch in C++, inspired by the techniques used in the JPEG standard. This involved implementing the discrete cosine transform, various encoding techniques, and creating a custom binary file format, which I named “.samuel,” to store the compressed data.
Beyond the nice mathematical of image compression, this project also deepened my understanding of software development as it grew in complexity. I applied design patterns and set up automated unit testing using GitHub Actions and CMake.

# Features

- **Custom Compression Format**: Compress images into a custom ".samuel" file format.
- **Domain Transformation**: Transform images to a new domain (e.g., Fourier domain) for efficient compression.
- **Multiple Compression Levels**: Support for various compression levels to balance quality and file size.
- **Unit Testing**: Comprehensive unit tests to ensure code reliability.
- **OO Design**: Object-oriented design principles for maintainable and scalable code.
- **Interface**: Command-line interface for easy interaction with the tool (WIP).

# Goals

- Practice C++ programming.
- Implement object-oriented design.
- Develop unit tests for code reliability.
- Create a user-friendly interface.

# Compression Strategy
```

┌─────────────┐     ┌──────────────────────┐     ┌─────────┐    ┌────────────┐
│ Input Image │ --> │ Transformer/compress │ --> │ Encoder │ -->| Compressed │
└─────────────┘     └──────────────────────┘     └─────────┘    └────────────┘
      |                                                               ^
      |                                                               |                   
      └───────────────────────────────────────────────────────────────┘
                                 Decompression
```
In very simple terms, lossy compression is based on the fact that we can transform an image into a new domain. In this domain, only a few data points have a significant value. This means that we can discard all other data points and still reconstruct the image to a reasonable level.

The best-known of such transforms is the Fourier Transform (FT). The FT can deconstruct a signal into a weighted sum of sine and cosine functions. The weights are called the Fourier coefficients. Other transforms with similar properties include the cosine transform (also used in this project and JPEG) as well as wavelet transforms and many others.

In the image below, an example is given of compression using the Fourier Transform. You can see that most coefficients close to the edge (high frequencies) are close to zero. So we can set them to zero and still reconstruct the image. It's easy to see how this could be used to store images efficiently.

![Fourier compression](lowpass.gif)

One difference between this example and my implementation is that I don’t set an area of the image to zero, but I set the lowest values to zero. This is to retain high-frequency coefficients that are significant.

## Fourier Compression

The first approach I implemented was a naive Fourier-based compression. Here, I transformed the image to the Fourier domain (using OpenCV's DFT implementation), resulting in a two-channel array of real and imaginary numbers of the same size as the original image.

Thereafter, I calculated the magnitude of each coefficient. Next, I set a percentage of the lowest-magnitude coefficients to zero. This way, we end up with a Fourier domain image where only a small part of the significant coefficients is retained.

This is nice, but we still have an image of the same size, just with a lot of zeros. So now we need to efficiently store the information. Here, I chose a {Column, Row, Value} format. For every nonzero element, we store its location and value (a complex value in the case of the FT).

## Discret Cosine transform Compression

Secondly, I implemented the Discrete Cosine Transform (DCT) compression, a core component of the JPEG standard, and I implemented the DCT from scratch.

The DCT is closely related to the Discrete Fourier Transform (DFT), but it uses only cosine functions as basis functions. this results in only real coefficients which simplifies the representation. Both the DCT and DFT can compact image infromation; however, the DCT’s exclusive use of cosine functions often results in a more concentrated infromation distribution in the low-frequency components for many natural images. 


### Mathematics 

The **DCT**, is defined as follows, transforms an input signal $ x[n] $ of length $ N $ into frequency coefficients $ X[k] $:

$$
X[k] = \sum_{n=0}^{N-1} x[n] \cdot  \alpha(k) \cos \left( \frac{\pi (2n + 1) k}{2N} \right)
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

### Implementation 

The whole DCT compression has a view more steps then the DFT approach.

1. Cut image into 8x8 blocks
2. DCT
3. Perform quantisation
4. ZigZagEndode the transforme image blocks
5. Run lenght encoding

#### 1. Cut image into 8x8 blocks

As opposed to the to the DFT we will perfrom the DCT on blocks of the image instead of the image as a whole. So the first step is to cut the image up into the blocks, where the image may need to be zero-padded.

#### 2. DCT

Then we DCT each image block, were we use the fact that the DCT is sperable in it's dimentions so we can perform a 1D DCT on ech image row and the perform another 1D DCT column wise.

#### 3. Perform quantisation

Here we also divert from the DFT approch where we just removed the smallest coeffcients. Here we devide the transformed 8x8 image block by a so called quantiation tabel. these tabels have been emoricle foud to have the least amout of negative perseptible effect on the compressed image.

Below we see an example of a quantisation tabel, as you can se in the upper right values are low and in the bottum left values are high. this is to remove more high frecuancy componets and leave the lower frecuancies allown.  

```cpp
const std::vector<std::vector<int>> QuantizationTable::highCompressionTable = {
    {8, 6, 6, 8, 12, 20, 25, 30},
    {6, 6, 7, 10, 13, 29, 30, 28},
    {7, 7, 8, 12, 20, 28, 34, 28},
    {7, 9, 12, 16, 26, 44, 40, 31},
    {9, 12, 20, 28, 33, 55, 52, 39},
    {12, 18, 28, 32, 41, 52, 57, 46},
    {24, 32, 39, 44, 52, 61, 60, 50},
    {36, 46, 48, 50, 56, 50, 52, 49}};
```

#### 4. ZigZagEndode the transforme image blocks

Now that we have our transformed an quantised image blocks we need to store them efficenly. to do this we want to order the coeffcents from high to low frequanecy. this means we travers the image blok in a zig zag pattern as shown in the snipit below

```cpp
imageBlock = {{1,  2,  6,   7},
              {3,  5,  8,  13},
              {4,  9,  12, 14},
              {10, 11, 15, 16}};

result = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}
```

#### 5. Run lenght encoding

Now that we have orderd the image blocks in to 


## Software Design 

I tried to structure the code using the strategy pattern where there are now two strategys DFT and DCT. 

![Class Diagram](class_diagram.svg)

## Dependencies

- CMake 3.11 or higher
- OpenCV
- GoogleTest



## References

- [JPEG Compression Video](https://www.youtube.com/watch?v=0me3guauqOU)