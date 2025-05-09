#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include <QWidget>
#include <QPoint>

class QLabel;
class QPushButton;
class QHBoxLayout;

class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleBar(QWidget *parent = nullptr);
    void setTitle(const QString &title);
    void setWindowStates(bool maximized);


signals:
    void minimizeRequested();
    void maximizeRestoreRequested();
    void closeRequested();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QLabel *m_titleLabel;
    QPushButton *m_minimizeButton;
    QPushButton *m_maximizeButton;
    QPushButton *m_closeButton;

    QPoint m_dragPosition;
    bool m_dragging;

    // Helper to create styled buttons
    QPushButton* createButton(const QString& objectName, const QString& iconSvg, const QString& tooltip);
    // Static helper to set button icon (declaration)
    static void setButtonIconHelper(QPushButton* button, const QString& iconSvg, int iconSize);

    // SVG Icon Strings
    QString svgMinimizeIcon();
    QString svgMaximizeIcon();
    QString svgRestoreIcon();
    QString svgCloseIcon();
};

#endif // CUSTOMTITLEBAR_H
