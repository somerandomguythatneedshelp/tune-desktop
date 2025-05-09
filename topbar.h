#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>

class QHBoxLayout;
class QLineEdit;
class QPushButton;

class TopBar : public QWidget {
    Q_OBJECT

public:
    explicit TopBar(QWidget *parent = nullptr);

private:
    QLineEdit *searchBar;
    QPushButton *settingsButton; // Only search and settings remain
};

#endif // TOPBAR_H
