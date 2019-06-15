#ifndef R_SFHEADERS_SFG_LINESTRING_H
#define R_SFHEADERS_SFG_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {

  // need functions to get_line(), get_polygon(), etc.
  //
  // inline SEXP get_line(
  //     SEXP x
  // ) {
  //
  // }



  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP to_linestring(
      Rcpp::IntegerMatrix& im
  ) {

    size_t n_col = im.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "LINESTRING";
    im.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return im;
  }

  inline SEXP to_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {

    size_t n_row = im.nrow();
    size_t n_col = cols.size();
    size_t i;
    Rcpp::IntegerMatrix im2( n_row, n_col );
    for( i = 0; i < n_col; i++ ) {
      int this_col = cols[ i ];
      im2( Rcpp::_, i ) = im( Rcpp::_, this_col );
    }
    return to_linestring( im2 );
  }

  inline SEXP to_linestring(
      Rcpp::NumericMatrix& nm
  ) {

    size_t n_col = nm.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "LINESTRING";
    nm.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type);

    return nm;
  }

  inline SEXP to_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {

    size_t n_row = nm.nrow();
    size_t n_col = cols.size();
    size_t i;
    Rcpp::NumericMatrix nm2( n_row, n_col );
    for( i = 0; i < n_col; i++ ) {
      int this_col = cols[ i ];
      nm2( Rcpp::_, i ) = nm( Rcpp::_, this_col );
    }
    return to_linestring( nm2 );
  }

  // expects only lon/lat/z/m columns
  inline SEXP to_linestring(
      Rcpp::DataFrame& df
  ) {
    size_t n_row = df.nrow();
    size_t n_col = df.ncol();
    // need to extract each column-vector, then create a numeric vector from those
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( df );
    return to_linestring( nm );
  }

  inline SEXP to_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    size_t n_col = cols.size();
    if( df.ncol() < n_col ) {
      Rcpp::stop("sfheaders - incorrect number of columns");
    }
    size_t n_row = df.nrow();
    Rcpp::NumericMatrix nm( n_row, n_col );
    size_t i;

    for( i = 0; i < n_col; i++ ) {
      Rcpp::String this_col = cols[i];
      //nm( Rcpp::_, i ) = df[ this_col ];
      Rcpp::NumericVector this_vec = df[ this_col ];
      nm( Rcpp::_, i ) = this_vec;

    }
    return to_linestring( nm );
  }

  inline SEXP to_linestring(
      SEXP& x
  ) {
    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_linestring( im );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_linestring( nm );
    }
    case VECSXP: { // data.frame && list?
      //   if( Rf_isNewList( x ) ) {
      //   Rcpp::stop("sfheaders - lists not supported for sfg_LINESTRING");
      // }
      // TODO - rather than Rf_isNewList - need to check the class is not data.frame
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_linestring( df );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
    }
    }

    return x; // never reaches
  }

  inline SEXP to_linestring(
      SEXP& x,
      Rcpp::IntegerVector cols
  ) {
    // with string columns it must be a data.frame(?)
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("Expecting a matrix ");
    }
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_linestring( im, cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_linestring( nm, cols );
    }
    default: {
      Rcpp::stop("Expecting a matrix") ; //should never reach?
    }
    }
    return Rcpp::List::create(); // never reaches
  }


} // sfg
} // sfheaders


#endif
