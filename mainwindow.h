#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Sidebar;
class TopBar;
class ContentArea;
class PlaybackBar;
class CustomTitleBar;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleMinimize();          // Definition will be added in mainwindow.cpp
    void handleMaximizeRestore(); // Definition will be added in mainwindow.cpp

private:
    CustomTitleBar *m_customTitleBar;
    Sidebar *sidebar;
    TopBar *topBar;
    ContentArea *contentArea;
    PlaybackBar *playbackBar;
    QWidget *m_mainContentWidget;
};

#endif // MAINWINDOW_H
