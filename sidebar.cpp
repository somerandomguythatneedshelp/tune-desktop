#include "Sidebar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSvgRenderer>
#include <QPainter>
#include <QIcon>
#include <QButtonGroup>
#include <QDebug>

// --- SVG Icon Strings ---
static QString sidebarSvgHomeIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="m3 9 9-7 9 7v11a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"/><polyline points="9 22 9 12 15 12 15 22"/></svg>)";
}
static QString sidebarSvgSearchIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="11" cy="11" r="8"/><line x1="21" y1="21" x2="16.65" y2="16.65"/></svg>)";
}
static QString sidebarSvgLibraryIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="m16 6 4 14"/><path d="M12 6v14"/><path d="M8 8v12"/><path d="M4 4v16"/></svg>)";
}
static QString sidebarSvgPlaylistIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="8" x2="21" y1="6" y2="6"/><line x1="8" x2="21" y1="12" y2="12"/><line x1="8" x2="21" y1="18" y2="18"/><line x1="3" x2="3.01" y1="6" y2="6"/><line x1="3" x2="3.01" y1="12" y2="12"/><line x1="3" x2="3.01" y1="18" y2="18"/></svg>)";
}
static QString sidebarSvgHeartIcon() {
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M19 14c1.49-1.46 3-3.21 3-5.5A5.5 5.5 0 0 0 16.5 3c-1.76 0-3 .5-4.5 2-1.5-1.5-2.74-2-4.5-2A5.5 5.5 0 0 0 2 8.5c0 2.3 1.5 4.05 3 5.5l7 7Z"/></svg>)";
}
// --- End SVG Icon Strings ---

Sidebar::Sidebar(QWidget *parent) : QWidget(parent) {
    this->setObjectName("sidebar");
    setFixedWidth(230);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 0, 10, 10);
    layout->setSpacing(0);

    logoLabel = new QLabel("Tune", this);
    logoLabel->setObjectName("logoLabel");
    logoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(logoLabel);
    layout->addSpacing(10);

    menuButtonGroup = new QButtonGroup(this);
    menuButtonGroup->setExclusive(true);

    struct MenuItem {
        int id;
        QString name;
        QString svgString;
    };

    QVector<MenuItem> menuItems = {
        {0, "Home", sidebarSvgHomeIcon()},
        {1, "Search", sidebarSvgSearchIcon()},
        {2, "Library", sidebarSvgLibraryIcon()},
        {3, "Playlists", sidebarSvgPlaylistIcon()},
        {4, "Liked Songs", sidebarSvgHeartIcon()}
    };

    for (const auto &item : menuItems) {
        QPushButton *button = new QPushButton(item.name, this); // Standard QPushButton
        button->setCheckable(true);
        button->setFlat(true); // Important for stylesheet background control

        QPixmap pixmap(20, 20);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        QSvgRenderer renderer(item.svgString.toUtf8());
        if (renderer.isValid()) {
            renderer.render(&painter);
            button->setIcon(QIcon(pixmap));
            button->setIconSize(QSize(20,20));
        } else {
            qWarning() << "Sidebar: Failed to load SVG for" << item.name;
        }
        layout->addWidget(button);
        menuButtonGroup->addButton(button, item.id);
    }

    connect(menuButtonGroup, &QButtonGroup::idClicked, this, &Sidebar::onMenuItemClicked);

    if(menuButtonGroup->button(0)) {
        menuButtonGroup->button(0)->setChecked(true);
    }

    layout->addStretch();
    setLayout(layout);
}

void Sidebar::onMenuItemClicked(int id) {
    qDebug("Sidebar item clicked: %d", id);
}

// These are not strictly needed if the static functions are used directly, but keep for consistency if you prefer
QString Sidebar::svgHomeIcon() { return sidebarSvgHomeIcon(); }
QString Sidebar::svgSearchIcon() { return sidebarSvgSearchIcon(); }
QString Sidebar::svgLibraryIcon() { return sidebarSvgLibraryIcon(); }
QString Sidebar::svgPlaylistIcon() { return sidebarSvgPlaylistIcon(); }
QString Sidebar::svgHeartIcon() { return sidebarSvgHeartIcon(); }
