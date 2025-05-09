#include "MainWindow.h"
#include "Sidebar.h"
#include "TopBar.h"
#include "ContentArea.h"
#include "PlaybackBar.h"
#include "titlebar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <QApplication>
#include <QEvent> // For changeEvent

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->setObjectName("mainWindow");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    QWidget *mainContainer = new QWidget(this);
    mainContainer->setObjectName("mainContainer"); // For potential specific styling
    QVBoxLayout *appLayout = new QVBoxLayout(mainContainer);
    appLayout->setContentsMargins(0, 0, 0, 0);
    appLayout->setSpacing(0);

    m_customTitleBar = new CustomTitleBar(this);
    m_customTitleBar->setTitle("Tune");
    connect(m_customTitleBar, &CustomTitleBar::minimizeRequested, this, &MainWindow::handleMinimize);
    connect(m_customTitleBar, &CustomTitleBar::maximizeRestoreRequested, this, &MainWindow::handleMaximizeRestore);
    connect(m_customTitleBar, &CustomTitleBar::closeRequested, this, &QWidget::close);
    appLayout->addWidget(m_customTitleBar);

    m_mainContentWidget = new QWidget(this);
    QHBoxLayout *contentAndSidebarLayout = new QHBoxLayout(m_mainContentWidget);
    contentAndSidebarLayout->setContentsMargins(0, 0, 0, 0);
    contentAndSidebarLayout->setSpacing(0);

    sidebar = new Sidebar(m_mainContentWidget);
    contentAndSidebarLayout->addWidget(sidebar);

    QWidget *rightColumnWidget = new QWidget(m_mainContentWidget);
    QVBoxLayout *rightColumnLayout = new QVBoxLayout(rightColumnWidget);
    rightColumnLayout->setContentsMargins(0, 0, 0, 0);
    rightColumnLayout->setSpacing(0);

    topBar = new TopBar(rightColumnWidget);
    rightColumnLayout->addWidget(topBar);

    QScrollArea *contentScrollArea = new QScrollArea(rightColumnWidget);
    contentScrollArea->setWidgetResizable(true);
    contentScrollArea->setObjectName("contentScrollArea");
    contentScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    contentScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    contentArea = new ContentArea(contentScrollArea);
    contentScrollArea->setWidget(contentArea);
    rightColumnLayout->addWidget(contentScrollArea, 1);

    playbackBar = new PlaybackBar(rightColumnWidget);
    rightColumnLayout->addWidget(playbackBar);

    rightColumnWidget->setLayout(rightColumnLayout);
    contentAndSidebarLayout->addWidget(rightColumnWidget, 1);
    m_mainContentWidget->setLayout(contentAndSidebarLayout);
    appLayout->addWidget(m_mainContentWidget, 1);

    mainContainer->setLayout(appLayout);
    setCentralWidget(mainContainer);

    m_customTitleBar->setWindowStates(isMaximized());
}

MainWindow::~MainWindow() {}

void MainWindow::handleMinimize() {
    this->showMinimized();
}

void MainWindow::handleMaximizeRestore() {
    if (this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
    m_customTitleBar->setWindowStates(this->isMaximized());
}

// Optional: Override changeEvent to update maximize button when state changes externally
// void MainWindow::changeEvent(QEvent *event) {
//     QMainWindow::changeEvent(event);
//     if (event->type() == QEvent::WindowStateChange) {
//         if (m_customTitleBar) {
//             m_customTitleBar->setWindowStates(isMaximized());
//         }
//     }
// }
