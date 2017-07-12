// 
// $Id: humanconfig.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of HumanConfig class
//
// Jan Borsodi <jb@ez.no>
// Created on: <19-Oct-1999 17:54:34 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef HUMANCONFIG_HPP
#define HUMANCONFIG_HPP

#include "humanbrain.hpp"
#include "playerprofile.hpp"

#include <qdialog.h>
#include <qwidget.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qstring.h>

class HumanConfig : public QDialog
{
public:
    HumanConfig( const QString &pname, bool markers, const QString &toptext, QWidget *parent = 0, const char *name = 0 );
    virtual ~HumanConfig();

    QString playerName() const;
    bool markersOn() const;

private:
    PlayerProfile *pPly;
    HumanBrain *pBrain;
    QLineEdit *pName;
    QCheckBox *pCheck;
};


#endif // HUMANCONFIG_HPP
