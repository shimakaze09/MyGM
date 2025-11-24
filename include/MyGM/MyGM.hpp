#pragma once

/**
 * @file MyGM.hpp
 * @brief Main header file for the MyGM library.
 *
 * This file includes all the necessary headers for using the MyGM library.
 * MyGM is a modern C++ mathematics library designed for computer graphics
 * and geometry applications. It provides a set of template classes and
 * functions for vector arithmetic, matrix operations, geometric primitives,
 * and more.
 *
 * Key components:
 * - Linear Algebra: vec, mat, quat, hvec, svec
 * - Geometry: point, line, plane, triangle, bbox, ray
 * - Utilities: val, euler, scale, rgb, rgba, transform
 *
 * The library uses a Static Interface (SI) system based on CRTP and Mixins
 * to achieve high performance and extensibility.
 */

#include "basic.hpp"
#include "bbox.hpp"
#include "euler.hpp"
#include "hvec.hpp"
#include "line.hpp"
#include "mat.hpp"
#include "normal.hpp"
#include "plane.hpp"
#include "point.hpp"
#include "quat.hpp"
#include "ray.hpp"
#include "rgb.hpp"
#include "rgba.hpp"
#include "sample.hpp"
#include "scale.hpp"
#include "svec.hpp"
#include "transform.hpp"
#include "triangle.hpp"
#include "val.hpp"
#include "vec.hpp"
