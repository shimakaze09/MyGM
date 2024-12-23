//
// Created by Admin on 23/12/2024.
//

#include <array>
#include <iostream>
#include <utility>

struct Nil {};
template <template <typename, typename, typename, size_t> class... Interfaces>
struct IMergeT;
template <typename Base, typename Impl, typename T, size_t N,
          template <typename, typename, typename, size_t> class... Interfaces>
using IMerge = typename IMergeT<Interfaces...>::template type<Base, Impl, T, N>;

template <>
struct IMergeT<> {
 private:
  template <typename Base, typename Impl, typename T, size_t N>
  struct INil : Base {};

 public:
  template <typename Base, typename Impl, typename T, size_t N>
  using type = INil<Base, Impl, T, N>;
};

template <template <typename, typename, typename, size_t> class Interface>
struct IMergeT<Interface> {
 private:
  template <typename Base, typename Impl, typename T, size_t N>
  struct INil : Base {};

 public:
  template <typename Base, typename Impl, typename T, size_t N>
  using type = Interface<Base, Impl, T, N>;
};

template <template <typename, typename, typename, size_t> class IHead,
          template <typename, typename, typename, size_t> class... ITail>
struct IMergeT<IHead, ITail...> {
  template <typename Base, typename Impl, typename T, size_t N>
  using type = IHead<IMerge<Base, Impl, T, N, ITail...>, Impl, T, N>;
};

template <typename Base, typename Impl, typename T, size_t N>
struct IFoo : Base {
  Impl* Foo() {
    T{};
    N;
    return static_cast<Impl*>(this);
  }
};

template <typename Base, typename Impl, typename T, size_t N>
struct IBar : Base {
  Impl* Bar() { return static_cast<Impl*>(this); }
};

template <typename Base, typename Impl, typename T, size_t N>
using ITest = IMerge<Base, Impl, T, N, IFoo, IBar>;

template <typename Base, typename Impl, typename T, size_t N>
struct IAdd : Base {
  Impl operator+(const Impl& y) const {
    const auto& x = *static_cast<const Impl*>(this);
    Impl rst;
    for (size_t i = 0; i < N; i++)
      rst[i] = x[i] + y[i];
    return rst;
  }
};

template <typename Base, typename Impl, typename T, size_t N>
struct IInOut : Base {
  friend std::ostream& operator<<(std::ostream& os, const Impl& x) {
    for (size_t i = 0; i < N - 1; i++)
      os << x[i] << ", ";
    os << x[N - 1];
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Impl& x) {
    for (size_t i = 0; i < N; i++)
      is >> x[i];
    return is;
  }
};

template <typename Impl, typename T, size_t N,
          template <typename, typename, typename, size_t> class... Interfaces>
struct Val : std::array<T, N>, IMerge<Nil, Impl, T, N, Interfaces...> {
  Val() = default;

  Val(const std::array<T, N>& data) : std::array<T, N>(data) {}
};

template <typename T, size_t N>
struct Vec : Val<Vec<T, N>, T, N, ITest, IAdd, IInOut> {
  using Val<Vec<T, N>, T, N, ITest, IAdd, IInOut>::Val;
};

template <size_t N>
using Vecf = Vec<float, N>;
using Vecf3 = Vecf<3>;
static_assert(sizeof(Vecf3) == 3 * sizeof(float),
              "sizeof(Vecf3) == 3 * sizeof(float)");

int main() {
  Vecf3 vs[4];
  Vecf3 u;
  u.Foo();

  for (size_t i = 0; i < 4; i++)
    std::cin >> vs[i];

  std::cout << vs[2] + vs[3];
  std::cout << Vecf3(
      {vs[0][0] + vs[1][0], vs[0][1] + vs[1][1], vs[0][2] + vs[1][2]});
}