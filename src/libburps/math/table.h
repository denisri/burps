/***************************************************************************
    copyright            : (C) 2003 by Denis Rivière
    email                : nudz@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef BURPS_MATH_TABLE_H
#define BURPS_MATH_TABLE_H

namespace burps
{

  class BTable
  {
  public:
    BTable();
    virtual ~BTable();

    virtual BTable* clone() const = 0;
    ///	forward
    virtual double operate( double x ) const = 0;
    /// just calls operate()
    double operator () ( double x ) const;
    ///	inverse
    virtual double inv( double x ) const = 0;
    ///	return inverse table
    virtual BTable* inverse() const;
  };

  inline double BTable::operator () ( double x ) const
  {
    return( operate( x ) );
  }


  class InvTable : public BTable
  {
  public:
    InvTable( const BTable & t );
    virtual ~InvTable();

    virtual BTable* clone() const;
    ///	forward
    virtual double operate( double x ) const;
    ///	inverse
    virtual double inv( double x ) const;
    ///	return inverse table
    virtual BTable* inverse() const;

  protected:
    BTable	*_t;
  };

}


#endif

