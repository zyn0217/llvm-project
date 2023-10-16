// RUN: %clang_cc1 -std=c++14 %s -fsyntax-only -verify
// expected-no-diagnostics
template <typename... Ts> void g(Ts... p1s) {
  (void)[&](auto... p2s) { ([&] { p1s; p2s; }, ...); };
}                                                       
void f1() {
  g();
}

template <typename... a> void b() {
  c([] {
    using d = typename a::e;
    d::category;
  }...);
}
