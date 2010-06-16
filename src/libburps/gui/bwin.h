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

#ifndef BURPS_GUI_BWIN_H
#define BURPS_GUI_BWIN_H


#include <qmainwindow.h>

namespace burps
{
  class BTable;
}

struct BMain_PrivateData;


class BMain : public QMainWindow
{
  Q_OBJECT

public:
#if QT_VERSION >= 0x040000
  typedef Qt::WindowFlags WFlags;
#endif

  BMain( QWidget* parent = 0, const char* name = 0,
         WFlags f = Qt::WType_TopLevel | Qt::WDestructiveClose );
  virtual ~BMain();

public slots:
  void gaussTable();
  void sigmoTable();
  void orTable();
  void logTable();
  void gaussTableInv();
  void sigmoTableInv();
  void orTableInv();
  void logTableInv();
  void localization();

protected:
  void plot( const burps::BTable & t, double xmin, double xmax, double inc, 
	     const char* name );

private:
  BMain_PrivateData	*d;

};


#endif

