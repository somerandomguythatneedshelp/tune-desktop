#include "playbackbar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QStyle>
#include <QDebug>
#include <QIcon>
#include <QSvgRenderer>
#include <QPainter>
#include <QTime>
#include <QColor> // For QColor directly

// --- SVG Icon Definitions ---
QString PlaybackBar::svgHeartOutline() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M20.84 4.61a5.5 5.5 0 0 0-7.78 0L12 5.67l-1.06-1.06a5.5 5.5 0 0 0-7.78 7.78l1.06 1.06L12 21.23l7.78-7.78 1.06-1.06a5.5 5.5 0 0 0 0-7.78z"></path></svg>)"; }
QString PlaybackBar::svgHeartFilled() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="currentColor" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M20.84 4.61a5.5 5.5 0 0 0-7.78 0L12 5.67l-1.06-1.06a5.5 5.5 0 0 0-7.78 7.78l1.06 1.06L12 21.23l7.78-7.78 1.06-1.06a5.5 5.5 0 0 0 0-7.78z"></path></svg>)"; }
QString PlaybackBar::svgShuffle() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="16 3 21 3 21 8"></polyline><line x1="4" y1="20" x2="21" y2="3"></line><polyline points="16 21 21 21 21 16"></polyline><line x1="15" y1="15" x2="21" y2="21"></line><line x1="4" y1="4" x2="9" y2="9"></line></svg>)"; }
QString PlaybackBar::svgPrevPB() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="currentColor"><polygon points="19 5 19 19 12 12 19 5"></polygon><polygon points="5 5 5 19 12 19 12 5 5 5"></polygon></svg>)"; }
QString PlaybackBar::svgPlayPB() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="currentColor"><polygon points="5 3 19 12 5 21 5 3"></polygon></svg>)"; }
QString PlaybackBar::svgPausePB() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="currentColor"><rect x="6" y="4" width="4" height="16"></rect><rect x="14" y="4" width="4" height="16"></rect></svg>)"; }
QString PlaybackBar::svgNextPB() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="currentColor"><polygon points="5 5 5 19 12 12 5 5"></polygon><polygon points="19 5 19 19 12 19 12 5 19 5"></polygon></svg>)"; }
QString PlaybackBar::svgRepeat() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="17 1 21 5 17 9"></polyline><path d="M3 11V9a4 4 0 0 1 4-4h14"></path><polyline points="7 23 3 19 7 15"></polyline><path d="M21 13v2a4 4 0 0 1-4 4H3"></path></svg>)"; }
QString PlaybackBar::svgRepeatOne() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"><path d="M17 1l4 4-4 4"/><path d="M3 11V9a4 4 0 014-4h14"/><path d="M7 23l-4-4 4-4"/><path d="M21 13v2a4 4 0 01-4 4H3"/><path d="M11.5 10.5v3M10 10.5h3"/></svg>)"; }
QString PlaybackBar::svgVolumeHigh() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"></polygon><path d="M19.07 4.93a10 10 0 0 1 0 14.14M15.54 8.46a5 5 0 0 1 0 7.07"></path></svg>)"; }
QString PlaybackBar::svgVolumeMedium() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"></polygon><path d="M15.54 8.46a5 5 0 0 1 0 7.07"></path></svg>)"; }
QString PlaybackBar::svgVolumeLow() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"></polygon></svg>)"; }
QString PlaybackBar::svgVolumeMute() { return R"(<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"></polygon><line x1="23" y1="9" x2="17" y2="15"></line><line x1="17" y1="9" x2="23" y2="15"></line></svg>)"; }
// --- End SVG Icon Definitions ---

QPushButton* PlaybackBar::createIconButtonPB(const QString& objectName, const QString& iconSvg, const QString& tooltip, bool checkable, int iconSize) {
    QPushButton *button = new QPushButton(this);
    button->setObjectName(objectName);
    button->setToolTip(tooltip);
    button->setCheckable(checkable);
    button->setFocusPolicy(Qt::NoFocus);
    button->setFlat(true);
    setButtonIconPB(button, iconSvg, iconSize);
    return button;
}

void PlaybackBar::setButtonIconPB(QPushButton* button, const QString& iconSvg, int iconSize) {
    if (!button) return;
    QPixmap pixmap(iconSize, iconSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QSvgRenderer renderer(iconSvg.toUtf8());
    if (renderer.isValid()) {
        renderer.render(&painter);
        button->setIcon(QIcon(pixmap));
        button->setIconSize(QSize(iconSize, iconSize));
    } else {
        qWarning() << "PlaybackBar: Failed to load SVG for" << button->objectName();
        button->setText("!");
    }
}

PlaybackBar::PlaybackBar(QWidget *parent) : QWidget(parent), m_isRepeatingOne(false) {
    this->setObjectName("playbackBar");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(15, 8, 15, 8);
    mainLayout->setSpacing(15);

    // --- Left Section (Song Info) ---
    QWidget *songInfoWidget = new QWidget(this);
    songInfoWidget->setObjectName("songInfoPlayback");
    QHBoxLayout *songInfoLayout = new QHBoxLayout(songInfoWidget);
    songInfoLayout->setContentsMargins(0,0,0,0);
    songInfoLayout->setSpacing(10);

    m_albumArtLabel = new QLabel(this);
    m_albumArtLabel->setObjectName("albumArtLabel");
    m_albumArtLabel->setFixedSize(48, 48);
    QPixmap tempArt(48,48); tempArt.fill(QColor(Qt::darkGray)); m_albumArtLabel->setPixmap(tempArt);

    QVBoxLayout *titleArtistLayout = new QVBoxLayout();
    titleArtistLayout->setContentsMargins(0,0,0,0);
    titleArtistLayout->setSpacing(1);
    m_songTitleLabel = new QLabel("Song Title", this);
    m_songTitleLabel->setObjectName("songTitleLabel");
    m_songArtistLabel = new QLabel("Artist Name", this);
    m_songArtistLabel->setObjectName("songArtistLabel");
    titleArtistLayout->addWidget(m_songTitleLabel);
    titleArtistLayout->addWidget(m_songArtistLabel);

    m_likeButton = createIconButtonPB("likeButton", svgHeartOutline(), "Like", true, 16);
    connect(m_likeButton, &QPushButton::toggled, this, [this](bool checked){
        setButtonIconPB(m_likeButton, checked ? svgHeartFilled() : svgHeartOutline(), 16);
    });

    songInfoLayout->addWidget(m_albumArtLabel);
    songInfoLayout->addLayout(titleArtistLayout);
    songInfoLayout->addWidget(m_likeButton, 0, Qt::AlignVCenter);
    songInfoLayout->addStretch();
    songInfoWidget->setLayout(songInfoLayout);
    mainLayout->addWidget(songInfoWidget, 2); // Song info on the LEFT, stretch factor 2

    // --- Center Section (Controls & Seek) ---
    QWidget *centerControlsWidget = new QWidget(this);
    centerControlsWidget->setObjectName("centerPlaybackControls");
    QVBoxLayout *centerOuterLayout = new QVBoxLayout(centerControlsWidget);
    centerOuterLayout->setContentsMargins(0,0,0,0);
    centerOuterLayout->setSpacing(4);

    QHBoxLayout *playbackButtonsLayout = new QHBoxLayout();
    playbackButtonsLayout->setContentsMargins(0,0,0,0);
    playbackButtonsLayout->setSpacing(15);
    playbackButtonsLayout->addStretch();
    m_shuffleButton = createIconButtonPB("shuffleButton", svgShuffle(), "Shuffle", true, 18);
    connect(m_shuffleButton, &QPushButton::toggled, this, &PlaybackBar::onShuffleClicked);
    m_prevButton = createIconButtonPB("prevButton", svgPrevPB(), "Previous", false, 22);
    m_playPauseButton = createIconButtonPB("playPauseButton", svgPlayPB(), "Play", true, 26);
    connect(m_playPauseButton, &QPushButton::toggled, this, &PlaybackBar::onPlayPauseClicked);
    m_nextButton = createIconButtonPB("nextButton", svgNextPB(), "Next", false, 22);
    m_repeatButton = createIconButtonPB("repeatButton", svgRepeat(), "Repeat", true, 18);
    connect(m_repeatButton, &QPushButton::toggled, this, &PlaybackBar::onRepeatClicked);

    playbackButtonsLayout->addWidget(m_shuffleButton);
    playbackButtonsLayout->addWidget(m_prevButton);
    playbackButtonsLayout->addWidget(m_playPauseButton);
    playbackButtonsLayout->addWidget(m_nextButton);
    playbackButtonsLayout->addWidget(m_repeatButton);
    playbackButtonsLayout->addStretch();
    centerOuterLayout->addLayout(playbackButtonsLayout);

    QHBoxLayout *seekLayout = new QHBoxLayout();
    seekLayout->setContentsMargins(0,0,0,0);
    seekLayout->setSpacing(8);
    m_currentTimeLabel = new QLabel("0:00", this);
    m_currentTimeLabel->setObjectName("currentTimeLabel");
    m_currentTimeLabel->setMinimumWidth(40); m_currentTimeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_seekSlider = new QSlider(Qt::Horizontal, this);
    m_seekSlider->setObjectName("seekSlider");
    m_seekSlider->setFixedHeight(12);
    connect(m_seekSlider, &QSlider::sliderMoved, this, &PlaybackBar::seekSliderMoved);
    connect(m_seekSlider, &QSlider::sliderReleased, this, &PlaybackBar::onSeekSliderReleased);
    m_totalTimeLabel = new QLabel("0:00", this);
    m_totalTimeLabel->setObjectName("totalTimeLabel");
    m_totalTimeLabel->setMinimumWidth(40); m_totalTimeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    seekLayout->addWidget(m_currentTimeLabel);
    seekLayout->addWidget(m_seekSlider, 1);
    seekLayout->addWidget(m_totalTimeLabel);
    centerOuterLayout->addLayout(seekLayout);
    centerControlsWidget->setLayout(centerOuterLayout);
    mainLayout->addWidget(centerControlsWidget, 3); // Playback controls in the CENTER, stretch factor 3

    // --- Right Section (Volume Controls) ---
    QWidget *rightControlsWidget = new QWidget(this);
    rightControlsWidget->setObjectName("rightPlaybackControls");
    QHBoxLayout *rightControlsLayout = new QHBoxLayout(rightControlsWidget);
    rightControlsLayout->setContentsMargins(0,0,0,0);
    rightControlsLayout->setSpacing(8);
    rightControlsLayout->addStretch();
    m_volumeButton = createIconButtonPB("volumeButton", svgVolumeHigh(), "Volume", false, 18);
    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeSlider->setObjectName("volumeSlider");
    m_volumeSlider->setFixedWidth(100);
    m_volumeSlider->setFixedHeight(12);
    m_volumeSlider->setRange(0, 100);
    m_volumeSlider->setValue(75);
    connect(m_volumeSlider, &QSlider::valueChanged, this, &PlaybackBar::onVolumeSliderChanged);

    rightControlsLayout->addWidget(m_volumeButton);
    rightControlsLayout->addWidget(m_volumeSlider);
    rightControlsWidget->setLayout(rightControlsLayout);
    mainLayout->addWidget(rightControlsWidget, 1); // Volume controls on the RIGHT, stretch factor 1

    setLayout(mainLayout);
    updateTrackInfo(QPixmap(48,48), "No Song Playing", "...");
    updatePlaybackTime(0,0);
    onVolumeSliderChanged(m_volumeSlider->value());
}

void PlaybackBar::updateTrackInfo(const QPixmap& albumArt, const QString& title, const QString& artist) {
    if (!albumArt.isNull() && !albumArt.size().isEmpty()) {
        m_albumArtLabel->setPixmap(albumArt.scaled(m_albumArtLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        QPixmap tempArt(m_albumArtLabel->width(),m_albumArtLabel->height());
        tempArt.fill(QColor(Qt::darkGray));
        QPainter p(&tempArt); p.setPen(Qt::white); p.drawText(tempArt.rect(), Qt::AlignCenter, "Art");
        m_albumArtLabel->setPixmap(tempArt);
    }
    m_songTitleLabel->setText(title);
    m_songArtistLabel->setText(artist);
}

void PlaybackBar::updatePlaybackTime(int currentTime, int totalTime) {
    QTime ct = QTime(0,0,0).addSecs(currentTime);
    QTime tt = QTime(0,0,0).addSecs(totalTime);
    QString timeFormat = totalTime >= 3600 ? "H:mm:ss" : "m:ss";

    m_currentTimeLabel->setText(ct.toString(timeFormat));
    m_totalTimeLabel->setText(tt.toString(timeFormat));

    if (!m_seekSlider->isSliderDown()) {
        m_seekSlider->setRange(0, totalTime > 0 ? totalTime : 1);
        m_seekSlider->setValue(currentTime);
    }
}

void PlaybackBar::onPlayPauseClicked(bool checked) {
    setButtonIconPB(m_playPauseButton, checked ? svgPausePB() : svgPlayPB(), 26);
    if (checked) {
        qDebug() << "Playback: Request PLAY";
    } else {
        qDebug() << "Playback: Request PAUSE";
    }
}

void PlaybackBar::onShuffleClicked(bool checked) {
    qDebug() << "Shuffle Toggled:" << checked;
}

void PlaybackBar::onRepeatClicked(bool checked) {
    if (!checked) {
        setButtonIconPB(m_repeatButton, svgRepeat(), 18);
        m_repeatButton->setToolTip("Repeat");
        m_isRepeatingOne = false;
        qDebug() << "Repeat: OFF";
    } else {
        if (!m_isRepeatingOne) {
            setButtonIconPB(m_repeatButton, svgRepeat(), 18);
            m_repeatButton->setToolTip("Repeat All - Click to repeat one song");
            m_isRepeatingOne = true;
            qDebug() << "Repeat: ALL";
        } else {
            setButtonIconPB(m_repeatButton, svgRepeatOne(), 18);
            m_repeatButton->setToolTip("Repeat One - Click to turn off repeat");
            qDebug() << "Repeat: ONE";
        }
    }
}

void PlaybackBar::seekSliderMoved(int position) {
    QTime ct = QTime(0,0,0).addSecs(position);
    QString timeFormat = m_seekSlider->maximum() >= 3600 ? "H:mm:ss" : "m:ss";
    m_currentTimeLabel->setText(ct.toString(timeFormat));
}

void PlaybackBar::onSeekSliderReleased() {
    qDebug() << "Seek Slider Released at:" << m_seekSlider->value();
}

void PlaybackBar::onVolumeSliderChanged(int value) {
    qDebug() << "Volume changed:" << value;
    if (value == 0) setButtonIconPB(m_volumeButton, svgVolumeMute(), 18);
    else if (value < 33) setButtonIconPB(m_volumeButton, svgVolumeLow(), 18);
    else if (value < 66) setButtonIconPB(m_volumeButton, svgVolumeMedium(), 18);
    else setButtonIconPB(m_volumeButton, svgVolumeHigh(), 18);
}
