#ifndef PLAYBACKBAR_H
#define PLAYBACKBAR_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QLabel;
class QSlider;

class PlaybackBar : public QWidget {
    Q_OBJECT

public:
    explicit PlaybackBar(QWidget *parent = nullptr);
    void updateTrackInfo(const QPixmap& albumArt, const QString& title, const QString& artist);
    void updatePlaybackTime(int currentTime, int totalTime); // Time in seconds

private slots:
    void onPlayPauseClicked(bool checked);
    void onShuffleClicked(bool checked);
    void onRepeatClicked(bool checked);
    void seekSliderMoved(int position); // Slot for when user drags
    void onSeekSliderReleased();      // Slot for when user releases seek slider
    void onVolumeSliderChanged(int value);


private:
    // Left: Song Info
    QLabel *m_albumArtLabel;
    QLabel *m_songTitleLabel;
    QLabel *m_songArtistLabel;
    QPushButton *m_likeButton;

    // Center: Playback Controls & Seek
    QPushButton *m_shuffleButton;
    QPushButton *m_prevButton;
    QPushButton *m_playPauseButton;
    QPushButton *m_nextButton;
    QPushButton *m_repeatButton;

    QLabel *m_currentTimeLabel;
    QSlider *m_seekSlider;
    QLabel *m_totalTimeLabel;

    // Right: Other Controls
    // QPushButton *m_lyricsButton;
    // QPushButton *m_queueButton;
    // QPushButton *m_deviceButton;
    QPushButton *m_volumeButton;
    QSlider *m_volumeSlider;

    QPushButton* createIconButtonPB(const QString& objectName, const QString& iconSvgPath, const QString& tooltip, bool checkable = false, int iconSize = 18);
    void setButtonIconPB(QPushButton* button, const QString& iconSvg, int iconSize = 18);

    // SVG Icons
    QString svgHeartOutline();
    QString svgHeartFilled();
    QString svgShuffle();
    QString svgPrevPB(); // Renamed to avoid conflict if any
    QString svgPlayPB();
    QString svgPausePB();
    QString svgNextPB();
    QString svgRepeat();
    QString svgRepeatOne();
    QString svgVolumeHigh();
    QString svgVolumeMedium(); // Added
    QString svgVolumeLow();    // Added
    QString svgVolumeMute();   // Added
    // QString svgLyrics();
    // QString svgQueue();
    // QString svgDevice();

    bool m_isRepeatingOne = false;
};

#endif // PLAYBACKBAR_H
