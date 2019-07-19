#ifndef JPSEDITOR_PLATFORMPROPERTYWIDGET_H
#define JPSEDITOR_PLATFORMPROPERTYWIDGET_H

#include <QtGui>
#include <QtWidgets>
#include "src/datamanager.h"
#include "src/GraphicView.h"

namespace Ui {
    class PlatformPropertyWidget;
}

class PlatformPropertyWidget : public QWidget
{
    Q_OBJECT;

public:
    explicit PlatformPropertyWidget(QWidget *parent = nullptr, jpsDatamanager *dmanager = nullptr,
                                    jpsGraphicsView *gview = nullptr);

    ~PlatformPropertyWidget();

public slots:
    void receiveJPSZone(JPSZone *zone);

protected slots:
    void addWallButtonClicked();
    void addTrackButtonClicked();
    void updateListWidget();
    void applyNumberButtonClicked();
    void updateTrackListWidget();
    void updateNumberLineEdit();
    void highlightWall(QListWidgetItem *item);
    void highlightTrack(QListWidgetItem *item);


private:
    Ui::PlatformPropertyWidget *ui;
    jpsDatamanager *data;
    jpsGraphicsView *view;
    JPSZone *current_zone;

};


#endif //JPSEDITOR_PLATFORMPROPERTYWIDGET_H
