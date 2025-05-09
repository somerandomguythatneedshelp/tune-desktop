#include "TopBar.h" // Ensure this matches your actual header file name (TopBar.h or topbar.h)
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QSvgRenderer>
#include <QPainter>

// SVG string for settings icon (Corrected xmlns)
static QString topBarSvgSettingsIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                 <circle cx="12" cy="12" r="3"></circle>
                 <path d="M19.4 15a1.65 1.65 0 0 0 .33 1.82l.06.06a2 2 0 0 1 0 2.83 2 2 0 0 1-2.83 0l-.06-.06a1.65 1.65 0 0 0-1.82-.33 1.65 1.65 0 0 0-1 1.51V21a2 2 0 0 1-2 2 2 2 0 0 1-2-2v-.09A1.65 1.65 0 0 0 9 19.4a1.65 1.65 0 0 0-1.82.33l-.06.06a2 2 0 0 1-2.83 0 2 2 0 0 1 0-2.83l.06-.06a1.65 1.65 0 0 0 .33-1.82 1.65 1.65 0 0 0-1.51-1H3a2 2 0 0 1-2-2 2 2 0 0 1 2-2h.09A1.65 1.65 0 0 0 4.6 9a1.65 1.65 0 0 0-.33-1.82l-.06-.06a2 2 0 0 1 0-2.83 2 2 0 0 1 2.83 0l.06.06a1.65 1.65 0 0 0 1.82.33H9a1.65 1.65 0 0 0 1-1.51V3a2 2 0 0 1 2-2 2 2 0 0 1 2 2v.09a1.65 1.65 0 0 0 1 1.51 1.65 1.65 0 0 0 1.82-.33l.06-.06a2 2 0 0 1 2.83 0 2 2 0 0 1 0 2.83l-.06.06a1.65 1.65 0 0 0-.33 1.82V15a1.65 1.65 0 0 0 1.51 1H21a2 2 0 0 1 2 2 2 2 0 0 1-2 2h-.09a1.65 1.65 0 0 0-1.51 1z"></path>
               </svg>)";
}


TopBar::TopBar(QWidget *parent) : QWidget(parent) {
    this->setObjectName("topBar");
    setFixedHeight(60);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(15, 0, 15, 0);
    layout->setSpacing(10);

    searchBar = new QLineEdit(this);
    searchBar->setObjectName("searchBar");
    searchBar->setPlaceholderText("Search for songs, artists, or albums...");
    searchBar->setFixedHeight(34);
    layout->addWidget(searchBar, 1);

    layout->addStretch(1);

    settingsButton = new QPushButton(this);
    settingsButton->setObjectName("settingsButton");
    settingsButton->setFixedSize(34, 34);
    settingsButton->setToolTip("Settings");
    settingsButton->setFlat(true);


    QPixmap settingsPixmap(20, 20);
    settingsPixmap.fill(Qt::transparent);
    QPainter settingsPainter(&settingsPixmap);
    QSvgRenderer settingsRenderer(topBarSvgSettingsIcon().toUtf8());
    if (settingsRenderer.isValid()) {
        settingsRenderer.render(&settingsPainter);
        settingsButton->setIcon(QIcon(settingsPixmap));
        settingsButton->setIconSize(QSize(20, 20));
    }

    layout->addWidget(settingsButton);
    setLayout(layout);
}
