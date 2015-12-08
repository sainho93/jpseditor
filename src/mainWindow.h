/**
 * \file        mainWindow.h
 * \date        Jun 26, 2015
 * \version     v0.7
 * \copyright   <2009-2015> Forschungszentrum Jülich GmbH. All rights reserved.
 *
 * \section License
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
 * This class is setting up the main window incl. all buttons and bars. It is the parent widget of all other widgets
 * (GraphicView, roomWidget, widgetLandmark).
 *
 **/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include "ui_mainwindow.h"
#include "roomwidget.h"
#include "widgetlandmark.h"
#include "GraphicView.h"
#include "datamanager.h"
#include "rooms.h"


class MWindow : public QMainWindow, private Ui::MainWindow {

    Q_OBJECT
public:
    MWindow();
    ~MWindow();


private:
    roomWidget* rwidget;
    widgetLandmark* lwidget;
    jpsDatamanager* dmanager;
    jpsGraphicsView* mview;
    //QVBoxLayout* VBox;
    QLineEdit* length_edit;
    QLabel* label1;
    QLabel* label2;
    QLabel* infoLabel;
    QString _filename;
    QTimer *timer;


protected slots:
    void openFile();
    void openFileXML();
    void saveFile();
    void saveAsDXF();
    void info();
    void gridmode();
    void en_disableWall();
    void en_disableDoor();
    void en_disableExit();
    void en_disableLandmark();
    void disableDrawing();
    void objectsnap();
    void show_coords();
    void delete_lines();
    void delete_marked_lines();
    void send_length();
    void define_room();
    void define_landmark();
    void en_selectMode();
    void dis_selectMode();
    void lines_deleted();
    void remove_all_lines();
    void rotate();
    void AutoSave();
    void add_landmark();
    void closeEvent(QCloseEvent *event);


};


#endif // MAINWINDOW_H
