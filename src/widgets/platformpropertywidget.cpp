/***************************************************************
 *
 * \file platformpropertywidget.cpp
 * \date 2019-06-25
 * \version 
 * \author Tao Zhong
 * \copyright <2009-2019> Forschungszentrum Jülich GmbH. All rights reserved.
 *
 * \section Lincense
 * This file is part of JuPedSim.
 *
 * JuPedSim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JuPedSim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with JuPedSim. If not, see <http://www.gnu.org/licenses/>.
 *
 * \section Description
 *
 * This class is for platform property Dockwidget
****************************************************************/

#include "platformpropertywidget.h"
#include "ui_platformpropertywidget.h"

PlatformPropertyWidget::PlatformPropertyWidget(QWidget *parent, jpsDatamanager *dmanager, jpsGraphicsView *gview)
    : QWidget(parent), ui(new Ui::PlatformPropertyWidget)
{
    ui->setupUi(this);

    data = dmanager;
    view = gview;
    current_zone = nullptr;

    updateListWidget();
    updateTrackListWidget();

    // Add wall/track into platform
    connect(ui->pushButton_addWall, SIGNAL(clicked()), this, SLOT(addWallButtonClicked()));
    connect(ui->pushButton_addTrack,  SIGNAL(clicked()), this, SLOT(addTrackButtonClicked()));
    // Remove wall/track from platform
    connect(ui->pushButton_removeWall, SIGNAL(clicked()), this, SLOT(removeWallButtonClicked()));
    connect(ui->pushButton_removeTrack,  SIGNAL(clicked()), this, SLOT(removeTrackButtonClicked()));
    // Change/Update number of line
    connect(ui->pushButton_applyNumber, SIGNAL(clicked()), this, SLOT(applyNumberButtonClicked()));
    connect(ui->listWidget_tracks, SIGNAL(itemSelectionChanged()), this, SLOT(updateNumberLineEdit()));
    // Hightlight
    connect(ui->listWidget_walls, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(highlightWall(QListWidgetItem *)));
    connect(ui->listWidget_tracks, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(highlightTrack(QListWidgetItem *)));
}

PlatformPropertyWidget::~PlatformPropertyWidget()
{
    delete ui;
}

void PlatformPropertyWidget::addWallButtonClicked()
{
    qDebug("Enter PlatformPropertyWidget::addWallButtonClicked");
    if(!view->get_markedLines().isEmpty())
    {
        foreach(jpsLineItem *line, view->get_markedLines())
        {
            if(line->getType() == "wall")
                current_zone->addWall(line);
        }

        updateListWidget();
    }
    qDebug("Leave PlatformPropertyWidget::addWallButtonClicked");
}

void PlatformPropertyWidget::receiveJPSZone(JPSZone *zone)
{
    qDebug("Enter PlatformPropertyWidget::receiveJPSZone");
    current_zone = zone;
    updateListWidget();
    qDebug("Leave PlatformPropertyWidget::receiveJPSZone");
}

/*
    Purpose: Update wall listWidget, track listWidget, and number lineEdit

    Note: This function cleared number, but does't update number. See more in
*/
void PlatformPropertyWidget::updateListWidget()
{
    qDebug("Enter PlatformPropertyWidget::updateListWidget");
    ui->listWidget_walls->clear();
    ui->listWidget_tracks->clear();
    ui->lineEdit->clear();

    if(current_zone != nullptr)
    {
        QList<jpsLineItem *> walllist = current_zone->get_listWalls();
        for(int i=0; i<walllist.size(); i++)
        {
            QString string = "";
            string.sprintf("[%+06.3f, %+06.3f] - [%+06.3f, %+06.3f]",
                           walllist[i]->get_line()->line().x1(),
                           walllist[i]->get_line()->line().x2(),
                           walllist[i]->get_line()->line().y1(),
                           walllist[i]->get_line()->line().y2());

            ui->listWidget_walls->addItem(string);
        }

        QList<JPSTrack *> tracklist = current_zone->getTrackList();
        for (int j = 0; j < tracklist.size(); ++j) {
            QString string = "";
            string.sprintf("[%+06.3f, %+06.3f] - [%+06.3f, %+06.3f]",
                           tracklist[j]->getLine()->get_line()->line().x1(),
                           tracklist[j]->getLine()->get_line()->line().x2(),
                           tracklist[j]->getLine()->get_line()->line().y1(),
                           tracklist[j]->getLine()->get_line()->line().y2());

            ui->listWidget_tracks->addItem(string);
        }
    }
    qDebug("Leave PlatformPropertyWidget::updateListWidget");
}

/*
    Purpose: Change number of track from input in LineEdit
*/
void PlatformPropertyWidget::applyNumberButtonClicked()
{
    qDebug("Enter PlatformPropertyWidget::applyNumberButtonClicked");
    QString number = ui->lineEdit->text();

    int cRow = ui->listWidget_tracks->currentRow();
    JPSTrack *current_track = current_zone->getTrackList()[cRow];

    current_track->setNumber(number);
    qDebug("Leave PlatformPropertyWidget::applyNumberButtonClicked");
}

void PlatformPropertyWidget::addTrackButtonClicked()
{
    qDebug("Enter PlatformPropertyWidget::addTrackButtonClicked");
    if(!view->get_markedLines().isEmpty())
    {
        foreach(jpsLineItem *marked_line, view->get_markedLines())
        {
            if(marked_line->getType() == "track")
            {
                QString number = ui->lineEdit->text();
                current_zone->addTrack(marked_line, number);
            }
        }

        updateTrackListWidget();
    }
    qDebug("Leave PlatformPropertyWidget::addTrackButtonClicked");
}

void PlatformPropertyWidget::updateTrackListWidget()
{
    qDebug("Enter PlatformPropertyWidget::updateTrackListWidget");
    ui->listWidget_tracks->clear();

    if(current_zone != nullptr)
    {
        QList<JPSTrack *> tracks = current_zone->getTrackList();
        for (int i=0; i<tracks.size(); i++)
        {
            QString string = "";
            string.sprintf("[%+06.3f, %+06.3f] - [%+06.3f, %+06.3f]",
                           tracks[i]->getLine()->get_line()->line().x1(),
                           tracks[i]->getLine()->get_line()->line().x2(),
                           tracks[i]->getLine()->get_line()->line().y1(),
                           tracks[i]->getLine()->get_line()->line().y2());

            ui->listWidget_tracks->addItem(string);
        }
    }
    qDebug("Leave PlatformPropertyWidget::updateTrackListWidget");
}

/*
    Purpose: Update content in LineEdit, when selection in listWidget_tracks changed.

    Note: Default number of track is 0, but it won't be showed.
*/
void PlatformPropertyWidget::updateNumberLineEdit()
{
    qDebug("Enter PlatformPropertyWidget::updateNumberLineEdit");
    int cRow = ui->listWidget_tracks->currentRow();

    if(cRow == -1) // There is no rows in list
    {
        qDebug("No row is selected. Leave PlatformPropertyWidget::updateNumberLineEdit");
        return;
    }

    JPSTrack *current_track = current_zone->getTrackList()[cRow];
    QString number = current_track->getNumber();

    ui->lineEdit->setText(number);
    qDebug("Leave PlatformPropertyWidget::updateNumberLineEdit");
}

/*
    Purpose: Highlight selected wall in listWidget_walls.

    Note: Hightlighting operation is by jpsGraphicsView::select_line.
*/
void PlatformPropertyWidget::highlightWall(QListWidgetItem *item)
{
    qDebug("Enter PlatformPropertyWidget::highlightWall");
    int row = ui->listWidget_walls->currentRow();

    if(row == -1) // There is no rows in list
    {
        qDebug("No row is selected. Leave PlatformPropertyWidget::highlightWall");
        return;
    }

    jpsLineItem *wall= current_zone->get_listWalls()[row];
    view->select_line(wall);
    qDebug("Leave PlatformPropertyWidget::highlightWall");

}

/*
    Purpose: Highlight selected track in listWidget_tracks.

    Note: Hightlighting operation is by jpsGraphicsView::select_line.
*/
void PlatformPropertyWidget::highlightTrack(QListWidgetItem *item)
{
    int row = ui->listWidget_tracks->currentRow();

    if(row == -1) // There is no rows in list
        return;

    JPSTrack *track = current_zone->getTrackList()[row];
    view->select_line(track->getLine());
}

/*
    Purpose: Remove wall from wall_lists
*/
void PlatformPropertyWidget::removeWallButtonClicked()
{
    int row = ui->listWidget_walls->currentRow();

    if(row == -1) // There is no rows in list
        return;

    jpsLineItem *wall = current_zone->get_listWalls()[row];

    current_zone->removeWall(wall);

    ui->listWidget_walls->setCurrentRow(-1); // Set no focus

    updateListWidget();
}

/*
    Purpose: Remove track from track_lists

    Note: Set no focus after removing, otherwise updateNumberLineEdit() will get wrong currentRow
*/
void PlatformPropertyWidget::removeTrackButtonClicked()
{
    int row = ui->listWidget_tracks->currentRow();

    if(row == -1) // There is no focus in list
        return;

    JPSTrack *track = current_zone->getTrackList()[row];

    current_zone->removeTrack(track);

    ui->listWidget_tracks->setCurrentRow(-1);

    updateListWidget();
}