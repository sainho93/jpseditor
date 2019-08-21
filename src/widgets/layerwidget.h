#ifndef JPSEDITOR_LAYERWIDGET_H
#define JPSEDITOR_LAYERWIDGET_H

#include <QtGui>
#include <QtWidgets>
#include "src/GraphicView.h"
#include "src/models/layer.h"

namespace Ui {
    class LayerWidget;
}

class LayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LayerWidget(QWidget *parent = nullptr, jpsGraphicsView *mview = nullptr);

    ~LayerWidget();

protected slots:
    void addLayerButtonClicked();
    void updateLayerListWidget();
    void renameLayer(QListWidgetItem *item);
    void deleteLayerButtonClicked();

    void addItemsButtonClicked();
    void updateItemsListWidget();

    bool isRepeatedName(QString name);

private:
    Ui::LayerWidget *ui;
    jpsGraphicsView *view;
};


#endif //JPSEDITOR_LAYERWIDGET_H
