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

#ifndef BURPS_GUI_LOCWIN_H
#define BURPS_GUI_LOCWIN_H


#include <qwidget.h>


namespace burps
{
  class Localization;
}


class LocWin : public QWidget
{
  Q_OBJECT

public:
  LocWin( burps::Localization *loc, QWidget* parent = 0, const char* name = 0, 
          Qt::WindowFlags f = Qt::WindowFlags() );
  virtual ~LocWin();

protected:
  burps::Localization	*_loc;

private:
};


#endif

