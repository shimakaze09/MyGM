# MyGM

> **My** **G**raphics **M**ath

## Features

- Emphasizes correct algebraic concepts (groups, rings, fields, linear algebra, Euclidean space, etc.)
- Object-oriented (all methods are class methods)
- SIMD acceleration
- Optimizes code structure using single inheritance
- Provides natvis optimization for debug information

## 1. Introduction

MyGM is a mathematics library focusing on algebraic concepts, distinguishing between points, vectors, normals, colors,
etc., thereby avoiding incorrect calculations as much as possible.

Common math libraries (such as Eigen, glm) only provide a `vec` class and enable various operations (such as `+-*/`),
but from an algebraic perspective, this is not reasonable.

> Example
>
> - Points cannot be added or subtracted from each other
> - Colors have no relationship with points
> - Transformation matrices (4x4) multiply differently with normals than with regular vectors
> - When considering homogeneous coordinates, transformation matrices (4x4) multiply differently with vectors and points
> - ...

We provide `point`, `vec`, `normal`, `rgb`, etc. to distinguish different algebraic concepts and only allow reasonable
operations. This enables us to discover algebraic errors during compilation and reduce mental burden (perform different
operations based on types).

Additionally, we achieve excellent code writing through single inheritance technology, featuring:

- Function implementation reuse (different from C++20's `concept` or interfaces; they only constrain the "operations"
  supported by classes)
- Empty base class optimization

## 2. Installation

### 2.1 Environment

- [Git](https://git-scm.com/)
- VS 2019
- [CMake-GUI](https://cmake.org/) 3.16.3 or later

> Other environments can be tested; please report if successful

### 2.2 Steps

- Git

```bash
git clone https://github.com/shimakaze09/MyGM
```

- CMake-GUI

- Set source code path "Where is the source code" to the previous git clone path "<your-path-to-MyGM>"
- Set build (intermediate code) path "Where to build the binaries" to "<your-path-to-MyGM>/build"
- Click Configure button (you can make the following configurations if needed):
    - (Not checked by default) `BUILD_TEST`: Can build test cases
    - (Checked by default) `MY_USE_XSIMD`: Use SIMD acceleration
    - Modify installation path `CMAKE_INSTALL_PREFIX`, noted as "<install-path>" (default is "C:/...", requires VS 2019
      to be opened as administrator)


- Click Generate button
- Click Open Project button to open VS 2019

- In VS 2019's "Solution Explorer" window, find the "INSTALL" project, right-click, select "Generate"

### 2.3 Usage

```cpp
// main.cpp

#include <MyGM/MyGM.h>
#include <iostream>

using namespace My;

int main(){
    pointf3 p{0, 1, 2};
    pointf3 q{2, 1, 0};
    std::cout << p - q << std::endl;
}
```

```cmake
# CMakeLists.txt
project(demo_project VERSION 1.0.0)
find_package(MyGM REQUIRE)
add_executable(demo main.cpp)
target_link_libraries(demo PUBLIC My::MyGM_core)
```

## 3. Design Philosophy

To better utilize this math library, it's very important to understand its design philosophy first.

### 3.1 Algebraic Concepts

The library emphasizes correct algebraic concepts. Users might not be familiar with this aspect, but basic linear
algebra knowledge is sufficient. Here's a simple introduction to the algebraic concepts involved in the library:

- Addition `IAdd`: Operations between identical elements, having commutative property (`a+b==b+a`) and invertibility (
  `a+(-a)=0`)
- Multiplication `IMul`: Operations between identical elements, having invertibility (`a*(1/a)=1`), not necessarily
  commutative (`a*b==b*a`)
- Scalar multiplication `IScalarMul`: Operations between classes and scalars (such as `float`), having commutative
  property
- Linear `ILinear`: Addition + scalar multiplication; elements in such space become vectors
- Ring `IRing`: Addition + multiplication
- Metric `IMetric`: Also called distance
- Norm `INorm`: Vector => scalar function, generally called magnitude/length, can naturally induce metric (
  `distance(a,b) == (a-b).norm()`)
- Inner product `IInnerProduct`: Can naturally induce norm (`sqrt(dot(x, x)) == norm`)
- Affine space `IAffine`: Space with position concept; elements in such space are called points, corresponding to linear
  space, with relationships between elements of both spaces, such as `point-point => vector`, `point+vector => point`

### 3.2 Storage Types

- Array `IArray`: Ordered sequence of elements, which becomes the base class for various classes, generally
  `std::array<T, N>`, where T can be `float`, `int`, or `point`, `vec`

- Matrix `IMetric`: Array of 1D arrays

Due to differences in underlying storage types, the concrete implementation of algebraic concepts differs (abstract =>
concrete) and leads to new algebraic concepts

### 3.2.1 Arrays

When the underlying storage type is array, the following algebraic concepts can be extended:

- Euclidean (vector) space `IEuclideanV`: Linear space + inner product (`dot(a,b) == a.x*b.x + a.y*b.y + a.z*b.z`)
- Euclidean affine space `IEuclideanA`: Euclidean (vector) space corresponding affine space
- Element-wise multiplication `IArrayHadamardProduct`: `a*b=(a.x*b.x, a.y*b.y, a.z*b.z)`

These concepts have corresponding implementations when dealing with arrays, such as:

```cpp
Impl operator+(Impl a, Impl b) const {
    return {a[0]+b[0], a[1]+b[1], a[2]+b[2]};
}
```

### 3.2.2 Matrices

Since this library is used for graphics, it primarily supports 3x3 and 4x4 matrices.

The base implementation uses arrays of 1D arrays, with right-multiplication and column-major ordering, consistent with
OpenGL and DX (right-multiplication + column-major scheme is very suitable for SIMD, similarly left-multiplication +
row-major is also suitable).

### 3.3 Classes

By combining multiple algebraic concepts and adding specific type support operations, we can easily obtain various
algebraic classes. They satisfy different operations, helping users avoid errors significantly.

Currently, the main combinations (main parts) are as follows:

> ![MyGM_graph.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/MyGM_graph.jpg)

The graph contains classes such as:

- Vector [`vec`](include/MyGM/vec.h)
- Normal [`normal`](include/MyGM/normal.h): Essentially a
  bivector ([wiki](https://en.wikipedia.org/wiki/Bivector), [stackoverflow](ttps://stackoverflow.com/questions/30465573/transforming-surface-normal-vectors-and-tangent-vectors))
- Point [`point`](include/MyGM/point.h)
- Quaternion [`quat`](include/MyGM/quat.h): Limited to unit quaternions, used for rotation
- Matrix [`mat`](include/MyGM/mat.h)
- Transform [`transform`](include/MyGM/transform.h): Can represent affine transformations (translation, rotation,
  scaling) and projection transformations (orthographic projection, perspective projection)
- Color [`rgb`](include/MyGM/rgb.h)
- Scale [`scale`](include/MyGM/scale.h)

The library also includes classes such as:

- Value [`val`](include/MyGM/val.h): Addition + scalar multiplication + element-wise multiplication
- Euler angles [`euler`](include/MyGM/euler.h): roll -> pitch -> yaw, same as Unity3D
- RGBA color [`rgba`](include/MyGM/rgba.h)
- Surface vector [`svec`](include/MyGM/svec.h): Unit vector in tangent space, positive Z direction
- Homogeneous vector [`hvec`](include/MyGM/svec.h)
- Bounding box [`bbox`](include/MyGM/bbox.h): axis-aligned bounding box (AABB)
- Triangle [`triangle`](include/MyGM/triangle.h)
- Line [`line`](include/MyGM/line.h)
- Ray [`ray`](include/MyGM/ray.h)

## 4. Interfaces

Classes are composed of multiple algebraic concepts, so the key lies in grasping the interfaces of algebraic concepts.
All interfaces are located at [include/MyGM/Interfaces/]

All interfaces are class methods, convenient to use