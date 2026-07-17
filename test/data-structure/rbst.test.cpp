#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"
#include "src/template/1template.hpp"
#include "src/data-structure/rbst.hpp"
signed main() {
   int N, Q;
   cin >> N >> Q;
   RBST<ll, [](ll s, ll t) -> ll { return s + t; }, []() -> ll { return 0; }> rb{0};
   int a{}, ar{};
   rep(i, N) {
      ll A;
      cin >> A;
      rb.insert(a, i, A);
      rb.insert(ar, 0, A);
   }
   for(; Q--;) {
      if(int t, L, R; cin >> t >> L >> R, t) {
         auto [l, m]{rb.split(a, L)};
         auto [x, r]{rb.split(m, R - L)};
         cout << rb.sum(x) << '\n';
         a = rb.merge(rb.merge(l, x), r);
      } else {
         auto [la, ma]{rb.split(a, L)};
         auto [xa, ra]{rb.split(ma, R - L)};
         auto [lr, mr]{rb.split(ar, N - R)};
         auto [xr, rr]{rb.split(mr, R - L)};
         a = rb.merge(rb.merge(la, xr), ra);
         ar = rb.merge(rb.merge(lr, xa), rr);
      }
   }
}
