template<class T>  //Shell sort v1 (stepping by a value close to 3)
void shell1(vector<T> &a) {
  int i, j, h;
  T v;
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
        while (j >= 0 && v <= a[j]) {
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

template<>  //Shell sort v1 (stepping by a value close to 3)
void shell1(vector<const char*> &a) {
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
        while (j >= 0 && strcmp(v,a[j]) <= 0) {
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

template<class T>  //Shell sort v2 (table)
void shell2(vector<T> &a, int type) {
  static const int x0[] = {485165237, 178482289, 65659969, 24154967, 8886109, 3269011, 1202609, 442439, 162713, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes approximately close to powers of e
//static const int x0[] = {485165237, 178482289, 65659969, 24154957, 8886113, 3269011, 1202603, 442399, 162751, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes close to powers of e
  static const int x1[] = {284820883, 104779757, 38546311, 14180393, 5216681, 1919119, 706001, 259723, 95549, 35149, 12923, 4759, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation
  static const int x2[] = {67108859, 33554393, 16777213, 8388617, 4194301, 2097143, 1048571, 524287, 262253, 131063, 65537, 32771, 16381, 8191, 4093, 2041, 1023, 511, 253, 123, 61, 31, 11, 5, 2, 1, 0};  //primes close to powers of 2

  //static const int x2[] = {230242168, 84701360, 31159889, 11463083, 4217032, 1551360, 570713, 209954, 77238, 28414, 10453, 3845, 1415, 520, 191, 70, 26, 10, 4, 1, 0}; //experimental

  static const int x3[] = {485165195, 178482301, 65659969, 24154953, 8886111, 3269017, 1202604, 442413, 162755, 59874, 22026, 8103, 2981, 1097, 403, 148, 55, 20, 7, 3, 1, 0};  //values close to powers of e
  static const int x4[] = {688549733, 206564921, 61969477, 18590849, 5577239, 1673179, 501953, 150587, 45179, 13553, 4073, 1223, 367, 109, 31, 11, 3, 1, 0};  //values of primes close to numbers from sequence s[n+1] = 10s[n]/3
  const int *p;
  switch (type) {
      case 0: p = x0; break;
      case 1: p = x1; break;
      case 2: p = x2; break;
      case 3: p = x3; break;
      case 4: p = x4; break;
  }
  int i, j, k = 0, gap;
  while (p[k] >= a.size()) ++k;
  while (p[k]) {
     gap = p[k++];
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

template<>  //Shell sort v2 (table)
void shell2(vector<const char*> &a, int type) {
  static const int x0[] = {485165237, 178482289, 65659969, 24154967, 8886109, 3269011, 1202609, 442439, 162713, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes approximately close to powers of e
//static const int x0[] = {485165237, 178482289, 65659969, 24154957, 8886113, 3269011, 1202603, 442399, 162751, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes close to powers of e
  static const int x1[] = {284820883, 104779757, 38546311, 14180393, 5216681, 1919119, 706001, 259723, 95549, 35149, 12923, 4759, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation
  static const int x2[] = {67108859, 33554393, 16777213, 8388617, 4194301, 2097143, 1048571, 524287, 262253, 131063, 65537, 32771, 16381, 8191, 4093, 2041, 1023, 511, 253, 123, 61, 31, 11, 5, 2, 1, 0};  //primes close to powers of 2

  //static const int x2[] = {230242168, 84701360, 31159889, 11463083, 4217032, 1551360, 570713, 209954, 77238, 28414, 10453, 3845, 1415, 520, 191, 70, 26, 10, 4, 1, 0}; //experimental

  static const int x3[] = {485165195, 178482301, 65659969, 24154953, 8886111, 3269017, 1202604, 442413, 162755, 59874, 22026, 8103, 2981, 1097, 403, 148, 55, 20, 7, 3, 1, 0};  //values close to powers of e
  static const int x4[] = {688549733, 206564921, 61969477, 18590849, 5577239, 1673179, 501953, 150587, 45179, 13553, 4073, 1223, 367, 109, 31, 11, 3, 1, 0};  //values of primes close to numbers from sequence s[n+1] = 10s[n]/3
  const int *p;
  switch (type) {
      case 0: p = x0; break;
      case 1: p = x1; break;
      case 2: p = x2; break;
      case 3: p = x3; break;
      case 4: p = x4; break;
  }
  int i, j, k = 0, gap;
  while (p[k] >= a.size()) ++k;
  while (p[k]) {
     gap = p[k++];
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

template<class T>  //Shell sort v3 (stepping by values from the sequence s[n+1] = 10s[n]/3)
void shell3(vector<T> &a) {
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
void shell3(vector<const char *> &a) {
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

