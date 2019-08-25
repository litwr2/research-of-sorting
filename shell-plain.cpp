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

template<class T>  //Shell sort v3 (stepping by values from the sequence s[n+1] = 10s[n]/3)
void shell_10d3(vector<T> &a) {
  static const int maxi = 19; 
  static int p[maxi] = {0, 1};
  int i, j, k, gap;
  if (p[2] == 0)
      for (k = 2; k < maxi; ++k) p[k] = 10*p[k - 1]/3;
  else
      k = maxi;
  while (p[--k] >= a.size());
  while (p[k]) {
     gap = p[k--];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        //T t = a[j + gap];
        while (a[j] > a[j + gap]) {
           //a[j] = a[j + gap];
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
        //a[j] = t;
     }
  }
}

template<>  //Shell sort v3 (stepping by values from the sequence s[n+1] = 10s[n]/3)
void shell_10d3(vector<const char *> &a) {
  static const int maxi = 19; 
  static int p[maxi] = {0, 1};
  int i, j, k, gap;
  if (p[2] == 0)
      for (k = 2; k < maxi; ++k) p[k] = 10*p[k - 1]/3;
  else
      k = maxi;
  while (p[--k] >= a.size());
  while (p[k]) {
     gap = p[k--];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        //T t = a[j + gap];
        while (strcmp(a[j], a[j + gap]) > 0) {
           //a[j] = a[j + gap];
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
        //a[j] = t;
     }
  }
}

