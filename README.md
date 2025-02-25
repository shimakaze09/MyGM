# MyGM

> **My** **G**raphics **M**ath Graphics Mathematics Library

## Features

- Emphasizes correct algebraic concepts (groups, rings, fields, linear algebra, Euclidean spaces, etc.)
- Object-oriented (all methods are member functions)
- High performance: SIMD acceleration, optimal algorithms
- Optimize code structure using single inheritance (avoiding ugly macros)
- Provide [natvis](https://docs.microsoft.com/en-us/visualstudio/debugger/create-custom-views-of-native-objects?view=vs-2019)
optimization for debug information

## 1. Introduction

MyGM is a mathematics library focused on algebraic concepts, distinguishing between points, vectors, normals, colors,
etc., thereby avoiding incorrect calculations as much as possible.

Common math libraries (such as Eigen, glm) only provide a vec class and enable various operations (such as +-* / etc.),
but from an algebraic perspective, this is not reasonable.

> **Examples**
>
> - Points cannot be added or subtracted from each other
> - Colors have no relation to points
> - Transformation matrices (4x4) multiplied with normals differ from regular vectors
> - When considering homogeneous coordinates, transformation matrices (4x4) multiplied with vectors and points differ
> - ...

We provide point, vec, normal, rgb, etc. to distinguish different algebraic concepts and only allow reasonable
operations. This allows us to discover various algebraic errors at compile-time while reducing mental burden (performing
different operations based on types).

Additionally, we implement excellent code writing through single inheritance techniques with the following
characteristics:

- Function implementation reuse (different from C++20's concept or interfaces, which only constrain the "operations"
  supported by classes)
- Empty base class optimization

## 2. Installation

### 2.1 Environment

- Win10
- [Git](https://git-scm.com/)
- VS 2019
- [CMake-GUI](https://cmake.org/) 3.16.3 or later
- Supports SIMD instruction set extensions SSE 4.1

> Other environments can be self-tested; please notify us if successful

### 2.2 Steps

> These are all basic operations of CMake, maybe someone is encountering it for the first time, I'll introduce them in
> detail here

- Git

```bash
git clone https://github.com/shimakaze09/MyGM
```

- CMake-GUI- Set source code path "Where is the source code" to the git clone path "<your-path-to-source-MyGM>"

    - Set build path "Where to build the binaries" to "<your-path-to-source-MyGM>/build"
    - Click Configure button (you can perform the following configurations if needed):
        - (`BUILD_TEST`: Build test cases [default unchecked])
        - (`MY_USE_XSIMD`: Use SIMD acceleration [default checked])
        - Modify installation path `CMAKE_INSTALL_PREFIX`, noted as `<install-path>` (default is `C:/...`, requiring
          administrator privileges for VS 2019)

    - Click Generate button
    - Click Open Project button to open VS 2019

- In VS 2019's "Solution Explorer" window, find the "INSTALL" project, right-click, select "Generate"

- Add `<your-path-to-installed-MyGM>` to the system environment variable Path (or create a new environment variable
  named MyGM_DIR and set its value to `<your-path-to-installed-MyGM>`), so that CMake's find_package can correctly
  locate MyGM

- Delete `<your-path-to-source-MyGM>/build`, otherwise CMake's find_package will prioritize locating it here, which
  might cause errors

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
PROJECT(demo_project VERSION 1.0.0)
FIND_PACKAGE(MyGM REQUIRED)
ADD_EXECUTABLE(demo main.cpp)
TARGET_LINK_LIBRARIES(demo PUBLIC My::MyGM_core)
```

## 3. Design Philosophy

To better utilize this math library, it's essential to understand its design philosophy.

### 3.1 Algebraic Concepts

The library emphasizes correct algebraic concepts. Users likely won't be familiar with these aspects, but knowing basic
linear algebra is sufficient.

Below is a brief introduction to the algebraic concepts involved in the library:

- Addition [`IAdd`](include/MyGM/Interfaces/IAdd.h): Operations between identical elements with commutativity (
  `a+b==b+a`) and invertibility (`a+(-a)=0`)
- Multiplication [`IMul`](include/MyGM/Interfaces/IMul.h): Operations between identical elements with invertibility (
  `a*(1/a)=1`), not necessarily commutative (`a*b==b*a`)
- Scalar multiplication [`IScalarMul`](include/MyGM/Interfaces/IScalarMul.h): Operations between classes and scalars (
  such as float) with commutativity
- Linear [`ILinear`](include/MyGM/Interfaces/ILinear.h): Addition + scalar multiplication; elements become vectors
- Ring [`IRing`](include/MyGM/Interfaces/IRing.h): Addition + multiplication
- Metric [`IMetric`](include/MyGM/Interfaces/IMetric.h): Also called distance
- Norm [`INorm`](include/MyGM/Interfaces/INorm.h): Vector => scalar function, generally called size/length, naturally
  induces metric (`distance(a,b) == (a-b).norm()`)
- Inner product [`IInnerProduct`](include/MyGM/Interfaces/IInnerProduct.h): Naturally induces norm (
  `sqrt(dot(x, x)) == norm`)
- Affine space [`IAffine`](include/MyGM/Interfaces/IAffine.h): Space with position concept; elements are called points;
  corresponds to linear space with associated elements, such as `point-point => vector`, `point+vector => point`

### 3.2 Underlying Storage Types

- Array [`IArray`](include/MyGM/Interfaces/IArray.h): Ordered sequence of elements; serves as base class for various
  classes; typically `std::array<T, N>`, where T can be float, int, or point, vec
- Matrix [`IMetric`](include/MyGM/Interfaces/IMetric.h): Array of 1D arrays

Due to different underlying storage types, the concrete implementations of algebraic concepts differ (abstract =>
concrete), leading to new algebraic concepts.

### 3.2.1 Arrays

When the underlying storage type is an array, the following algebraic concepts emerge:

- Euclidean (Vector) Space [`IEuclideanV`](include/MyGM/Interfaces/IEuclideanV.h): Linear space + inner product (
  `dot(a,b) == a.x*b.x + a.y*b.y + a.z*b.z`)
- Euclidean Affine Space [`IEuclideanA`](include/MyGM/Interfaces/IEuclideanA.h): Euclidean (vector) space corresponding
  affine space
- Element-wise multiplication [`IArrayHadamardProduct`](include/MyGM/Interfaces/IArrayHadamardProduct.h):
  `a*b=(a.x*b.x, a.y*b.y, a.z*b.z)`

These concepts have corresponding implementations when applied to arrays, such as:

```cpp
T operator+(T a, T b) const {
    return {a[0]+b[0], a[1]+b[1], a[2]+b[2]};
}
```

### 3.2.2 Matrices

Since this library is used for graphics, it primarily supports 3x3 and 4x4 matrices.

The library implements matrices through 1D arrays of arrays, right-multiplication, column-major, consistent with OpenGL
and DX (right-multiplication + column-major is highly suitable for SIMD, similarly left-multiplication + row-major is
also suitable).

### 3.3 Classes

By combining multiple algebraic concepts and adding specific type support operations, we can easily obtain various
algebraic classes. They satisfy different operations, greatly helping users avoid errors.

Currently, the main combinations (major parts) are as follows:

> ![MyGM_graph.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/MyGM_graph.jpg)

> If the image fails to load, please use this
> link [MyGM_graph.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/MyGM_graph.jpg)

The graph contains the following classes:

- Vector [`vec`](include/MyGM/vec.h)
- Normal [`normal`](include/MyGM/normal.h): Essentially
  bivector ([wiki](https://en.wikipedia.org/wiki/Bivector), [stackoverflow](https://stackoverflow.com/questions/30465573/transforming-surface-normal-vectors-and-tangent-vectors))
- Point [`point`](include/MyGM/point.h)
- Quaternion [`quat`](include/MyGM/quat.h): Limited to unit quaternions, used for rotation
- Matrix [`mat`](include/MyGM/mat.h)
- Transform [`transform`](include/MyGM/transform.h): Can represent affine transformations (translation, rotation,
  scaling) and projection transformations (orthographic projection, perspective projection)
- Color [`rgb`](include/MyGM/rgb.h)
- Scale [`scale`](include/MyGM/scale.h)

The library also contains classes:

- Value [`val`](include/MyGM/val.h): Addition + scalar multiplication + element-wise multiplication
- Euler angles [`euler`](include/MyGM/euler.h): roll -> pitch -> yaw, same as Unity3D
- Color with alpha [`rgba`](include/MyGM/rgba.h)
- Surface vector [`svec`](include/MyGM/svec.h): Unit vectors in tangent space, up direction is z-axis
- Homogeneous vector [`hvec`](include/MyGM/svec.h)
- Bounding box [`bbox`](include/MyGM/bbox.h): axis-aligned bounding box (AABB)
- Triangle [`triangle`](include/MyGM/triangle.h)
- Line [`line`](include/MyGM/line.h)
- Ray [`ray`](include/MyGM/ray.h)

## 4. Interfaces

Classes are composed of multiple algebraic concepts, so the key lies in grasping the interfaces. All algebraic concepts
are located in [include/MyGM/Interfaces/](include/MyGM/Interfaces/).

All interfaces are member functions, convenient to use, and most situations allow utilizing IDE code completion
functionality (such as VS2019's intellisense) to query interfaces.

Additionally, common graphics algorithms/functions are provided, such as intersection (located in line, ray), sampling,
materials, etc.

## 5. SIMD

The library supports SIMD, requiring only SSE instruction support, using xsimd as the wrapper class for SSE
instructions, though most cases directly use SSE instructions.

The main accelerated classes are `float4`, including `vecf4`, `pointf4`, etc.

Accelerated parts include:

- `+-*/ ...`
- `min/max/min_component/max_component/abs/sin/cos/...`
- `transform * float4/bbox/transform`
- `transform inverse`
- Intersection between `ray` and `sphere/triangle/bbox`
- `dot/cross` of `float3` (requires extension to `float4` and uses `float4::dot3` and `float4::cross3`)

### 6. Natvis
During debugging, generic programming introduces extensive single inheritance relationships. This library employs single inheritance technology with deep inheritance hierarchies, making it difficult to view class member variables in IDEs.

> **Example**
>
> ![TextBox default visualization](https://docs.microsoft.com/en-us/visualstudio/debugger/media/dbg_natvis_textbox_default.png?view=vs-2019)

We can use the natvis feature of VS2019 to implement customized views

![natvis_demo.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/natvis_demo.jpg)

When using `FIND_PACKAGE(MyGM REQUIRED)`, a project will be automatically added to the solution, containing `MyGM_<VERSION>.natvis`, so that other projects can support natvis ([VS2019 supports multiple ways to introduce natvis](https://docs.microsoft.com/en-us/visualstudio/debugger/create-custom-views-of-native-objects?view=vs-2019#BKMK_natvis_location), but this is the most suitable way I can think of at the moment).
