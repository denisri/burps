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

#include <burps/math/localization.h>
#include <burps/math/logTable.h>
#include <stdlib.h>

using namespace burps;
using namespace std;


Localization::Localization() : _totalSize( 0 ), _totalVoid( 0 )
{
}


Localization::~Localization()
{
}


const vector<string> & Localization::parts() const
{
  return( _parts );
}


double Localization::size( const string & part ) const
{
  unsigned	i, n = _parts.size();

  for( i=0; i<n && _parts[i]!=part; ++i );
  if( i == n )
    return( 0 );	// not found
  return( _sizes[i] );
}


double Localization::voidSpace( const string & part ) const
{
  unsigned	i, n = _parts.size();

  for( i=0; i<n && _parts[i]!=part; ++i );
  if( i == n )
    return( 0 );	// not found
  return( _voids[i] );
}


double Localization::pSize( const string & part ) const
{
  return( size( part ) / totalSize() );
}


double Localization::pVoid( const string & part ) const
{
  return( voidSpace( part ) / totalSize() );
}


double Localization::totalSize() const
{
  if( _totalSize == 0 )
    {
      unsigned	i, n = _sizes.size();

      for( i=0; i<n; ++i )
	_totalSize += _sizes[i];
    }

  return( _totalSize );
}


double Localization::totalVoid() const
{
  if( _totalVoid == 0 )
    {
      unsigned	i, n = _voids.size();

      for( i=0; i<n; ++i )
	_totalVoid += _voids[i];
    }

  return( _totalVoid );
}


const vector<string> & Localization::order( const string & part ) const
{
  static vector<string>	dummy;
  map<string, vector<string> >::const_iterator	ip = _orders.find( part );

  if( ip == _orders.end() )
    return( dummy );
  return( (*ip).second );
}


double Localization::sumSize( const string & aimpart, int pos ) const
{
  const vector<string> & ord = order( aimpart );
  if( pos > ((int) ord.size() ) - 1 )
    pos = ord.size() - 1;

  double	s = 0, e = 0, ev = 0;
  int		i, ie = -1;

  for( i=0; i<=pos; ++i )
    {
      const string & p = ord[i];
      if( p == "empty" )
	{
	  ie = true;
	  ev = e;
	}
      else if( p[0] == '*' )	// both sizes
	{
	  string	ps( p.substr( 1, p.length() - 1 ) );
	  string	ls( string( "left" ) + ps );
	  string	rs( string( "right" ) + ps );
	  s += pSize( ls );
	  s += pSize( rs );
	  e += pVoid( ls );
	  e += voidSpace( rs );
	}
      else
	{
	  s += pSize( p );
	  e += voidSpace( p );
	}
    }

  if( ie >= 0 )	// count empty voids too
    {
      for( ; i<(int) ord.size() && ord[i]!="empty"; ++i );
      if( i == (int) ord.size() )	// last empty
	{
	  s += totalVoid();	// all voids counted
	}
      else
	{
	  s += ev;		// empty remaining
	}
    }

  return( s );
}


string Localization::localize( const string & aimpart, double dieroll, 
			       const BTable & tab, double adj ) const
{
  return( localize( aimpart, tab.inv( dieroll ) + adj ) );
}


string Localization::localize( const string & aimpart, double margin, 
			       bool specifySide ) const
{
  buildDistances();

  const vector<string>	& ord = order( aimpart );

  if( ord.empty() )
    return( "" );

  const vector<double>	& sz = (*_dist.find( aimpart )).second;
  unsigned		i, n = sz.size();
  static LogTable	logt;
  double		dist = logt( margin );

  for( i=0; i<n && sz[i] < dist; ++i );
  if( i == n )
    return( "" );

  string		part = ord[i];

  if( part[0] == '*' )
    {
      if( specifySide )
	{
	  if( rand() & 1 )
	    part.replace( 0, 1, "left" );
	  else
	    part.replace( 0, 1, "right" );
	}
      else
	{
	  if( part[1] == ' ' )
	    part.erase( 0, 2 );
	  else
	    part.erase( 0, 1 );
	}
    }
  else if( part == "empty" )
    part = "";

  return( part );
}


void Localization::buildDistances() const
{
  if( !_dist.empty() )
    return;

  map<string, vector<string> >::const_iterator	ip, ep = _orders.end();
  unsigned					i, n;
  double					vd, olds;

  for( ip=_orders.begin(); ip!=ep; ++ip )
    {
      const string		& aimpart = (*ip).first;
      const vector<string>	& p = (*ip).second;
      vector<double>		& sz = _dist[ aimpart ];

      vd = voidSpace( aimpart );
      olds = 0;
      //cout << "aim : " << aimpart << ", void : " << vd << endl;
      for( i=0, n=p.size(); i<n; ++i )
	{
	  const string	& pt = p[i];

	  if( pt == "empty" )
	    {
	      olds += vd;
	    }
	  else if( pt[0] == '*' )	// bilateral loc.
	    {
	      string	sp = pt.substr( 1, pt.length() - 1 );
	      olds += pSize( string( "left" ) + sp );
	      olds += pSize( string( "right" ) + sp );
	    }
	  else
	    {
	      olds += pSize( p[i] );
	    }
	  //cout << "size " << i << " : " << olds << endl;
	  sz.push_back( olds ); //sqrt( olds / M_PI );
	}
    }
}


//


ManLocalization::ManLocalization() : Localization()
{
  _parts.push_back( "head" );
  _parts.push_back( "thorax" );
  _parts.push_back( "abdomen" );
  _parts.push_back( "left arm" );
  _parts.push_back( "right arm" );
  _parts.push_back( "left leg" );
  _parts.push_back( "right leg" );

  _sizes.push_back( 6.3 );
  _sizes.push_back( 16.8 );
  _sizes.push_back( 17.5 );
  _sizes.push_back( 9.95 );
  _sizes.push_back( 9.95 );
  _sizes.push_back( 19.75 );
  _sizes.push_back( 19.75 );

  _voids.push_back( 0.5025 );
  _voids.push_back( 0.378 );
  _voids.push_back( 0.2444 );
  _voids.push_back( 0.5347 );
  _voids.push_back( 0.5347 );
  _voids.push_back( 0.7698 );
  _voids.push_back( 0.7698 );

  vector<string>	& hd = _orders[ "head" ];
  hd.push_back( "head" );
  hd.push_back( "empty" );
  hd.push_back( "thorax" );
  hd.push_back( "* arm" );
  hd.push_back( "abdomen" );
  hd.push_back( "* leg" );
  vector<string>	& th = _orders[ "thorax" ];
  th.push_back( "thorax" );
  th.push_back( "head" );
  th.push_back( "abdomen" );
  th.push_back( "empty" );
  th.push_back( "* arm" );
  th.push_back( "* leg" );
  vector<string>	& ab = _orders[ "abdomen" ];
  ab.push_back( "abdomen" );
  ab.push_back( "thorax" );
  ab.push_back( "empty" );
  ab.push_back( "* leg" );
  ab.push_back( "* arm" );
  ab.push_back( "head" );
  vector<string>	& ar = _orders[ "left arm" ];
  ar.push_back( "left arm" );
  ar.push_back( "empty" );
  ar.push_back( "thorax" );
  ar.push_back( "abdomen" );
  ar.push_back( "left leg" );
  ar.push_back( "head" );
  ar.push_back( "right arm" );
  ar.push_back( "right leg" );
  vector<string>	& lg = _orders[ "left leg" ];
  lg.push_back( "left leg" );
  lg.push_back( "right leg" );
  lg.push_back( "empty" );
  lg.push_back( "abdomen" );
  lg.push_back( "thorax" );
  lg.push_back( "left arm" );
  lg.push_back( "right arm" );
  lg.push_back( "head" );
}


ManLocalization::~ManLocalization()
{
}


