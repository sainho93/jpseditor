#ifndef OPENDXFDIALOG_H
#define OPENDXFDIALOG_H

#include <QDialog>
#include "src/datamanager.h"

namespace Ui {
class OpenDXFDialog;
}

class OpenDXFDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDXFDialog(QWidget *parent = nullptr, jpsDatamanager* dmanager = nullptr);
    ~OpenDXFDialog();

public slots:
    void openButtonClicked();
    void addToImportButtonClicked();

private:
    Ui::OpenDXFDialog *ui;
    jpsDatamanager *data;
};

#endif // OPENDXFDIALOG_H
