// 
// $Id: computerconfig.cpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Implementation of ComputerConfig class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 20:24:16 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "computerconfig.hpp"
#include <qdialog.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qwidget.h>

/*!
  \class ComputerConfig computerconfig.hpp
  \brief

*/

/*!
  Default constructor
*/

ComputerConfig::ComputerConfig( PlayerProfile *p, ComputerBrain *b, QWidget *parent, const char *name )
    : QDialog( parent, name ,true )
{
    pPly = p;
    pBrain = b;
    CHECK_PTR( p );
    CHECK_PTR( b );
    Val = b->timeout();
    LVal = b->limit();

    setCaption( tr( "Configure computer player %1" ).arg( p->profileName() ) );
    QVBoxLayout *lay = new QVBoxLayout( this, 0, 4 );
    {
        QGroupBox *box = new QGroupBox( "Computer information", this );
        lay->addWidget( box, 1 );
        {
            QVBoxLayout *vlay = new QVBoxLayout( box, 5 );
            vlay->addSpacing( box->fontMetrics().lineSpacing() );
            {
                pBox = new QSpinBox( 0, 10000, 100, box );
                pBox->setSuffix( " ms" );
                pBox->setValue( Val );
                connect( pBox, SIGNAL( valueChanged( int ) ),
                         this, SLOT( valueChanged( int ) ) );
                vlay->addWidget( pBox, 0 );

                pLimit = new QSpinBox( 0, 50, 1, box );
                pLimit->setSuffix( " level(s)" );
                pLimit->setValue( b->limit() );
                connect( pLimit, SIGNAL( valueChanged( int ) ),
                         this, SLOT( limitValueChanged( int ) ) );
                vlay->addWidget( pLimit, 0 );

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

ComputerConfig::~ComputerConfig()
{
}

void ComputerConfig::valueChanged( int v )
{
    Val = v;
}

void ComputerConfig::limitValueChanged( int v )
{
    LVal = v;
}
