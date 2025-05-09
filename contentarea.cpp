#include "ContentArea.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>
#include <QColor>
#include <QTimer> // <<< THIS INCLUDE IS CORRECT

ContentArea::ContentArea(QWidget *parent) : QWidget(parent) {
    this->setObjectName("contentArea");

    m_mainLayout = new QGridLayout(this);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    setLayout(m_mainLayout);

    QList<AlbumData> dummyAlbums;
    for (int i = 0; i < 10; ++i) {
        QPixmap placeholderPixmap(180, 180);
        placeholderPixmap.fill(QColor("#3B4252"));
        QPainter painter(&placeholderPixmap);
        painter.setPen(Qt::white);
        painter.drawText(placeholderPixmap.rect(), Qt::AlignCenter, QString("Album %1").arg(i + 1));
        painter.end();
        dummyAlbums.append({QString("Album %1 Title Example").arg(i + 1),
                            QString("Artist %1").arg(i+1),
                            placeholderPixmap});
    }
    setAlbums(dummyAlbums);

    QTimer::singleShot(0, this, [this]() {
        if (this->width() > 0) {
            relayoutAlbums(this->width());
        }
    });
}

void ContentArea::setAlbums(const QList<AlbumData>& albums) {
    m_albumDataList = albums;
    if (this->isVisible() && this->width() > 0) {
        relayoutAlbums(this->width());
    }
}

QWidget* ContentArea::createAlbumWidget(const AlbumData& albumData) {
    QWidget *albumItemWidget = new QWidget();
    albumItemWidget->setMinimumWidth(ALBUM_ITEM_MIN_WIDTH);
    albumItemWidget->setMaximumWidth(ALBUM_ITEM_WIDTH_HINT + 40);

    QVBoxLayout *albumItemLayout = new QVBoxLayout(albumItemWidget);
    albumItemLayout->setContentsMargins(5, 5, 5, 5);
    albumItemLayout->setSpacing(8);

    QLabel *imageLabel = new QLabel(albumItemWidget);
    imageLabel->setProperty("class", "albumImageLabel");
    if (!albumData.artwork.isNull()) {
        imageLabel->setPixmap(albumData.artwork.scaled(180, 180, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    } else {
        QPixmap placeholderPixmap(180, 180);
        placeholderPixmap.fill(QColor("#3B4252"));
        QPainter painter(&placeholderPixmap);
        painter.setPen(Qt::white);
        painter.drawText(placeholderPixmap.rect(), Qt::AlignCenter, "No Art");
        painter.end();
        imageLabel->setPixmap(placeholderPixmap);
    }
    imageLabel->setFixedSize(180, 180);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setScaledContents(true);

    QLabel *titleLabel = new QLabel(albumData.title, albumItemWidget);
    titleLabel->setProperty("class", "albumTitleLabel");
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    titleLabel->setWordWrap(true);
    titleLabel->setMinimumHeight(30);

    albumItemLayout->addWidget(imageLabel, 0, Qt::AlignHCenter);
    albumItemLayout->addWidget(titleLabel);

    albumItemWidget->setLayout(albumItemLayout);
    return albumItemWidget;
}

void ContentArea::relayoutAlbums(int availableWidth) {
    QLayoutItem* item;
    while ((item = m_mainLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            m_albumWidgets.removeOne(widget);
            widget->deleteLater();
        }
        delete item;
    }
    m_albumWidgets.clear();

    if (m_albumDataList.isEmpty()) {
        m_currentColumns = 0;
        return;
    }

    int leftMargin, topMargin, rightMargin, bottomMargin;
    m_mainLayout->getContentsMargins(&leftMargin, &topMargin, &rightMargin, &bottomMargin);
    int horizontalSpacing = m_mainLayout->horizontalSpacing();
    if (horizontalSpacing == -1) horizontalSpacing = m_mainLayout->spacing();

    int effectiveWidth = availableWidth - leftMargin - rightMargin;
    int itemTotalWidth = ALBUM_ITEM_WIDTH_HINT;
    int numColumns = qMax(1, effectiveWidth / itemTotalWidth);
    if (numColumns > 1) {
        numColumns = qMax(1, (effectiveWidth + horizontalSpacing) / (itemTotalWidth + horizontalSpacing));
    }

    if (numColumns == 0 && effectiveWidth > ALBUM_ITEM_MIN_WIDTH) numColumns = 1;
    else if (numColumns == 0) {
        m_currentColumns = 0;
        return;
    }
    m_currentColumns = numColumns;

    int row = 0;
    int col = 0;
    for (const AlbumData& albumData : m_albumDataList) {
        QWidget *albumWidget = createAlbumWidget(albumData);
        m_albumWidgets.append(albumWidget);
        m_mainLayout->addWidget(albumWidget, row, col, Qt::AlignTop);
        col++;
        if (col >= numColumns) {
            col = 0;
            row++;
        }
    }

    for (int i = 0; i < m_mainLayout->columnCount(); ++i) m_mainLayout->setColumnStretch(i, 0);
    for (int i = 0; i < m_mainLayout->rowCount(); ++i) m_mainLayout->setRowStretch(i, 0);
    if (numColumns > 0) m_mainLayout->setColumnStretch(numColumns, 1);
    if (m_mainLayout->rowCount() > 0) m_mainLayout->setRowStretch(m_mainLayout->rowCount(), 1);

    m_mainLayout->activate();
}

void ContentArea::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    int leftMargin, topMargin, rightMargin, bottomMargin;
    m_mainLayout->getContentsMargins(&leftMargin, &topMargin, &rightMargin, &bottomMargin);
    int horizontalSpacing = m_mainLayout->horizontalSpacing();
    if (horizontalSpacing == -1) horizontalSpacing = m_mainLayout->spacing();
    int effectiveWidth = event->size().width() - leftMargin - rightMargin;
    int itemTotalWidth = ALBUM_ITEM_WIDTH_HINT;
    int newNumColumns = qMax(1, effectiveWidth / itemTotalWidth);
    if (newNumColumns > 1) {
        newNumColumns = qMax(1, (effectiveWidth + horizontalSpacing) / (itemTotalWidth + horizontalSpacing));
    }
    if (newNumColumns == 0 && effectiveWidth > ALBUM_ITEM_MIN_WIDTH) newNumColumns = 1;

    if (newNumColumns > 0 && newNumColumns != m_currentColumns) {
        relayoutAlbums(event->size().width());
    } else if (m_currentColumns == 0 && newNumColumns > 0) {
        relayoutAlbums(event->size().width());
    }
}
