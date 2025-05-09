#include "MainWindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString nordPolarNightDarkest = "#2E3440";
    QString nordPolarNightDark = "#3B4252";
    QString nordPolarNightLight = "#434C5E";
    QString nordPolarNightLightest = "#4C566A";
    QString nordSnowStormLight = "#ECEFF4";
    QString nordSnowStormMedium = "#D8DEE9";
    QString nordSnowStormActive = "#FFFFFF";
    QString nordFrostAccent = "#88C0D0";
    QString nordAuroraGreen = "#A3BE8C";

    QString styleSheet = QString(R"(
        QWidget {
            background-color: %1; color: %2;
            font-family: 'Segoe UI', 'Open Sans', Arial, sans-serif; font-size: 14px; border: none;
        }
        QMainWindow#mainWindow, QWidget#mainContainer { background-color: %1; }

        QWidget#customTitleBar { background-color: %3; }
        QLabel#titleBarText { color: %2; font-size: 13px; font-weight: bold; padding-left: 5px; }
        QWidget#customTitleBar QPushButton {
            background-color: transparent; color: %4; border: none; padding: 0px;
            min-width: 40px; max-width: 40px; min-height: 30px; max-height: 30px; border-radius: 0px;
        }
        QWidget#customTitleBar QPushButton:hover { background-color: %5; color: %2; }
        QWidget#customTitleBar QPushButton:pressed { background-color: %7; }
        QWidget#customTitleBar QPushButton#closeButton:hover { background-color: #BF616A; color: %2; }
        QWidget#customTitleBar QPushButton#closeButton:pressed { background-color: #a95058; }

        QWidget#sidebar { background-color: %3; }
        QWidget#sidebar QLabel#logoLabel {font-size: 22px; font-weight: bold; color: %2; margin-bottom: 25px; padding-top: 15px; padding-bottom: 5px;}
        QWidget#sidebar QPushButton {background-color: transparent; border: none; color: %4; font-size: 15px; text-align: left; padding: 12px 18px; border-radius: 6px; margin: 0px 5px 8px 5px;}
        QWidget#sidebar QPushButton:hover {background-color: %5; color: %2;}
        QWidget#sidebar QPushButton:checked {background-color: %6; color: %1; font-weight: bold;}
        QWidget#sidebar QPushButton::icon {padding-right: 12px;}

        QWidget#topBar { background-color: %3; border-bottom: 1px solid %1; padding-top: 8px; padding-bottom: 8px; }
        QWidget#topBar QLineEdit#searchBar {background-color: %5; border: 1px solid %3; border-radius: 17px; color: %2; padding: 0px 15px; font-size: 14px; min-width: 300px; height: 34px;}
        QWidget#topBar QLineEdit#searchBar:focus {border: 1px solid %6; background-color: %7;}
        QWidget#topBar QPushButton#settingsButton {background-color: transparent; border: none; color: %4; padding: 4px; border-radius: 17px; min-width: 34px; max-width: 34px; min-height: 34px; max-height: 34px;}
        QWidget#topBar QPushButton#settingsButton:hover {background-color: %5; color: %2;}
        QWidget#topBar QPushButton#settingsButton:pressed {background-color: %7;}

        QWidget#contentArea { background-color: %1; }
        QLabel.albumImageLabel {background-color: %3; border-radius: 6px;}
        QLabel.albumTitleLabel {color: %2; font-size: 14px; font-weight: 500; margin-top: 6px;}

        QWidget#playbackBar {
             background-color: #181818; border-top: 1px solid #2A2A2A;
             min-height: 70px; max-height: 70px;
        }
        QWidget#playbackBar QLabel#albumArtLabel {
            min-width: 48px; max-width: 48px; min-height: 48px; max-height: 48px;
            border-radius: 4px; background-color: %5;
        }
        QWidget#playbackBar QLabel#songTitleLabel { color: %8; font-size: 13px; font-weight: bold; }
        QWidget#playbackBar QLabel#songArtistLabel { color: %4; font-size: 11px; }
        QWidget#playbackBar QPushButton#likeButton { color: %4; min-width: 28px; max-width: 28px; min-height: 28px; max-height: 28px; padding: 0px; }
        QWidget#playbackBar QPushButton#likeButton:hover { color: %8; }
        QWidget#playbackBar QPushButton#likeButton:checked { color: %9; }

        QWidget#playbackBar QWidget#centerPlaybackControls QPushButton {
            color: %4; min-width: 32px; max-width: 32px; min-height: 32px; max-height: 32px;
            padding: 0px; border-radius: 16px;
        }
        QWidget#playbackBar QWidget#centerPlaybackControls QPushButton:hover { color: %8; }
        QWidget#playbackBar QWidget#centerPlaybackControls QPushButton#playPauseButton {
            background-color: %8; color: #000000;
            min-width: 36px; max-width: 36px; min-height: 36px; max-height: 36px; border-radius: 18px;
        }
        QWidget#playbackBar QWidget#centerPlaybackControls QPushButton#playPauseButton:hover { background-color: %2; }
        QWidget#playbackBar QWidget#centerPlaybackControls QPushButton#shuffleButton:checked,
        QWidget#playbackBar QWidget#centerPlaybackControls QPushButton#repeatButton:checked { color: %9; }

        QWidget#playbackBar QLabel.timeLabel, QLabel#currentTimeLabel, QLabel#totalTimeLabel {
            color: %4; font-size: 11px; min-width: 35px;
        }
        QLabel#currentTimeLabel { text-align: right; }
        QLabel#totalTimeLabel { text-align: left; }


        QWidget#playbackBar QSlider::groove:horizontal {
            background-color: %5; border: 1px solid %5; height: 4px; border-radius: 2px; margin: 2px 0;
        }
        QWidget#playbackBar QSlider::handle:horizontal {
            background-color: %8; border: 1px solid %8; width: 12px; height: 12px;
            margin: -4px 0; border-radius: 6px;
        }
        QWidget#playbackBar QSlider:hover QSlider::handle:horizontal { background-color: %9; border-color: %9; }
        QWidget#playbackBar QSlider::sub-page:horizontal {
            background: %8; border: 1px solid %8; height: 4px; border-radius: 2px;
        }
        QWidget#playbackBar QSlider:hover QSlider::sub-page:horizontal { background: %9; border-color: %9;}

        QWidget#playbackBar QWidget#rightPlaybackControls QPushButton {
            color: %4; min-width: 28px; max-width: 28px; min-height: 28px; max-height: 28px; padding: 0px;
        }
        QWidget#playbackBar QWidget#rightPlaybackControls QPushButton:hover { color: %8; }
        QWidget#playbackBar QWidget#rightPlaybackControls QSlider::groove:horizontal { height: 3px; border-radius: 1px; background-color: %5;}
        QWidget#playbackBar QWidget#rightPlaybackControls QSlider::handle:horizontal { background-color: %8; width: 10px; height: 10px; margin: -3.5px 0; border-radius: 5px;}
        QWidget#playbackBar QWidget#rightPlaybackControls QSlider:hover QSlider::handle:horizontal { background-color: %9; }
        QWidget#playbackBar QWidget#rightPlaybackControls QSlider::sub-page:horizontal { background: %8; height: 3px; border-radius: 1px;}
        QWidget#playbackBar QWidget#rightPlaybackControls QSlider:hover QSlider::sub-page:horizontal { background: %9; }

        QScrollArea { border: none; background-color: transparent; }
        QScrollBar:vertical {border: none; background: %5; width: 10px; margin: 0px;}
        QScrollBar::handle:vertical {background: %7; min-height: 25px; border-radius: 5px;}
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {border: none; background: none;}
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: none;}
        QScrollBar:horizontal {border: none; background: %5; height: 10px; margin: 0px;}
        QScrollBar::handle:horizontal {background: %7; min-width: 25px; border-radius: 5px;}
        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {border: none; background: none;}
        QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {background: none;}
        QLineEdit {background-color: %5; border: 1px solid %3; border-radius: 4px; color: %2; padding: 6px 10px; font-size: 14px;}
        QLineEdit:focus {border: 1px solid %6;}

    )")
                             .arg(nordPolarNightDarkest)     // %1
                             .arg(nordSnowStormLight)      // %2
                             .arg(nordPolarNightDark)      // %3
                             .arg(nordSnowStormMedium)     // %4
                             .arg(nordPolarNightLight)     // %5
                             .arg(nordFrostAccent)         // %6
                             .arg(nordPolarNightLightest)  // %7
                             .arg(nordSnowStormActive)     // %8
                             .arg(nordAuroraGreen);        // %9

    app.setStyleSheet(styleSheet);

    MainWindow window;
    window.setWindowTitle("Tune");
    window.resize(1280, 850);
    window.show();

    return app.exec();
}
