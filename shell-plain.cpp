template<class T>  //Shell sort v1 (stepping by a value close to 3)
void shell_a3n(vector<T> &a) {
  int i, j, h;
  T v;
  h = 1;
  while (h < a.size())
     h = 3*h + 1;
  h = (h - 1)/3;
  while (h) {
     i = h;
     j = i;
     swap(v, a[i]);
     for(;;) {
        j -= h;
        while (j >= 0 && v < a[j]) {
           swap(a[j + h], a[j]);
           j -= h;
        }
        swap(a[j + h], v);
        if (++i == a.size()) break;
        j = i;
        swap(v, a[i]);
     }
     h = (h - 1)/3;
  }
}

template<>  //Shell sort v1 (stepping by a value close to 3)
void shell_a3n(vector<const char*> &a) {
  int i, j, h;
  const char *v;
  h = 1;
  while (h < a.size())
     h = 3*h + 1;
  h = (h - 1)/3;
  while (h) {
     i = h;
     j = i;
     v = a[i];
     while (i < a.size()) {
        j -= h;
        while (j >= 0 && strcmp(v, a[j]) < 0) {
           a[j + h] = a[j];
           j -= h;
        }
        a[j + h] = v;
        ++i;
        j = i;
        v = a[i];
     }
     h = (h - 1)/3;
  }
}

