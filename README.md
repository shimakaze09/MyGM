# MyGM

> **My** **G**raphics **M**athematics, My Graphics Mathematics Library

**Features**

- Focus on correct **algebraic** concepts (rings, linear spaces, Euclidean spaces, affine spaces, etc.)
- Object-oriented (all methods are class methods)
- Header-only implementation
- High-performance: SIMD acceleration, optimized algorithms
- Uses [single inheritance transformation technique](https://zhuanlan.zhihu.com/p/106672814) to optimize code structure (without relying on messy macros)
- Provides [natvis](https://docs.microsoft.com/en-us/visualstudio/debugger/create-custom-views-of-native-objects?view=vs-2019) support for improved debugging experience
- ...

## 1. Introduction

MyGM is a mathematics library focused on **algebraic** concepts, distinguishing between points, vectors, normals, colors, etc., to prevent incorrect calculations.

Common graphics math libraries (like Eigen, glm) only provide a `vec` class and allow it to perform various operations (like `+-*/`), but from an algebraic perspective, this isn't always appropriate.

> **Examples**
>
> - Points cannot be added to or subtracted from other points
> - Colors and points have no mathematical relation
> - Transformation matrices (4x4) multiply with normals differently than with regular vectors
> - When using homogeneous coordinates, transformation matrices (4x4) multiply with vectors and points differently
> - ...

We address this by providing separate `point`, `vec`, `normal`, `rgb` classes to distinguish different algebraic concepts, only enabling operations that make sense mathematically. This catches many algebraic errors at compile-time and reduces cognitive load (different operations are performed based on types).

Furthermore, we've implemented an excellent code structure using single inheritance techniques with the following advantages:

- Reuse of function implementations (different from C++20's `concept` or interfaces, which only constrain operations that classes support)
- Empty base class optimization
- ...

## 2. Example

```c++
#include <MyGM/MyGM.h>

using namespace My;
using namespace std;

int main() {
    transformf tsfm{ pointf3{1,1,1},
                    scalef3{2.f},
                    quatf{vecf3{1,0,0}, to_radian(90.f)} }; // T * R * S

    pointf3 p{ 1,2,3 };
    vecf3 v{ 1,1,1 };
    normalf n{ 0,1,0 };
    bboxf3 b{ p, p + v }; // min: 1 2 3, max: 2 3 4
    rayf3 r{ p, v }; // point: 1 2 3, dir: 1 1 1, tmin: EPSILON, tmax: FLT_MAX

    cout << tsfm * p << endl; // 3 -5 5
    cout << tsfm * v << endl; // 2 -2 2
    cout << tsfm * n << endl; // 0 0 0.5
    cout << tsfm * b << endl; // 3 -7 5, 5 -5 7
    cout << tsfm * r << endl; // 3 -5 5, 2 -2 2, EPSILON, FLT_MAX

    return 0;
}
```

## 3. Installation

### 3.1 Requirements

- Windows 10
- [Git](https://git-scm.com/)
- Visual Studio 2019
- [CMake-GUI](https://cmake.org/) 3.16.3 or higher
- CPU supporting SIMD extension instruction set SSE 4.1

> Other environments may work but are untested

### 3.2 Steps

> For users unfamiliar with CMake, you can directly download the CMake-installed version and header-only library from [release-0.5.8](https://github.com/shimakaze09/MyGM/releases/tag/0.5.8)
>
> Please feel free to open issues for any configuration or usage questions

- Git

  ```bash
  git clone https://github.com/shimakaze09/MyGM
  ```

- CMake-GUI

    - Set the source code path `Where is the source code` to the git clone path `<your-path-to-source-MyGM>`
    - Set the build path `Where to build the binaries` to `<your-path-to-source-MyGM>/build`
    - Click the Configure button
        - (Default unchecked) `BUILDMyGMTEST`: builds test cases if selected
        - (Default checked) `MY_USE_XSIMD`: enables SIMD acceleration
        - Change the installation path `CMAKE_INSTALL_PREFIX` to `<install-path>` (default is `C:/...` which requires **Administrator** privileges for VS 2019). Note that `<install-path>` should end with `My`, such as `<install-path>=D:/Program_Files/My`, as it will also install [MyCMake](https://github.com/shimakaze09/MyCMake) and [MyTemplate](https://github.com/shimakaze09/MyTemplate).
    - Click the Generate button
    - Click the Open Project button to open VS 2019

- In VS 2019's "Solution Explorer" window, find the `INSTALL` project, right-click, and select "Build"

- Add `<your-path-to-installed-MyGM>` to your system's `Path` environment variable (or create a new environment variable `MyGM_DIR` with value `<your-path-to-installed-MyGM>`), allowing CMake's `find_package` to correctly locate `MyGM`

- Delete `<your-path-to-source-MyGM>/build`, otherwise CMake's `FIND_PACKAGE` might locate this directory first, potentially causing errors

### 3.3 Usage

```c++
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

```CMake
# CMakeLists.txt
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(demo_project VERSION 1.0.0)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

IF(MSVC)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
ENDIF()

#find_package(MyGM 0.5.8 REQUIRED)
FIND_PACKAGE(MyGM REQUIRED)

ADD_EXECUTABLE(demo main.cpp)

TARGET_LINK_LIBRARIES(demo PUBLIC My::MyGM_core)
```

## 4. Design Philosophy

To better use this mathematics library, it's important to understand its design philosophy.

### 4.1 Algebraic Concepts

This library focuses on correct algebraic concepts. Users may not be familiar with these concepts, but basic linear algebra knowledge is sufficient.

Here is a brief introduction to the main algebraic concepts used in the library:

- Addition [`IAdd`](include/MyGM/Interfaces/IAdd.h): Operations between identical elements, with commutative property (`a+b==b+a`) and invertibility (`a+(-a)=0`)
- Multiplication [`IMul`](include/MyGM/Interfaces/IMul.h): Operations between identical elements, with invertibility (`a*(1/a)=1`), but not necessarily commutative (`a*b` may not equal `b*a`)
- Scalar Multiplication [`IScalarMul`](include/MyGM/Interfaces/IScalarMul.h): Operations between a class and a scalar (like `float`), with commutative property
- Linear Space [`ILinear`](include/MyGM/Interfaces/ILinear.h): Addition + Scalar Multiplication, elements in this space are called vectors
- Ring [`IRing`](include/MyGM/Interfaces/IRing.h): Addition + Multiplication
- Metric [`IMetric`](include/MyGM/Interfaces/IMetric.h): Also known as distance
- Norm [`INorm`](include/MyGM/Interfaces/INorm.h): A function from vector to scalar, generally called magnitude/length, can **naturally induce** a metric (`distance(a,b) == (a-b).norm()`)
- Inner Product [`IInnerProduct`](include/MyGM/Interfaces/IInnerProduct.h): Can **naturally induce** a norm (`sqrt(dot(x, x)) == norm`)
- Affine Space [`IAffine`](include/MyGM/Interfaces/IAffine.h): A space with the concept of position, elements in this space are called points, corresponds to a linear space with relationships like `point-point => vector`, `point+vector => point`

### 4.2 Underlying Storage Types

- Arrays [`IArray`](include/MyGM/Interfaces/IArray/IArray.h): Ordered sequences of elements, this is the base class for various types, generally implemented as `std::array<T, N>`, where `T` can be `float`, `int`, or even `point`, `vec`
- Matrices [`IMatrix`](include/MyGM/Interfaces/IMatrix/IMatrix.h): Arrays of one-dimensional arrays

Due to differences in underlying storage types, the specific implementations of the above algebraic concepts vary (abstraction => concretization), leading to new algebraic concepts:

#### 4.2.1 Arrays

When the underlying storage type is an array, the following algebraic concepts are introduced:

- Euclidean (Vector) Space [`IEuclideanV`](include/MyGM/Interfaces/IEuclideanV.h): Linear space + Inner Product (`dot(a,b) == a.x*b.x + a.y*b.y + a.z*b.z`)
- Euclidean Affine Space [`IEuclideanA`](include/MyGM/Interfaces/IEuclideanA.h): Affine space corresponding to a Euclidean (Vector) Space
- Element-wise Multiplication [`IArrayHadamardProduct`](include/MyGM/Interfaces/IArrayHadamardProduct.h): `a*b=(a.x*b.x, a.y*b.y, a.z*b.z)`

Each concept has specific implementations for arrays, such as:

```c++
T operator+(T a, T b) const {
    return {a[0]+b[0], a[1]+b[1], a[2]+b[2]};
}
```

#### 4.2.2 Matrices

Since this library is designed for offline rendering, real-time rendering, and games, it primarily uses float4, requiring only 3x3 and 4x4 matrices. Therefore, the library is limited to supporting only 3x3 and 4x4 matrices (with optimized implementations for matrix multiplication and inversion, like loop unrolling and SIMD acceleration, to improve performance).

Large matrix support would generally require a linear algebra library like Eigen.

The underlying implementation uses arrays of one-dimensional arrays, with right multiplication and column-major format, similar to OpenGL and DirectX (right multiplication + column-major is excellent for SIMD, as is left multiplication + row-major).

### 4.3 Classes

By combining multiple algebraic concepts and adding type-specific operations, we can easily create various algebraic classes. They support different operations, greatly helping users avoid errors.

The current combinations (main parts) are as follows:

> ![graph.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/graph.jpg)

> If the image fails to load, please use this
> link [graph.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/graph.jpg)

The graph includes classes such as:

- Vector [`vec`](include/MyGM/vec.h)
- Normal [`normal`](include/MyGM/normal.h): Essentially a bivector ([wiki](https://en.wikipedia.org/wiki/Bivector), [stackoverflow](https://stackoverflow.com/questions/30465573/transforming-surface-normal-vectors-and-tangent-vectors))
- Point [`point`](include/MyGM/point.h)
- Quaternion [`quat`](include/MyGM/quat.h): Restricted to unit quaternions for representing rotations
- Matrix [`mat`](include/MyGM/mat.h)
- Transform [`transform`](include/MyGM/transform.h): Can represent affine transformations (translation, rotation, scaling) and projective transformations (orthographic projection, perspective projection)
- Color [`rgb`](include/MyGM/rgb.h)
- Scale [`scale`](include/MyGM/scale.h)

The library also includes:

- Value [`val`](include/MyGM/val.h): Addition + Scalar Multiplication + Element-wise Multiplication
- Euler Angles [`euler`](include/MyGM/euler.h): roll -> pitch -> yaw, same as Unity3D
- Transparent Color [`rgba`](include/MyGM/rgba.h)
- Surface Vector [`svec`](include/MyGM/svec.h): Unit vector in tangent space, with z-axis as the up direction
- Homogeneous Vector [`hvec`](include/MyGM/svec.h)
- Bounding Box [`bbox`](include/MyGM/bbox.h): Axis-aligned bounding box (AABB)
- Triangle [`triangle`](include/MyGM/triangle.h): Three `point`s
- Line [`line`](include/MyGM/line.h): `point` + `direction`
- Ray [`ray`](include/MyGM/ray.h): Line with added `t min` and `t max`

## 5. Interfaces

Classes are composed of multiple algebraic concepts, so the key is to understand the interfaces of these concepts, which are located in [include/MyGM/Interfaces/](include/MyGM/Interfaces/).

All interfaces are class methods for ease of use. In most cases, you can use your IDE's code suggestion feature (like VS2019's IntelliSense) to explore the interfaces.

Additionally, the library provides common functions/algorithms in the rendering field, such as intersection (in `line` and `ray`), [sampling](include/MyGM/sample.h), [materials](include/MyGM/material.h), etc.

## 6. SIMD

The library supports SIMD, requiring only SSE instruction support. It uses xsimd as a wrapper for SSE instructions, but in most cases, it directly uses SSE instructions.

The main accelerated class is `float4`, including `vecf4`, `pointf4`, etc.

Note that `float3` does not have SIMD acceleration, which ensures `sizeof(float3) == 3*sizeof(float)`. Some math libraries achieve SIMD acceleration for `float3` by using `__m128`, but this makes `sizeof(float3) == 4*sizeof(float)`. Currently, you can explicitly convert `float3` to `float4` to get acceleration.

Accelerated parts include:

- `+-*/ ...`
- `min/max/min_component/max_component/abs/sin/cos/...`
- `transform * float4/bbox/transform`
- `transform inverse`
- Intersection of `ray` with `sphere/triangle/bbox`
- `dot/cross` for `float3` (by extending to `float4` and using `float4::dot3` and `float4::cross3`)
- ...

## 7. Natvis

Generic programming introduces many single inheritance levels during debugging. This library uses a single inheritance transformation technique with significant inheritance depth, making it difficult to view class member variables in an IDE.

> **Example**
>
> ![TextBox default visualization](https://docs.microsoft.com/en-us/visualstudio/debugger/media/dbg_natvis_textbox_default.png?view=vs-2019)
>
> > If the image fails to load, please use this
> > link [TextBox default visualization](https://docs.microsoft.com/en-us/visualstudio/debugger/media/dbg_natvis_textbox_default.png?view=vs-2019)

When using `find_package(MyGM REQUIRED)`, a project containing `MyGM_<VERSION>.natvis` is automatically added to your solution, enabling natvis support for other projects ([VS2019 supports multiple ways to introduce natvis](https://docs.microsoft.com/en-us/visualstudio/debugger/create-custom-views-of-native-objects?view=vs-2019#BKMK_natvis_location), but this is currently the most suitable method I can think of).

## Future Features

- [x] Lighter single inheritance transformation technique (reduced coding overhead), further improving compilation speed
- [ ] Provide `config.h` for customizing features
- [ ] `xfloat3`: `float3` class using `__m128` for better SIMD support, with size of `4*sizeof(float)`, including `xpoint`, `xvec`, `xrgb`, ...
- [ ] CUDA support
- [ ] ...