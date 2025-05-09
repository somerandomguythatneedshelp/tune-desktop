#include "titlebar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QWindow>
#include <QIcon>
#include <QSvgRenderer>
#include <QPainter>

// --- SVG Icon Strings (Corrected xmlns) ---
QString CustomTitleBar::svgMinimizeIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="5" y1="12" x2="19" y2="12"></line></svg>)";
}
QString CustomTitleBar::svgMaximizeIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M8 3H5a2 2 0 0 0-2 2v3m18 0V5a2 2 0 0 0-2-2h-3m0 18h3a2 2 0 0 0 2-2v-3M3 16v3a2 2 0 0 0 2 2h3"></path></svg>)";
}
QString CustomTitleBar::svgRestoreIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="15 3 21 3 21 9"></polyline><polyline points="9 21 3 21 3 15"></polyline><line x1="21" y1="3" x2="14" y2="10"></line><line x1="3" y1="21" x2="10" y2="14"></line></svg>)";
}
QString CustomTitleBar::svgCloseIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="18" y1="6" x2="6" y2="18"></line><line x1="6" y1="6" x2="18" y2="18"></line></svg>)";
}
// --- End SVG Icon Strings ---

// Static helper function definition
void CustomTitleBar::setButtonIconHelper(QPushButton* button, const QString& iconSvg, int iconSize) {
    if (!button) return;
    QPixmap pixmap(iconSize, iconSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QSvgRenderer renderer(iconSvg.toUtf8());
    if (renderer.isValid()) {
        renderer.render(&painter);
        button->setIcon(QIcon(pixmap));
        button->setIconSize(QSize(iconSize, iconSize));
    }
}

QPushButton* CustomTitleBar::createButton(const QString& objectName, const QString& iconSvg, const QString& tooltip) {
    QPushButton *button = new QPushButton(this);
    button->setObjectName(objectName);
    button->setToolTip(tooltip);
    button->setFocusPolicy(Qt::NoFocus);
    button->setFlat(true);
    setButtonIconHelper(button, iconSvg, 14); // Use the static helper
    return button;
}

CustomTitleBar::CustomTitleBar(QWidget *parent)
    : QWidget(parent), m_dragging(false) {
    setObjectName("customTitleBar");
    setFixedHeight(32);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setObjectName("titleBarText");
    m_titleLabel->setAlignment(Qt::AlignCenter);

    m_minimizeButton = createButton("minimizeButton", svgMinimizeIcon(), "Minimize");
    m_maximizeButton = createButton("maximizeButton", svgMaximizeIcon(), "Maximize");
    m_closeButton = createButton("closeButton", svgCloseIcon(), "Close");

    connect(m_minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeRequested);
    connect(m_maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeRestoreRequested);
    connect(m_closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeRequested);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 0, 5, 0);
    layout->setSpacing(5);

    layout->addWidget(m_titleLabel, 1, Qt::AlignCenter);
    layout->addWidget(m_minimizeButton);
    layout->addWidget(m_maximizeButton);
    layout->addWidget(m_closeButton);
    setLayout(layout);
}

void CustomTitleBar::setTitle(const QString &title) {
    m_titleLabel->setText(title);
}

void CustomTitleBar::setWindowStates(bool maximized) {
    if (maximized) {
        setButtonIconHelper(m_maximizeButton, svgRestoreIcon(), 14);
        m_maximizeButton->setToolTip("Restore");
    } else {
        setButtonIconHelper(m_maximizeButton, svgMaximizeIcon(), 14);
        m_maximizeButton->setToolTip("Maximize");
    }
}

void CustomTitleBar::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        if (window()) {
            m_dragPosition = event->globalPosition().toPoint() - window()->frameGeometry().topLeft();
        }
        event->accept();
    } else {
        QWidget::mousePressEvent(event);
    }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && m_dragging && window()) {
        window()->move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    } else {
        QWidget::mouseMoveEvent(event);
    }
}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_dragging) {
        m_dragging = false;
        event->accept();
    } else {
        QWidget::mouseReleaseEvent(event);
    }
}

void CustomTitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit maximizeRestoreRequested();
        event->accept();
    } else {
        QWidget::mouseDoubleClickEvent(event);
    }
}
