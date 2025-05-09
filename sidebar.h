#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QButtonGroup> // To manage exclusive button checks

class QVBoxLayout; // Forward declaration
class QPushButton;
class QLabel;

class Sidebar : public QWidget {
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);

private slots:
    void onMenuItemClicked(int id); // Slot to handle button clicks

private:
    QString svgHomeIcon();
    QString svgLibraryIcon();
    QString svgSearchIcon();
    QString svgPlaylistIcon();
    QString svgHeartIcon();

    QVBoxLayout *layout;
    QLabel *logoLabel; // Made a member to access for objectName
    QButtonGroup *menuButtonGroup; // To make buttons checkable and exclusive
};

#endif // SIDEBAR_H
