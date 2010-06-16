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

#ifndef BURPS_MATH_LOCALIZATION
#define BURPS_MATH_LOCALIZATION


#include <string>
#include <vector>
#include <map>

namespace burps
{
  class BTable;

  class Localization
  {
  public:
    Localization();
    virtual ~Localization();

    const std::vector<std::string> & parts() const;
    double size( const std::string & part ) const;
    double totalSize() const;
    /// size of a part in proportion to the total size of all parts
    double pSize( const std::string & part ) const;
    ///	void space around a part
    double voidSpace( const std::string & part ) const;
    ///	void space in proportion to the total size of all parts (NOT voids)
    double pVoid( const std::string & part ) const;
    double totalVoid() const;
    const std::vector<std::string> & order( const std::string & part ) const;
    double sumSize( const std::string & aimpart, int pos ) const;
    std::string localize( const std::string & aimpart, double dieroll, 
		     const BTable & tab, double adj = 0 ) const;
    std::string localize( const std::string & aimpart, double margin, 
		     bool specifySide = true ) const;
    void buildDistances() const;

  protected:
    std::vector<std::string>				_parts;
    std::vector<double>					_sizes;
    std::vector<double>					_voids;
    mutable double					_totalSize;
    mutable double					_totalVoid;
    std::map<std::string, std::vector<std::string> >	_orders;
    mutable std::map<std::string, std::vector<double> >	_dist;
  };


  class ManLocalization : public Localization
  {
  public:
    ManLocalization();
    virtual ~ManLocalization();
  };

}


#endif

