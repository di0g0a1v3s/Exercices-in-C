
int check_data_property(int *vec, int iL, int iR) {

  int k, res;

  munch_data(vec, iL, iR);

  for (res = 0, k = iL; k < iR; k++) {

    if (vec[k] == vec[k + 1]) {
      res++;
    }
  }

  return(res);
}
