template<typename T, T (*f)(T, T), T (*e)()> struct RBST {
   inline int rnd() {
      static int x = 123456789;
      static int y = 362436069;
      static int z = 521288629;
      static int w = 88675123;
      int t;

      t = x ^ (x << 11);
      x = y;
      y = z;
      z = w;
      return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
   }
   struct node {
      int l, r;
      int cnt;
      T x, sum;
      node() = default;
      node(T x_) : l(0), r(0), x(x_), sum(x_) { cnt = 1; }
   };
   RBST(int n) : b(n + 1) {}
   int cnt(const int t) { return t ? b[t].cnt : 0; }
   T sum(const int t) { return t ? b[t].sum : e(); }
   int update(int t) {
      b[t].cnt = cnt(b[t].l) + cnt(b[t].r) + 1;
      b[t].sum = f(f(sum(b[t].l), b[t].x), sum(b[t].r));
      return t;
   }
   vector<node> b;
   int ptr = 1;
   inline int alloc(const T& v) {
      if(si(b) == ptr) b.resize(si(b) * 2);
      b[ptr] = node(v);
      return ptr++;
   }
   int merge(int l, int r) {
      if(!l or !r) return l ? l : r;
      if(rnd() % (cnt(l) + cnt(r)) < cnt(l)) {
         b[l].r = merge(b[l].r, r);
         return update(l);
      }
      b[r].l = merge(l, b[r].l);
      return update(r);
   }

   pair<int, int> split(int t, int k) {
      if(!t) return {t, t};
      if(k <= cnt(b[t].l)) {
         auto [l, r] = split(b[t].l, k);
         b[t].l = r;
         return {l, update(t)};
      }
      auto [l, r] = split(b[t].r, k - cnt(b[t].l) - 1);
      b[t].r = l;
      return {update(t), r};
   }

   void insert(int& t, int k, const T& v) {
      auto [l, r] = split(t, k);
      t = merge(merge(l, alloc(v)), r);
   }
};
