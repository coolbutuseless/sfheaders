#ifndef R_SFHEADERS_SFC_MULTIPOINTS_H
#define R_SFHEADERS_SFC_MULTIPOINTS_H

#include <Rcpp.h>
#include "sfheaders/sfc/multipoint/sfc_multipoint.hpp"

namespace sfheaders {
namespace sfc {

  Rcpp::List sfc_multipoints( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfc::sfc_multipoint( x );
    }
    return sfcs;
  }

} // sfc
} // sfheaders

#endif
