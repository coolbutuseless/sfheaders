#ifndef R_SFHEADERS_SFG_LINESTRINGS_H
#define R_SFHEADERS_SFG_LINESTRINGS_H

#include <Rcpp.h>
#include "sfheaders/sfg/linestring/sfg_linestring.hpp"

namespace sfheaders {
namespace sfg {

  Rcpp::List sfg_linestrings( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfg::sfg_linestring( x );
    }
    return sfcs;
  }

} // sfg
} // sfheaders


#endif
