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

## Usage

### Building the Project

To build the project, use CMake:

```sh
mkdir build
cd build
cmake ..
make
```

### Running the Tool

To compress an image:

```sh
./image-compression <input_image> <output_file> <compression_level>
```

### Compression Levels

- `low`: Low compression, high quality.
- `medium`: Medium compression, balanced quality and file size.
- `high`: High compression, reduced quality.
- `very_high`: Very high compression, significantly reduced quality.
- `ultra_high`: Ultra high compression, minimal quality.

## Testing

Run the unit tests using:

```sh
./run_tests
```

## Dependencies

- CMake 3.11 or higher
- OpenCV
- GoogleTest

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests.

## License

This project is licensed under the MIT License.

## References

- [JPEG Compression Video](https://www.youtube.com/watch?v=0me3guauqOU)