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

#include <burps/gui/locwin.h>
#include <burps/math/localization.h>
#include <burps/math/logTable.h>
#if QT_VERSION >= 0x040000
#include <qtablewidget.h>
#else
#include <qlistview.h>
#endif
#include <qlayout.h>


using namespace burps;
using namespace std;


#if QT_VERSION >= 0x040000
#if 0
class LocWinItem : public QTableWidgetItem
{
public:
  LocWinItem( bool gray, QTableView* parent, const QString & text )
    : QTableWidgetItem( parent, text ), _gray( gray ) {}
  virtual ~LocWinItem() {}
  virtual void paintCell( QPainter* p, const QColorGroup & cg, int col,
                          int width, int alignment );
  void setColumnColor( int col, const QColor & c );

protected:
  bool                  _gray;
  map<int, QColor>      _colcolors;
};
#endif
#else

class LocWinItem : public QListViewItem
{
public:
  LocWinItem( bool gray, QListView* parent, const QString & text )
    : QListViewItem( parent, text ), _gray( gray ) {}
  virtual ~LocWinItem() {}
  virtual void paintCell( QPainter* p, const QColorGroup & cg, int col, 
			  int width, int alignment );
  void setColumnColor( int col, const QColor & c );

protected:
  bool			_gray;
  map<int, QColor>	_colcolors;
};
#endif


//


LocWin::LocWin( Localization *loc, QWidget* parent, const char* name, 
		Qt::WindowFlags f )
  : QWidget( parent, f ), _loc( loc )
{
  setAttribute( Qt::WA_DeleteOnClose );
  setObjectName( name );

  unsigned	i, np = loc->parts().size(), j, n;
  LogTable	ltab;
  int		r;

  QVBoxLayout	*l = new QVBoxLayout( this );
  QTableWidget   *g = new QTableWidget( this );
  // g->setSorting( -1, false );
  g->insertColumn( 0 );
  g->setRowCount( 69 );
  g->setHorizontalHeaderItem( 0, new QTableWidgetItem( tr( "Distance :" ) ) );
  QTableWidgetItem    *gi;
  l->addWidget( g );

  vector<string>	parts;
  string		hit;
  QColor		collist[] 
    = { QColor( 255, 120, 120 ), QColor( 255, 200, 100 ),
        QColor( 255, 255, 100 ),
        QColor( 120, 255, 120 ), QColor( 40, 160, 40 ),
        QColor( 150, 150, 255 ), QColor( 80, 80, 255 ) };
  vector<QColor>	colors;
  int			col;

  for( i=0; i<np; ++i )
  {
    const string	& part = _loc->parts()[ i ];
    if( !_loc->order( part ).empty() )
    {
#if QT_VERSION >= 0x040000
      g->insertColumn( g->columnCount() );
      g->setHorizontalHeaderItem( g->columnCount() - 1,
        new QTableWidgetItem( tr( part.c_str() ) + " :" ) );
#else
      g->addColumn( tr( part.c_str() ) + " :" );
#endif
      parts.push_back( part );
    }
    colors.push_back( collist[ colors.size() % 7 ] );
  }
  n = parts.size();

  int line = 0;
  float darker = 0.85;
  for( r=34; r>=-34; --r, ++line )
  {
    double	ad = -r;
#if QT_VERSION >= 0x040000
    g->setVerticalHeaderItem( line,
      new QTableWidgetItem( QString::number( -r ) ) );
    gi = new QTableWidgetItem( QString::number( ltab( ad ) * 25 ) );
    g->setItem( line, 0, gi );
    bool isgrey = ( -r & 3 ) >= 2;
    QColor c = Qt::white;
    if( isgrey )
      c = QColor( (int) ( c.red() * darker ), (int) ( c.green() * darker ),
                  (int) ( c.blue() * darker ) );
    gi->setBackground( QBrush( c ) );
#else
    gi = new LocWinItem( ( -r & 3 ) >= 2, g,
                          QString::number( ltab( ad ) * 25 ) );
#endif

    QString	txt( QString::number( -r ) );

    for( i=0; i<n; ++i )
    {
      const string	& sp = parts[ i ];
      hit = _loc->localize( sp, ad - 0.5, false );
      QString	sz = QString( hit.c_str() );
#if QT_VERSION >= 0x040000
      gi = new QTableWidgetItem( txt + "  " + sz );
      g->setItem( line, i+1, gi );
#else
      gi->setText( i+1, txt + "  " + sz );
#endif
      col = -1;
      for( j=0; j<np; ++j )
        {
          const string	& hp = _loc->parts()[ j ];
          if( hp == hit || hp == string( "left " ) + hit
              || hp == string( "right" ) + hit )
            col = j;
        }
#if QT_VERSION >= 0x040000
      QColor c = Qt::white;
      if( col != -1 )
        c = colors[ col ];
      if( isgrey )
        c = QColor( (int) ( c.red() * darker ), (int) ( c.green() * darker ),
                    (int) ( c.blue() * darker ) );
      gi->setBackground( QBrush( c ) );
#else
      if( col != -1 )
        gi->setColumnColor( i+1, colors[ col ] );
#endif
    }
  }
}


LocWin::~LocWin()
{
  delete _loc;
}


//

#if QT_VERSION < 0x040000
void LocWinItem::paintCell( QPainter* p, const QColorGroup & cg, int col, 
                            int width, int alignment )
{
  map<int, QColor>::const_iterator	ic = _colcolors.find( col );
  bool					hasc = ( ic != _colcolors.end() );

  if( _gray || hasc )
  {
    QColorGroup	cg2( cg );
    QColor		c;
    if( hasc )
      c = QColor( (*ic).second );
    else
      c = white;
    if( _gray )
      c = QColor( (int) ( c.red() * 0.75 ), (int) ( c.green() * 0.75 ),
                  (int) ( c.blue() * 0.75 ) );
    cg2.setColor( QColorGroup::Base, c );
    QListViewItem::paintCell( p, cg2, col, width, alignment );
  }
  else
    QListViewItem::paintCell( p, cg, col, width, alignment );
}


void LocWinItem::setColumnColor( int col, const QColor & c )
{
  _colcolors[ col ] = c;
}
#endif


