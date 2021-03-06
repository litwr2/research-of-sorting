// Shell's sort implementations with tables

template<class T>  //Shell sort v2 (table)
void shell_tab(vector<T> &a, int type) {
  static const int x0[] = {485165237, 178482289, 65659969, 24154967, 8886109, 3269011, 1202609, 442439, 162713, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes approximately close to powers of e
//static const int x0[] = {485165237, 178482289, 65659969, 24154957, 8886113, 3269011, 1202603, 442399, 162751, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes close to powers of e
  static const int x1[] = {284820883, 104779757, 38546311, 14180393, 5216681, 1919119, 706001, 259723, 95549, 35149, 12923, 4759, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation
  static const int x2[] = {67108859, 33554393, 16777213, 8388617, 4194301, 2097143, 1048571, 524287, 262253, 131063, 65537, 32771, 16381, 8191, 4093, 2041, 1023, 511, 253, 123, 61, 31, 11, 5, 2, 1, 0};  //primes close to powers of 2
  static const int x3[] = {485165195, 178482301, 65659969, 24154953, 8886111, 3269017, 1202604, 442413, 162755, 59874, 22026, 8103, 2981, 1097, 403, 148, 55, 20, 7, 3, 1, 0};  //values close to powers of e
  static const int x4[] = {688549733, 206564921, 61969477, 18590849, 5577239, 1673179, 501953, 150587, 45179, 13553, 4073, 1223, 367, 109, 31, 11, 3, 1, 0};  //values of primes close to numbers from sequence s[n+1] = 10s[n]/3
  static const int x5[] = {680488555, 302439358, 134417492, 59741107, 26551603, 11800712, 5244761, 2331004, 1036002, 460445, 204642, 90952, 40423, 17965, 7984, 3548, 1577, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation based on 2.25 factor and floor rounding
  static const int x6[] = {637621501, 283387334, 125949926, 55977745, 24878998, 11057333, 4914370, 2184165, 970740, 431440, 191752, 85223, 37877, 16835, 7482, 3326, 1478, 657, 292, 130, 58, 26, 12, 6, 3, 1, 0};  //s[n]=ceil(v[n]), v[n]=2.25*v[n-1], v[1]=1
  const int *p;
  switch (type) {
      case 0: p = x0; break;
      case 1: p = x1; break;
      case 2: p = x2; break;
      case 3: p = x3; break;
      case 4: p = x4; break;
      case 5: p = x5; break;
      case 6: p = x6; break;
  }
  int i, j, k = 0, gap;
  while (p[k] >= a.size()) ++k;
  while (p[k]) {
     gap = p[k++];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        while (a[j] > a[j + gap]) {
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
     }
  }
}

template<>  //Shell sort v2 (table)
void shell_tab(vector<const char*> &a, int type) {
  static const int x0[] = {485165237, 178482289, 65659969, 24154967, 8886109, 3269011, 1202609, 442439, 162713, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes approximately close to powers of e
//static const int x0[] = {485165237, 178482289, 65659969, 24154957, 8886113, 3269011, 1202603, 442399, 162751, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes close to powers of e
  static const int x1[] = {284820883, 104779757, 38546311, 14180393, 5216681, 1919119, 706001, 259723, 95549, 35149, 12923, 4759, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation
  static const int x2[] = {67108859, 33554393, 16777213, 8388617, 4194301, 2097143, 1048571, 524287, 262253, 131063, 65537, 32771, 16381, 8191, 4093, 2041, 1023, 511, 253, 123, 61, 31, 11, 5, 2, 1, 0};  //primes close to powers of 2
  static const int x3[] = {485165195, 178482301, 65659969, 24154953, 8886111, 3269017, 1202604, 442413, 162755, 59874, 22026, 8103, 2981, 1097, 403, 148, 55, 20, 7, 3, 1, 0};  //values close to powers of e
  static const int x4[] = {688549733, 206564921, 61969477, 18590849, 5577239, 1673179, 501953, 150587, 45179, 13553, 4073, 1223, 367, 109, 31, 11, 3, 1, 0};  //values of primes close to numbers from sequence s[n+1] = 10s[n]/3
  static const int x5[] = {680488555, 302439358, 134417492, 59741107, 26551603, 11800712, 5244761, 2331004, 1036002, 460445, 204642, 90952, 40423, 17965, 7984, 3548, 1577, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation based on 2.25 factor and floor rounding
  static const int x6[] = {637621501, 283387334, 125949926, 55977745, 24878998, 11057333, 4914370, 2184165, 970740, 431440, 191752, 85223, 37877, 16835, 7482, 3326, 1478, 657, 292, 130, 58, 26, 12, 6, 3, 1, 0};  //s[n]=ceil(v[n]), v[n]=2.25*v[n-1], v[1]=1
  const int *p;
  switch (type) {
      case 0: p = x0; break;
      case 1: p = x1; break;
      case 2: p = x2; break;
      case 3: p = x3; break;
      case 4: p = x4; break;
      case 5: p = x5; break;
      case 6: p = x6; break;
  }
  int i, j, k = 0, gap;
  while (p[k] >= a.size()) ++k;
  while (p[k]) {
     gap = p[k++];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        while (strcmp(a[j], a[j + gap]) > 0) {
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
     }
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
        while (a[j] > a[j + gap]) {
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
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
        while (strcmp(a[j], a[j + gap]) > 0) {
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
     }
  }
}

