#ifndef R_SFHEADERS_DF_SFG_H
#define R_SFHEADERS_DF_SFG_H

#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/df/utils.hpp"
#include "sfheaders/coordinates/coordinates.hpp"

#include <Rcpp.h>

#define M_COLUMN                  12
#define Z_COLUMN                  11
#define Y_COLUMN                  10
#define X_COLUMN                  9
#define POINT_COLUMN              8
#define MULTIPOINT_COLUMN         7
#define LINESTRING_COLUMN         6
#define MULTILINESTRING_COLUMN    5
#define POLYGON_COLUMN            4
#define MULTIPOLYGON_COLUMN       3
#define GEOMETRYCOLLECTION_COLUMN 2
#define SFG_COLUMN                1
#define SFC_COLUMN                0

#define MAX_COLUMNS            13

#define SFG_POINT               1
#define SFG_MULTIPOINT          2
#define SFG_LINESTRING          3
#define SFG_MULTILINESTRING     4
#define SFG_POLYGON             5
#define SFG_MULTIPOLYGON        6
#define SFG_GEOMETRYCOLLECTION  7

namespace sfheaders {
namespace df {

  const Rcpp::CharacterVector column_names = {
    "sfc_id", "sfg_id", "geometrycollection_id", "multipolygon_id", "polygon_id", "multilinestring_id",
    "linestring_id", "multipoint_id", "point_id", "x","y","z","m"
  };

  inline Rcpp::CharacterVector make_names( Rcpp::CharacterVector& cls ) {

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    if ( dim == "XYZM" ) {
      columns[ Z_COLUMN ] = true;
      columns[ M_COLUMN ] = true;
    } else if ( dim == "XYZ" ) {
      columns[ Z_COLUMN ] = true;
    } else if ( dim == "XYM" ) {
      columns[ M_COLUMN ] = true;  // #nocov
    }

    columns[ X_COLUMN ] = true;
    columns[ Y_COLUMN ] = true;

    if( geometry == "POINT" ) {
    } else if ( geometry == "MULTIPOINT" ) {

    } else if ( geometry == "LINESTRING" ) {

    } else if ( geometry == "MULTILINESTRING" ) {
      columns[ LINESTRING_COLUMN ] = true;

    } else if ( geometry == "POLYGON" ) {
      columns[ LINESTRING_COLUMN ] = true;

    } else if ( geometry == "MULTIPOLYGON" ) {
      columns[ LINESTRING_COLUMN ] = true;
      columns[ POLYGON_COLUMN ] = true;
    }

    return column_names[ columns ];
  }


  inline Rcpp::List sfg_to_df( SEXP& sfg ) {

    Rcpp::List res;

    Rcpp::CharacterVector cls = sfheaders::coordinates::getSfgClass( sfg );

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    R_xlen_t sfg_rows = 0;

    if( geometry == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      res = sfheaders::coordinates::sfg_point_coordinates( nv, sfg_rows );

    } else if ( geometry == "MULTIPOINT" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfheaders::coordinates::sfg_multipoint_coordinates( nm, sfg_rows );

    } else if ( geometry == "LINESTRING" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfheaders::coordinates::sfg_linestring_coordinates( nm, sfg_rows );

    } else if ( geometry == "MULTILINESTRING" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::coordinates::sfg_multilinestring_coordinates( lst, sfg_rows );

    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::coordinates::sfg_polygon_coordinates( lst, sfg_rows );

    } else if ( geometry == "MULTIPOLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::coordinates::sfg_multipolygon_coordinates( lst, sfg_rows );

    } else {
      Rcpp::stop("sfheaders - unknown geometry type"); // #nocov
    }

    Rcpp::CharacterVector df_names = make_names( cls );

    sfheaders::utils::construct_df( res, df_names, sfg_rows );
    return res;

  }

} // df
} // sfheaders

#endif
