// RUN: %clang_cc1 -fsyntax-only -verify -std=c++2c %s

namespace Example1 {

template <class OPERATOR>
concept Operator =
  __is_nothrow_constructible(OPERATOR, OPERATOR&);

struct AnyOperator {

  template <Operator OP>
  explicit AnyOperator(OP op) noexcept {}

  AnyOperator(const AnyOperator&) noexcept = default;
};

static_assert(Operator<AnyOperator>);

}

namespace Example2 {

template <typename U>
struct B { static_assert(false); };

template <typename T>
requires (sizeof(B<T>) == 1)
void f(T, typename T::foo = 0) {} // #1
void f(int) {} // #2

void foo() {
    f(0);
}

}

namespace Example3 {

template <class Tp>
concept C = requires(Tp t) { f(t); }; // expected-note {{while substituting template arguments into constraint expression here}} \
                                      // expected-note {{in instantiation of requirement here}}

struct S {};

template <typename T = void>
auto f(S) { return 1; } // expected-note {{candidate function}}

template <class T>
  requires C<T> // expected-error {{constraint 'C<T>' depends on itself}} \
                // expected-note {{while checking the satisfaction of concept 'C<Example3::S>'}} \
                // expected-note 2{{while substituting template arguments into constraint}}
auto f(T); // expected-note 2{{while substituting deduced template arguments into function template}} \
           // expected-note 2{{while checking constraint satisfaction for template}} \
           // expected-note {{candidate template ignored: constraints not satisfied}}

S p;
int i = f(p); // expected-error {{no matching function for call to 'f'}}

}

namespace Example4 {

template <class Tp>
concept C = requires(Tp t) { f(t); };

struct S {};

auto f(S) { return 1; } // #1

template <class T> requires C<T>
auto f(T); // #2

S p;
int i = f(p);

}

namespace Example5 {

template<typename T>
decltype([] { return T::x;}) f(T); // #1
void f(int) {} // #2

int main() {
  f(0);
}

}

