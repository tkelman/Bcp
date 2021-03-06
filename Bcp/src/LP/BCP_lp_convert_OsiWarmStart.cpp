// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.

#include "CoinWarmStartDual.hpp"
#include "CoinWarmStartPrimalDual.hpp"
#include "CoinWarmStartBasis.hpp"

#include "BCP_lp_functions.hpp"
#include "BCP_warmstart_dual.hpp"
#include "BCP_warmstart_primaldual.hpp"

BCP_warmstart*
BCP_lp_convert_CoinWarmStart(BCP_lp_prob& p, CoinWarmStart*& warmstart)
{
  if (warmstart == NULL)
    return NULL;

  {
    const CoinWarmStartDual* ws =
      dynamic_cast<const CoinWarmStartDual*>(warmstart);
    if (ws != NULL) {
      const int size = ws->size();
      const double* dual = ws->dual();
      BCP_warmstart* bcp_ws = new BCP_warmstart_dual(dual, dual+size);
      delete warmstart;
      warmstart = NULL;
      return bcp_ws;
    }
  }

  {
    const CoinWarmStartPrimalDual* ws =
      dynamic_cast<const CoinWarmStartPrimalDual*>(warmstart);
    if (ws != NULL) {
      const int psize = ws->primalSize();
      const int dsize = ws->dualSize();
      const double* primal = ws->primal();
      const double* dual = ws->dual();
      BCP_warmstart* bcp_ws =
	  new BCP_warmstart_primaldual(primal, primal+psize, dual, dual+dsize);
      delete warmstart;
      warmstart = NULL;
      return bcp_ws;
    }
  }

  {
    const CoinWarmStartBasis* ws =
      dynamic_cast<const CoinWarmStartBasis*>(warmstart);
    if (ws != NULL) {
      // *FIXME* : want to convert it to BCP_warmstart_basis
      delete warmstart;
      warmstart = NULL;
      return NULL;
    }
  }


  return NULL;
}
