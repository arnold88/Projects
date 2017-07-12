// 
// $Id: humanconfig.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of HumanConfig class
//
// Jan Borsodi <jb@ez.no>
// Created on: <19-Oct-1999 17:54:33 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "humanconfig.hpp"
#include <qdialog.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qpushbutton.h>

/*!
  \class HumanConfig humanconfig.hpp
  \brief

*/

/*!
  Default constructor
*/

HumanConfig::HumanConfig( const QString &pname, bool markers, const QString &toptext, QWidget *parent, const char *name )
    : QDialog( parent, name, true )
{
//      pPly = p;
//      pBrain = b;
//      CHECK_PTR( p );
//      CHECK_PTR( b );

    setCaption( toptext );
    QVBoxLayout *lay = new QVBoxLayout( this, 0, 4 );
    {
        QGroupBox *box = new QGroupBox( "Player information", this );
        lay->addWidget( box, 1 );
        {
            QVBoxLayout *vlay = new QVBoxLayout( box, 5 );
            vlay->addSpacing( box->fontMetrics().lineSpacing() );
            {
                pName = new QLineEdit( pname, box );
                vlay->addWidget( pName, 0 );

                pCheck = new QCheckBox( tr( "Markers on" ), box );
                pCheck->setChecked( markers );
                vlay->addWidget( pCheck, 0 );

                vlay->addStretch( 1 );
            }
        }

        QHBoxLayout *blay = new QHBoxLayout( 5 );
        lay->addLayout( blay, 0 );
        {
            blay->addStretch( 1 );

            QPushButton *Ok = new QPushButton( tr( "OK" ), this );
            Ok->setDefault( true );
            blay->addWidget( Ok, 0 );

            QPushButton *Cancel = new QPushButton( tr( "Cancel" ), this );
            blay->addWidget( Cancel, 0 );

            connect( Ok, SIGNAL( clicked() ),
                     this, SLOT( accept() ) );
            connect( Cancel, SIGNAL( clicked() ),
                     this, SLOT( reject() ) );
        }
    }

    resize( 210, sizeHint().height() );
    setFixedHeight( sizeHint().height() );
}

/*!
  Destroys the object
*/

HumanConfig::~HumanConfig()
{
}

QString HumanConfig::playerName() const
{
    return pName->text();
}

bool HumanConfig::markersOn() const
{
    return pCheck->isChecked();
}
