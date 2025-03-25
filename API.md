# API

This math library adopts a component-based programming approach (where each class is composed of various components).
We'll first introduce the functionality of each component, and then outline which components are included in each
concrete class.

> Note: The API may undergo significant changes soon

## 1. Components

- `Impl` refers to the final class
- Interfaces:
    - Some interfaces (mainly symmetric ones like `operator`) have both static and non-static forms
    - Notation `<...>` indicates template functions
    - `const`, `noexcept`, `Type::`, and some parameters are omitted for brevity
    - Some simplified notations (`{`, `}`, `/`) are used for conciseness

### 1.1 Algebraic Components

#### IInOut

Input and Output

| Interface                           | Description                                                           |
|-------------------------------------|-----------------------------------------------------------------------|
| `std::{i/o}stream& operator{<</>>}` | Input and output, formatted as a list of elements separated by spaces |

#### IAdd

Addition

| Interface                              | Description                                             |
|----------------------------------------|---------------------------------------------------------|
| `operator{+/-/+=/-=}(const Impl& rhs)` | Element-wise addition/subtraction                       |
| `operator{*/*=}(int k)`                | Scalar multiplication, note the parameter type is `int` |
| `operator-`                            | Negation                                                |

#### IMul

Multiplication

| Interface                         | Description                 |
|-----------------------------------|-----------------------------|
| `Impl operator*(const Impl& rhs)` | Element-wise multiplication |
| `Impl inverse()`                  | Inverse                     |

#### IRing

Ring

This component includes the dependent components: `IAdd`, `IMul`

#### IScalarMul

> TODO: This interface needs to be organized

Scalar Multiplication

| Interface               | Description           |
|-------------------------|-----------------------|
| `Impl operator*(U k)`   | Scalar multiplication |
| `Impl& operator*=(U k)` | Scalar multiplication |
| `Impl operator/(U k)`   | Scalar division       |
| `Impl& operator/=(U k)` | Scalar division       |

#### ILinear

Linear

This component includes the dependent components: `IAdd`, `IScalarMul`

#### IMetric

Metric

| Interface    | Description |
|--------------|-------------|
| `F distance` | Distance    |

#### INorm

Norm, naturally induced metric

This component includes the dependent components: `IMetric`, `ILinear`

| Interface                     | Description                                  |
|-------------------------------|----------------------------------------------|
| `F norm()`                    | Norm                                         |
| `Impl normalize()`            | Normalize                                    |
| `bool is_normalized()`        | Check if normalized, with tolerance of 0.001 |
| `Impl& normalize_self()`      | Normalize self                               |
| `Impl safe_normalize()`       | Normalize, result is 0 if norm is 0          |
| `Impl& safe_normalize_self()` | Normalize self, no change if norm is 0       |

#### IInnerProduct

Inner Product, naturally induced norm, angle

This component includes the dependent components: `INorm`

| Interface                    | Description                                           |
|------------------------------|-------------------------------------------------------|
| `F dot`                      | Inner product                                         |
| `F norm2()`                  | Squared norm                                          |
| `F distance2`                | Squared distance                                      |
| `F cos_theta`                | Cosine of the angle between two elements              |
| `F cot_theta`                | Cotangent of the angle between two elements           |
| `Impl project(Impl n)`       | Project onto direction `n`                            |
| `Impl perpendicular(Impl n)` | Project onto the plane perpendicular to direction `n` |

#### IAffineSubspace

Affine Subspace (point, line, plane)

| Interface                            | Description |
|--------------------------------------|-------------|
| `Impl operator{+/-/+=/-=}(Vector v)` | Translation |

#### IAffineRealSubspace

Affine Real Subspace (line, plane)

This component includes the dependent components: `IAffineSubspace`

| Interface                  | Description                   |
|----------------------------|-------------------------------|
| `point`                    | Member variable, anchor point |
| `Impl move`                | Change anchor point           |
| `Impl& move_self(Point p)` | Change anchor point           |

#### IAffine

Affine (point)

This component includes the dependent components: `IAffineSubspace`

| Interface                   | Description                |
|-----------------------------|----------------------------|
| `Vector operator-(Point y)` | Point difference to vector |

#### IOLine

Line through origin (only contains direction)

`O` stands for origin

| Interface          | Description                |
|--------------------|----------------------------|
| `dir`              | Member variable, direction |
| `Vector inv_dir()` | Inverse direction          |

#### ILine

Line (direction + starting point)

This component includes the dependent components: `IOLine`, `IAffineSubspace`

| Interface       | Description       |
|-----------------|-------------------|
| `Point at(F t)` | `point + t * dir` |

#### IOPlane

Plane through origin (only contains normal)

`O` stands for origin

| Interface | Description             |
|-----------|-------------------------|
| `normal`  | Member variable, normal |

#### IPlane

Plane (normal + point)

This component includes the dependent components: `IOPlane`, `IAffineSubspace`

#### IEuclideanV

Euclidean Vector Space

This component includes the dependent components: `IInnerProduct`, `IArrayLinear` ( `IArrayLinear` is a concretization
of `ILinear` based on `IArray`)

For 4-dimensional vectors, some 3-dimensional vector interfaces (`v3_*`) are provided for acceleration using `__m128` (
storing 3-dimensional vectors in 4-dimensional vectors)

#### IEuclideanA

Euclidean Affine Space

This component includes the dependent components: `IMetric`, `IAffine`, `IArray`

| Interface     | Description      |
|---------------|------------------|
| `F distance2` | Squared distance |

#### ICross

Cross Product (only supports 3-dimensional vectors)

| Interface     | Description                                                                                                                  |
|---------------|------------------------------------------------------------------------------------------------------------------------------|
| `Impl cross`  | Cross product                                                                                                                |
| `F sin_theta` | Calculate `sin_theta` using cross product (not necessarily faster than using `cos_theta()` and then calculating `sin theta`) |

### 1.2 Storage Components

#### 1.2.1 Array

##### IArray

> TODO: Further split functionality

Implemented using `std::array<T, N>`, when using `<float, 4>`, implemented using `__m128`

Supports all `std::array` interfaces, such as `begin`, `end`, `operator[]`, etc.

Additionally, there are interfaces

| Interface                                   | Description                                                                                                                                |
|---------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| `IArray(const T* data)`                     | Construct from array pointer                                                                                                               |
| `IArray(const IArray& arr)`                 | Copy constructor                                                                                                                           |
| `IArray(T t)`                               | Construct from single element                                                                                                              |
| `IArray(Ts... ts)`                          | Construct from multiple elements, the number of elements `sizeof...(Ts)` equals the dimension `N`, requires `Ts...` to be `static_cast<T>` |
| `static Impl zero()`                        | Equivalent to `IArray(0)`                                                                                                                  |
| `T get<size_t i>()`                         | Similar to `operator[]`, but optimized for `__m128`                                                                                        |
| `void set<size_t i>(T t)`                   | Optimized for `__m128`                                                                                                                     |
| `Impl replicate<size_t i>`                  | Fill all elements with the `i`-th element to get a new `Impl`, optimized for `__m128`                                                      |
| `operator{</<=/>/>=/==/!=}`                 | Lexicographical comparison, optimized for `__m128`                                                                                         |
| `bool all_{lt/le/gt/ge}(const IArray& rhs)` | Total order comparison, optimized for `__m128`                                                                                             |

Concrete implementations of the above algebraic components based on arrays, such as `IArrayAdd`, `IArrayMScalarMul`,
etc., with no new interfaces

##### IArrayCast

This component includes the dependent components: `IArray`

| Interface                   | Description                                                                           |
|-----------------------------|---------------------------------------------------------------------------------------|
| `To cast_to<typename To>()` | Perform `static_cast<To::T>` on each member, requires `To::N` not to exceed `Impl::N` |
| `To& as<typename To>()`     | Direct `reinterpret_cast`, requires `sizeof(To)==sizeof(Impl)`                        |

##### IArray1D

Statically requires the array to be 1D

This component includes the dependent components: `IArray`

##### IArray1D_Util

This component includes the dependent components: `IArray`

| Interface                       | Description                                                           |
|---------------------------------|-----------------------------------------------------------------------|
| `Impl abs()`                    | Absolute value                                                        |
| `T& {min/max}_component()`      | Minimum/maximum element                                               |
| `T {min/max}_component() const` | Minimum/maximum element, the const version supports SIMD acceleration |
| `size_t {min/max}_dim()`        | Dimension with the smallest value                                     |
| `Impl {min/max}`                | Element-wise minimum/maximum value                                    |

#### 1.2.2 Matrix

##### IMatrix

An array of 1D arrays is a matrix

Column-major

This component includes the dependent components: `IArrayUtil`

| Interface                            | Description                                                                |
|--------------------------------------|----------------------------------------------------------------------------|
| `IMatrix(std::array<F, N*N> data)`   | Construct from array, **column-major**                                     |
| `void init(std::array<F, N*N> data)` | Assign from array, **column-major**                                        |
| `IMatrix(Ts... vals)`                | Construct from `N*N` elements, **row-major**                               |
| `void init(Ts... vals)`              | Assign from `N*N` elements, **row-major**                                  |
| `Impl eye()`                         | Identity matrix                                                            |
| `operator(size_t r, size_t c)`       | Element at row `r`, column `c`                                             |
| `at(size_t r, size_t c)`             | Element at row `r`, column `c`                                             |
| `operator(size_t n)`                 | `n`-th element, **row-major**                                              |
| `at(size_t n)`                       | `n`-th element, **row-major**                                              |
| `F trace()`                          | Trace                                                                      |
| `Impl transpose()`                   | Transpose                                                                  |
| `(U,S, V) SVD()`                     | SVD decomposition, supports 2x2 and 3x3 matrices (not exact, takes 1~2 ms) |
| `(U, S, V) signed_SVD()`             | SVD decomposition, ensures `det(UV^T)>0`, supports 2x2 and 3x3 matrices    |
| `F det()`                            | Determinant                                                                |
| `F* data()`                          | Data pointer                                                               |

##### IMatrix_Mul

This component includes the dependent components: `IMatrix`, `IMul`

| Interface                    | Description                  |
|------------------------------|------------------------------|
| `Vector operator*(Vector v)` | Matrix-vector multiplication |

##### IMatrix_InOut

This component includes the dependent components: `IMatrix`

| Interface                  | Description          |
|----------------------------|----------------------|
| `void print(std::ostream)` | Print in matrix form |

## 2. Classes

Classes are a combination of the above components, with additional functionalities

Users should refer to the header files in [include/MyGM](include/MyGM) for specific details

Here, we provide a brief overview of each class

### bbox

Axis-Aligned Bounding Box

Dependent components: `IArrayUtil`

### euler

Euler Angles (ZXY)

Dependent components: `IArray1D_Util`

First rotate around the object's y-axis, then around the object's x-axis, and finally around the object's z-axis

Tait–Bryan angles, extrinsic rotations (math: x-y-z, game: z-x-y)

### hvec

Homogeneous Vector

Dependent components: `IEuclideanV`

### line

Line

Dependent components: `ILine`, `IInOut`

### mat

Matrix

Dependent components: `IMatrixInOut`, `IMatrixMul`, `IArrayLinear`, `IRing`

### normal

Normal (essentially a bivector)

Dependent components: `ICross`

### plane

Plane

Dependent components: `IInOut`, `IPlane`

### point

Point

Dependent components: `IArray1D_Util`, `IEuclideanA`

### quat

Quaternion

Dependent components: `IMul`, `IArrayUtil`

### ray

Ray

Dependent components: `ILine`, `IInOut`

### rgb

RGB Color

Dependent components: `IArray1D_Util`, `IArrayHadamardProduct`, `IArrayLinear`

### rgba

RGBA Color

Dependent components: `IArray1D_Util`

### scale

Scale

Dependent components: `IArray1D_Util`

### svec

Surface Vector

Dependent components: `IArray1D_Util`, `ICross`

### transform

Transform

Dependent components: `IMatrixInOut`, `IMatrixMul`

### triangle

Triangle

Dependent components: `IArrayInOut`

### val

Value, does not use SIMD (for convenient storage)

Dependent components: `IArrayLinear`, `IArrayHadamardProduct`, `IArray1D_Util`

### vec

Vector

Dependent components: `IArray1D_Util`, `IEuclideanV` (for 3-dimensional vectors, also dependent on `ICross`)