# MyGM

> **My** **G**raphics **M**athematics

**Features**

- Emphasizes correct algebraic concepts (rings, linear, Euclidean space, affine space, etc.)
- Object-oriented design with all methods implemented as member functions
- Header-only library for easy integration
- High performance through SIMD acceleration and optimal algorithms
- Clean code structure using single inheritance (eliminating ugly macros)
- Enhanced debugging with [natvis](https://docs.microsoft.com/en-us/visualstudio/debugger/create-custom-views-of-native-objects?view=vs-2019) support
- ...

## 1. Introduction

MyGM is a mathematics library that focuses on proper algebraic concepts by clearly distinguishing between points, vectors, normals, colors, and other mathematical entities. This approach helps prevent incorrect calculations at the type level.

Most popular graphics math libraries (like Eigen and GLM) provide only generic vector classes with various operations (such as +, -, *, /), which is mathematically imprecise from an algebraic perspective.

> **Examples**
>
> - Points should not be added to or subtracted from each other
> - Colors are semantically distinct from spatial points
> - Normals transform differently than vectors when multiplied by a 4x4 matrix
> - In homogeneous coordinates, 4x4 matrices transform points and vectors differently
> - ...

By providing separate types for point, vector, normal, rgb, and other concepts, MyGM enforces algebraically correct operations. This design catches many errors at compile time rather than runtime, while also clarifying intent in your code (with operations naturally determined by types).

Our implementation leverages single inheritance techniques to achieve:

- Efficient function implementation reuse (beyond what C++20 concepts or interfaces offer, which only define supported operations)
- Empty base class optimization for minimal memory overhead
- ...

## 2. Demonstrate

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

### 3.1 Environment

- Windows 10
- [Git](https://git-scm.com/)
- Visual Studio 2019
- [CMake-GUI](https://cmake.org/) 3.16.3 or later
- CPU with SSE 4.1 instruction set support

> Other environments may work but haven't been extensively tested.

### 3.2 Steps

- Clone the repository:

```bash
git clone https://github.com/shimakaze09/MyGM
```

- CMake-GUI: Set the source code path "Where is the source code" to the git clone path "<your-path-to-source-MyGM>"

    - Set the build path "Where to build the binaries" to "<your-path-to-source-MyGM>/build"
    - Click the Configure button:
        - (`BUILD_TEST`: Build test cases [default unchecked])
        - (`MY_USE_XSIMD`: Use SIMD acceleration [default checked])
        - Modify the installation path `CMAKE_INSTALL_PREFIX`, record it as `<install-path>` (the default is `C:/...`,
          you need to open VS 2019 as an **administrator**), note that `<install-path>` should end with `My`, such as
          `<install-path>=D:/Program_Files/My`, because [MyCMake](https://github.com/shimakaze09/MyCMake)
          and [MyTemplate](https://github.com/shimakaze09/MyTemplate) will be installed at the same time.
    - Click the Generate button
    - Click the Open Project button to open VS 2019

- In VS 2019's "Solution Explorer" window, find the "INSTALL" project, right-click, and select "Generate"

- Add `<your-path-to-installed-MyGM>` to the system environment variable Path (or create a new environment variable
  named MyGM_DIR and set its value to `<your-path-to-installed-MyGM>`), so that CMake's find_package can correctly
  locate MyGM

- Delete `<your-path-to-source-MyGM>/build`, otherwise CMake's find_package will prioritize locating it here, which
  might cause errors

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

```cmake
# CMakeLists.txt
PROJECT(demo_project VERSION 1.0.0)
FIND_PACKAGE(MyGM REQUIRED)
ADD_EXECUTABLE(demo main.cpp)
TARGET_LINK_LIBRARIES(demo PUBLIC My::MyGM_core)
```

## 4. Design Philosophy

To better utilize this math library, it's essential to understand its design philosophy.

### 4.1 Algebraic Concepts

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

### 4.2 Underlying Storage Types

- Array [`IArray`](include/MyGM/Interfaces/IArray/IArray.h): Ordered sequence of elements; serves as base class for
  various
  classes; typically `std::array<T, N>`, where T can be floated, int, or point, vec
- Matrix [`IMetrix`](include/MyGM/Interfaces/IMatrix/IMatrix.h): Array of 1D arrays

Due to different underlying storage types, the concrete implementations of algebraic concepts differ (abstract =>
concrete), leading to new algebraic concepts.

### 4.2.1 Arrays

When the underlying storage type is an array, the following algebraic concepts emerge:

- Euclidean (Vector) Space [`IEuclideanV`](include/MyGM/Interfaces/IEuclideanV.h): Linear space + inner product (
  `dot(a,b) == a.x*b.x + a.y*b.y + a.z*b.z`)
- Euclidean Affine Space [`IEuclideanA`](include/MyGM/Interfaces/IEuclideanA.h): Euclidean (vector) space corresponding
  affine space
- Element-wise multiplication [`IArrayHadamardProduct`](include/MyGM/Interfaces/IArrayHadamardProduct.h):
  `a*b=(a.x*b.x, a.y*b.y, a.z*b.z)`

These concepts have corresponding implementations when applied to arrays, such as:

```c++
T operator+(T a, T b) const {
    return {a[0]+b[0], a[1]+b[1], a[2]+b[2]};
}
```

### 4.2.2 Matrices

Since this library is used for offline rendering, real-time rendering, games, etc., basically only float4 is used, so
only 3x3 and 4x4 matrices are needed. Therefore, this library is also limited to supporting only 3x3 and 4x4 matrices (
and specializing the implementation of matrix multiplication and inverse, such as loop unrolling and simd acceleration
to improve performance).

The library implements matrices through 1D arrays of arrays, right-multiplication, column-major, consistent with OpenGL
and DX (right-multiplication + column-major is highly suitable for SIMD, similarly left-multiplication + row-major is
also suitable).

### 4.3 Classes

By combining multiple algebraic concepts and adding specific type support operations, we can easily obtain various
algebraic classes. They satisfy different operations, greatly helping users avoid errors.

Currently, the main combinations (major parts) are as follows:

> ![graph.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/graph.jpg)

> If the image fails to load, please use this
> link [graph.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/graph.jpg)

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
- Triangle [`triangle`](include/MyGM/triangle.h): three `point`
- Line [`line`](include/MyGM/line.h): `point` + `direction`
- Ray [`ray`](include/MyGM/ray.h): added `t min` and `t max` for the line

## 5. Interfaces

Classes are composed of multiple algebraic concepts, so the key lies in grasping the interfaces. All algebraic concepts
are located in [include/MyGM/Interfaces/](include/MyGM/Interfaces/).

All interfaces are member functions, convenient to use, and most situations allow utilizing IDE code completion
functionality (such as VS2019's intellisense) to query interfaces.

In addition, common functions/algorithms in the rendering field are also provided, such as intersection (located in
`line`, `ray`), [sampling](include/MyGM/sample.h), [materials](include/MyGM/material.h), etc.

## 6. SIMD

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
- ...

### 7. Natvis

During debugging, generic programming introduces extensive single inheritance relationships. This library employs single
inheritance technology with deep inheritance hierarchies, making it difficult to view class member variables in IDEs.

> **Example**
>
> ![TextBox default visualization](https://docs.microsoft.com/en-us/visualstudio/debugger/media/dbg_natvis_textbox_default.png?view=vs-2019)
>
> > If the image fails to load, please use this
> >
link [TextBox default visualization](https://docs.microsoft.com/en-us/visualstudio/debugger/media/dbg_natvis_textbox_default.png?view=vs-2019)

We can use the natvis feature of VS2019 to implement customized views

![natvis_demo.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/natvis_demo.jpg)

> If the image fails to load, please use this
> link [natvis_demo.jpg](https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/natvis_demo.jpg)

When using `FIND_PACKAGE(MyGM REQUIRED)`, a project will be automatically added to the solution, containing
`MyGM_<VERSION>.natvis`, so that other projects can support
natvis ([VS2019 supports multiple ways to introduce natvis](https://docs.microsoft.com/en-us/visualstudio/debugger/create-custom-views-of-native-objects?view=vs-2019#BKMK_natvis_location),
but this is the most suitable way I can think of at the moment).

## Future Features

- [x] Lighter-weight single inheritance technology (reducing coding overhead), further accelerating compilation speed
- [ ] Provide `config.h` for easy feature customization
- [ ] `xfloat3`: A `float3` class using `__m128` as underlying implementation for better SIMD support, with size of `4*sizeof(float)`, including `xpoint`, `xvec`, `xrgb`, etc.
- [ ] Support for CUDA
- [ ] ...