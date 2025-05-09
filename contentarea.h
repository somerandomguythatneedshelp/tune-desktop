#ifndef CONTENTAREA_H
#define CONTENTAREA_H

#include <QWidget>
#include <QList> // For storing album widgets

class QGridLayout;
class QLabel; // Forward declare if only pointers are used

// A simple struct to hold album data for demonstration
struct AlbumData {
    QString title;
    QString artist; // Though not displayed in current ContentArea, good for future
    QPixmap artwork; // Placeholder for actual artwork loading
    // Add other relevant data like ID, path, etc.
};

class ContentArea : public QWidget {
    Q_OBJECT

public:
    explicit ContentArea(QWidget *parent = nullptr);
    void setAlbums(const QList<AlbumData>& albums); // Method to populate albums

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void relayoutAlbums(int availableWidth);
    QWidget* createAlbumWidget(const AlbumData& albumData); // Helper to create each album item

    QGridLayout *m_mainLayout;
    QList<QWidget*> m_albumWidgets; // Store pointers to the created album widgets
    QList<AlbumData> m_albumDataList; // Store the data for repopulation

    int m_currentColumns = 0;
    const int ALBUM_ITEM_WIDTH_HINT = 200; // Approx width of an album item (image + padding)
    const int ALBUM_ITEM_MIN_WIDTH = 160; // Absolute minimum before it looks too cramped
};

#endif // CONTENTAREA_H
