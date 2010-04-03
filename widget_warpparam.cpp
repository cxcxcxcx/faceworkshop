#include "widget_warpparam.h"
#include "ui_widget_warpparam.h"

#include "imgtranspiecewiseaffine.h"

Widget_WarpParam::Widget_WarpParam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_WarpParam)
{
    ui->setupUi(this);

    ui->cmbSkeletonWarpAlg->addItem(tr("Cumulative"));
    ui->cmbSkeletonWarpAlg->addItem(tr("Cumulative Key-Point Accurate"));
    ui->cmbSkeletonWarpAlg->addItem(tr("Key-Point Stable"));
}

Widget_WarpParam::~Widget_WarpParam()
{
    delete ui;
}

void Widget_WarpParam::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget_WarpParam::processImage(
                ASMModel &model,
                const vector< WarpControl > &warpControls,
                const vector< Point2i > &oldPoints,
                vector< Point2i > &newPoints)
{
    int skeletonWarpAlg = ui->cmbSkeletonWarpAlg->currentIndex();
    if (skeletonWarpAlg==0)
        interactiveImageWarping( warpControls,
                             oldPoints, newPoints );
    else if (skeletonWarpAlg==1)
        interactiveStableImageWarping( warpControls,
                             oldPoints, newPoints );
    else
        pointStableImageWarping( warpControls,
                             oldPoints, newPoints );

    if (ui->chkHumanLike->isChecked()){
        vector< Point2i > uPV;
        projectPListToShapeModel(model, newPoints, uPV);
        newPoints = uPV;
    }

}

void Widget_WarpParam::on_chkHumanLike_toggled(bool checked)
{
    emit updated();
}
