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

#include <burps/gui/bwin.h>
#include <burps/math/gaussTable.h>
#include <burps/math/sigmoTable.h>
#include <burps/math/orTable.h>
#include <burps/math/localization.h>
#include <burps/gui/locwin.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <QPen>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#if QWT_VERSION >= 0x060000
#include <qwt_point_data.h>
#endif
#include <qapplication.h>


using namespace burps;


BMain::BMain( QWidget* parent, const char* name, Qt::WindowFlags f )
  : QMainWindow( parent, f )
{
  setAttribute( Qt::WA_DeleteOnClose );
  setWindowTitle( tr( "BURPS" ) );
  setObjectName( name );

#if QT_VERSION >= 0x040000
  QMenu *fi = menuBar()->addMenu( tr( "File" ) );
  fi->addAction( tr( "Quit" ), qApp, SLOT( quit() ), Qt::CTRL+Qt::Key_Q );

  QMenu *tb = menuBar()->addMenu( tr( "Tables" ) );
  tb->addAction( tr( "Gaussian" ), this, SLOT( gaussTable() ) );
  tb->addAction( tr( "Sigmoid (opposition)" ), this, SLOT( sigmoTable() ) );
  tb->addAction( tr( "Or" ), this, SLOT( orTable() ) );
  tb->addAction( tr( "Exponential" ), this, SLOT( logTable() ) );
  tb->addAction( tr( "Shooting localization" ), this,
                 SLOT( localization() ) );
  tb->addAction( tr( "Melee localization" ) );
  tb->addSeparator();
  tb->addAction( tr( "Inverse Gaussian" ), this, SLOT( gaussTableInv() ) );
  tb->addAction( tr( "Inverse Sigmoid (opposition)" ), this,
                 SLOT( sigmoTableInv() ) );
  tb->addAction( tr( "Inverse Or" ), this, SLOT( orTableInv() ) );
  tb->addAction( tr( "Inverse Exponential" ), this, SLOT( logTableInv() ) );

  QMenu    *ch = menuBar()->addMenu( tr( "Character" ) );
  ch->addAction( tr( "Character creation" ) );

  QMenu    *si = menuBar()->addMenu( tr( "Simulation" ) );
  si->addAction( tr( "Combat simulation" ) );
#else
  QPopupMenu	*fi = new QPopupMenu;
  menuBar()->insertItem( tr( "File" ), fi );
  fi->insertItem( tr( "Quit" ), qApp, SLOT( quit() ), Qt::CTRL+Qt::Key_Q );

  QPopupMenu	*tb = new QPopupMenu;
  menuBar()->insertItem( tr( "Tables" ), tb );
  tb->insertItem( tr( "Gaussian" ), this, SLOT( gaussTable() ) );
  tb->insertItem( tr( "Sigmoid (opposition)" ), this, SLOT( sigmoTable() ) );
  tb->insertItem( tr( "Or" ), this, SLOT( orTable() ) );
  tb->insertItem( tr( "Exponential" ), this, SLOT( logTable() ) );
  tb->insertItem( tr( "Shooting localization" ), this, 
		  SLOT( localization() ) );
  tb->insertItem( tr( "Melee localization" ) );
  tb->insertSeparator();
  tb->insertItem( tr( "Inverse Gaussian" ), this, SLOT( gaussTableInv() ) );
  tb->insertItem( tr( "Inverse Sigmoid (opposition)" ), this, 
		  SLOT( sigmoTableInv() ) );
  tb->insertItem( tr( "Inverse Or" ), this, SLOT( orTableInv() ) );
  tb->insertItem( tr( "Inverse Exponential" ), this, SLOT( logTableInv() ) );

  QPopupMenu	*ch = new QPopupMenu;
  menuBar()->insertItem( tr( "Character" ), ch );
  ch->insertItem( tr( "Character creation" ) );

  QPopupMenu	*si = new QPopupMenu;
  menuBar()->insertItem( tr( "Simulation" ), si );
  si->insertItem( tr( "Combat simulation" ) );
#endif

  resize( 300, 50 );
}


BMain::~BMain()
{
}


void BMain::plot( const BTable & tab, double xmin, double xmax, double inc, 
		  const QString & name )
{
#if QWT_VERSION >= 0x060000
  QwtPlot     *gt = new QwtPlot( 0 );

  unsigned n = unsigned( ( xmax - xmin ) / inc );
  QVector<double> x( n ), y( n );
  double	t;
  unsigned	i;
  unsigned	curve;

  gt->setAutoReplot( true );

  QwtPlotMarker *pmark1 = new QwtPlotMarker;
  pmark1->attach( gt );
  pmark1->setLinePen( QPen( QColor( 255, 255, 255 ) ) );
  pmark1->setLineStyle( QwtPlotMarker::VLine );

  QwtPlotCurve      *crv = new QwtPlotCurve( name );
  crv->attach( gt );

  for( i=0, t=xmin; t<=xmax; ++i, t+=inc )
    {
      x[i] = t;
      y[i] = tab( t );
    }

  gt->setAxisAutoScale( false );

  QwtPointArrayData<double> *pd = new QwtPointArrayData<double>( x, y );
  crv->setData( pd );

#else

  #if QWT_VERSION >= 0x050000
  QwtPlot     *gt = new QwtPlot( 0 );
  #else
  QwtPlot       *gt = new QwtPlot( name, 0, 0 );

  #endif

  double        x[101], y[101];
  double        t;
  unsigned      i;
  unsigned      curve;

  gt->setAutoReplot( true );

  #if QWT_VERSION >= 0x050000
  QwtPlotMarker *pmark1 = new QwtPlotMarker;
  pmark1->attach( gt );
  pmark1->setLinePen( QPen( QColor( 255, 255, 255 ) ) );
  pmark1->setLineStyle( QwtPlotMarker::VLine );

  QwtPlotCurve      *crv = new QwtPlotCurve( name );
  crv->attach( gt );
  #else
  curve = gt->insertCurve( name );
  #endif
  for( i=0, t=xmin; t<=xmax; ++i, t+=inc )
    {
      x[i] = t;
      y[i] = tab( t );
    }

  gt->setAxisAutoScale( false );

  #if QWT_VERSION >= 0x050000
  crv->setData( x, y, i );
  #else
  //int	xa = gt->curveXAxis( curve );
  gt->setCurveData( curve, x, y, i );
  /*gt->setAxisScale( xa, xmin, xmax, 6. );
  gt->setGridXAxis( xa );
  gt->enableGridX();
  gt->setGridYAxis( gt->curveYAxis( curve ) );
  gt->enableGridY();*/
  #endif
#endif
  gt->replot();
  gt->show();
}


void BMain::gaussTable()
{
  GaussTable	tab;
  plot( tab, -40, 40, 1, tr( "Gaussian table" ) );
}


void BMain::gaussTableInv()
{
  GaussTable	tab;
  BTable	*t = tab.inverse();
  plot( *t, 0.01, 0.99, 0.01, tr( "Inverse Gaussian table" ) );
  delete t;
}


void BMain::sigmoTable()
{
  SigmoTable	tab;
  plot( tab, -40, 40, 1, tr( "Sigmoid / Opposition table" ) );
}


void BMain::sigmoTableInv()
{
  SigmoTable	tab;
  BTable	*t = tab.inverse();
  plot( *t, 0.01, 0.99, 0.01, tr( "Inverse Sigmoid / Opposition table" ) );
  delete t;
}


void BMain::orTable()
{
  OrTable	tab;
  plot( tab, -40, 40, 1, tr( "Or table" ) );
}


void BMain::orTableInv()
{
  OrTable	tab;
  BTable	*t = tab.inverse();
  plot( *t, 0.01, 0.99, 0.01, tr( "Inverse Or table" ) );
  delete t;
}


void BMain::logTable()
{
  LogTable	tab;
  plot( tab, -40, 40, 1, tr( "Exponential table" ) );
}


void BMain::logTableInv()
{
  LogTable	tab;
  BTable	*t = tab.inverse();
  plot( *t, 0.01, 0.99, 0.01, tr( "Inverse Exponential table" ) );
  delete t;
}


void BMain::localization()
{
  ManLocalization	*loc = new ManLocalization;
  LocWin		*lw = new LocWin( loc );
  lw->show();
}


