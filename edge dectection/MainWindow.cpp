#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AboutDialog.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    mPicture = 0;
    mCurrentPath = "";

    m_ui->scrollArea->setWidgetResizable(true);
    //m_ui->lblImage->setScaledContents(true);
    m_ui->lblImage->setAlignment(Qt::AlignCenter);
    m_ui->lblImage->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);
    m_ui->scrollArea->setMinimumSize(240, 160);

    // Commands
    connect(m_ui->cmdLoad, SIGNAL(triggered()), SLOT(slotLoad()));
    connect(m_ui->cmdSave, SIGNAL(triggered()), SLOT(slotSave()));
    connect(m_ui->cmdCanny, SIGNAL(clicked()), SLOT(slotCanny()));
    connect(m_ui->cmdShowOriginal, SIGNAL(toggled(bool)), SLOT(slotUpdate()));
    connect(m_ui->cmdReload, SIGNAL(clicked()), SLOT(slotReload()));
    connect(m_ui->cmdReloadAction, SIGNAL(triggered()), SLOT(slotReload()));
    connect(m_ui->cmdAbout, SIGNAL(triggered()), SLOT(slotAbout()));

    // Hysteresis
    connect(m_ui->chkHysteresis, SIGNAL(clicked()), SLOT(slotUpdate()));
    connect(m_ui->sliderHysteresisLow, SIGNAL(sliderMoved(int)), SLOT(slotUpdate()));
    connect(m_ui->sliderHysteresisHigh, SIGNAL(sliderMoved(int)), SLOT(slotUpdate()));
    connect(m_ui->spinHysteresisLow, SIGNAL(editingFinished()), SLOT(slotUpdateFromSpins()));
    connect(m_ui->spinHysteresisHigh, SIGNAL(editingFinished()), SLOT(slotUpdateFromSpins()));

}

MainWindow::~MainWindow()
{
    if(mPicture != 0)
        delete mPicture;
    delete m_ui;
}

void MainWindow::resizeEvent(QResizeEvent * e)
{
    redisplay();
    QMainWindow::resizeEvent(e);
}

void MainWindow::slotAbout()
{
    AboutDialog * dialog = new AboutDialog(this);
    dialog->exec();
    delete dialog;
}

void MainWindow::slotLoad(QString path)
{
    if(mPicture != 0)
        delete mPicture;

    if(path == "")
        mCurrentPath = QFileDialog::getOpenFileName(this, "Please select an image...", ".", "Images (*.png *.bmp *.gif *.xpm *.jpg)");
    else
        mCurrentPath = path;

    if(mCurrentPath == "") return;

    mPicture = new CImage(mCurrentPath);
    redisplay();
}

void MainWindow::slotReload()
{
    slotLoad(mCurrentPath);
}

void MainWindow::slotSave()
{
    bool fail = (mPicture == 0);
    if(!fail)
        if(mPicture->mImage->isNull())
            fail = true;
    if(fail) {
        QMessageBox::critical(this, "Error", "No file to save!");
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, "Please select a path to save to...", "out.jpg", "*.jpg");
    mPicture->mImage->save(path);
}

void MainWindow::slotCanny()
{
    if(mPicture == 0) return;

    mPicture->canny(
            m_ui->spinBlurSigma->value(),
            m_ui->chkR->isChecked(),
            m_ui->chkG->isChecked(),
            m_ui->chkB->isChecked());

    if(m_ui->cmdShowOriginal->isChecked())
        m_ui->cmdShowOriginal->setChecked(false);
    else
        slotUpdate();
}

void MainWindow::redisplay()
{
    if(mPicture == 0) return;

    if(m_ui->cmdShowOriginal->isChecked())
        mDisplayImage = QPixmap::fromImage(*mPicture->mOriginalImage);
    else
        mDisplayImage = QPixmap::fromImage(*mPicture->mImage);
    m_ui->lblImage->setPixmap(
            mDisplayImage.scaled(m_ui->lblImage->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
}

void MainWindow::slotUpdate()
{
    double low = m_ui->sliderHysteresisLow->value()/1000.;
    double high = m_ui->sliderHysteresisHigh->value()/1000.;
    if(low > high) {
        low = high;
        m_ui->sliderHysteresisLow->setValue(m_ui->sliderHysteresisHigh->value());
    }

    m_ui->spinHysteresisHigh->setValue(high);
    m_ui->spinHysteresisLow->setValue(low);

    if(mPicture == 0) return;

    if(!m_ui->cmdShowOriginal->isChecked()) {
        if(m_ui->chkHysteresis->isChecked()) {
            mPicture->useHysteresis(low, high);
        } else
            mPicture->useSuppressed();
    }

    redisplay();
}

void MainWindow::slotUpdateFromSpins()
{
    m_ui->sliderHysteresisLow->setValue(m_ui->spinHysteresisLow->value()*1000);
    m_ui->sliderHysteresisHigh->setValue(m_ui->spinHysteresisHigh->value()*1000);
}
