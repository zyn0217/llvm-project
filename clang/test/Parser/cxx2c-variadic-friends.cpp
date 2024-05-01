// RUN: %clang_cc1 -std=c++2c -verify -fsyntax-only %s

namespace list {

struct widget;
struct handler;

struct A {
  friend struct foo, struct bar;
  friend struct baz, qux;
  // expected-error@-1 {{a type specifier is required for all declarations}}
  friend widget, struct gadget;
  friend a, b, c;
  // expected-error@-1 3{{a type specifier is required for all declarations}}
  // expected-error@-2 3{{friends can only be classes or functions}}
  friend struct foo, bar, struct baz;
  // expected-error@-1 {{a type specifier is required for all declarations}}
  friend widget, handler;
};

struct B {
  friend widget, handler
  // expected-error {{expected member name or ';' after declaration specifiers}}
};

struct C {
  friend widget,
};

} // namespace list
