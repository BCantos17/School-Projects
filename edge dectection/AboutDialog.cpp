#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);

    connect(m_ui->cmdOK, SIGNAL(clicked()), SLOT(slotOK()));
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}
