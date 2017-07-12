// 
// $Id: computerconfig.hpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Definition of ComputerConfig class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 20:24:16 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef COMPUTERCONFIG_HPP
#define COMPUTERCONFIG_HPP

#include "playerprofile.hpp"
#include "computerbrain.hpp"

#include <qdialog.h>
#include <qspinbox.h>
#include <qwidget.h>

class ComputerConfig : public QDialog
{
    Q_OBJECT
public:
    ComputerConfig( PlayerProfile *p, ComputerBrain *b, QWidget *parent = 0, const char *name = 0 );
    virtual ~ComputerConfig();

    int timeoutValue() const { return Val; }
    int limitValue() const { return LVal; }

private slots:
    void valueChanged( int );
    void limitValueChanged( int );

private:
    PlayerProfile *pPly;
    ComputerBrain *pBrain;
    QSpinBox *pBox;
    QSpinBox *pLimit;
    int Val;
    int LVal;
};


#endif // COMPUTERCONFIG_HPP
