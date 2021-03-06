#pragma once

#include "../../corelib/enumerations.h"

class QApplication;

#ifdef _WIN32
QPixmap qt_pixmapFromWinHBITMAP(HBITMAP bitmap, int hbitmapFormat = 0);
#endif //_WIN32

namespace Ui
{
    class GeneralDialog;
}

namespace Utils
{
    class ShadowWidgetEventFilter : public QObject
    {
        Q_OBJECT

    public:
        ShadowWidgetEventFilter(int _shadowWidth);

    protected:
        bool eventFilter(QObject* _obj, QEvent* _event);

    private:
        void setGradientColor(QGradient& _gradient, bool _isActive);

    private:
        int ShadowWidth_;
    };

    inline const std::string QStringToString(const QString& _s)
    {
        return _s.toUtf8().constData();
    }

    QString getCountryNameByCode(const QString& _iso_code);
    QMap<QString, QString> getCountryCodes();

    QString ScaleStyle(const QString& _style, double _scale);

    void ApplyStyle(QWidget* _widget, QString _style);
    void ApplyPropertyParameter(QWidget* _widget, const char* _property, QVariant _parameter);

    QString SetFont(const QString& _qss);

    QString LoadStyle(const QString& _qssFile);

    QPixmap getDefaultAvatar(const QString& _uin, const QString& _displayName, const int _sizePx, const bool _isFilled);

    std::vector<QStringList> GetPossibleStrings(const QString& _text, unsigned& _count);
    
    QPixmap roundImage(const QPixmap& _img, const QString& _state, bool _isDefault, bool _miniIcons);

    void addShadowToWidget(QWidget* _target);
    void addShadowToWindow(QWidget* _target, bool _enabled = true);

	void grabTouchWidget(QWidget* _target, bool _topWidget = false);

    void removeLineBreaks(QString& _source);

    bool isValidEmailAddress(const QString& _email);

    bool isProbablyPhoneNumber(const QString& _number);

    bool foregroundWndIsFullscreened();

    QColor getSelectionColor();
    QString rgbaStringFromColor(const QColor& _color);

    double fscale_value(const double _px);
    int scale_value(const int _px);
    QSize scale_value(const QSize _px);
    QSizeF scale_value(const QSizeF _px);
    QRect scale_value(const QRect _px);
    int unscale_value(int _px);
    QSize unscale_value(const QSize& _px);
    int scale_bitmap(const int _px);
    int unscale_bitmap(const int _px);
    QSize scale_bitmap(const QSize& _px);
    QSize unscale_bitmap(const QSize& _px);
    QRect scale_bitmap(const QRect& _px);
	int scale_bitmap_with_value(const int _px);
	QSize scale_bitmap_with_value(const QSize& _px);
	QRect scale_bitmap_with_value(const QRect& _px);

    template <typename _T>
    void check_pixel_ratio(_T& _image);

    QString	parse_image_name(const QString& _imageName);
    bool	is_mac_retina();
    void	set_mac_retina(bool _val);
    double	getScaleCoefficient();
    void	setScaleCoefficient(double _coefficient);
    double	getBasicScaleCoefficient();
    void	initBasicScaleCoefficient(double _coefficient);

    void groupTaskbarIcon(bool _enabled);

    bool isStartOnStartup();
    void setStartOnStartup(bool _start);

#ifdef _WIN32
    HWND createFakeParentWindow();
#endif //WIN32

    const uint getInputMaximumChars();

    bool stateEqualsOnline(const QString& _state);

    int calcAge(const QDateTime& _birthdate);

    void initCrashHandlersInCore();

    void drawText(QPainter & painter, const QPointF & point, int flags,
        const QString & text, QRectF * boundingRect = 0);

    const QString &DefaultDownloadsPath();

    bool is_image_extension(const QString& _ext);

    void copyFileToClipboard(const QString& _path);

    bool saveAs(const QString& _inputFilename, QString& _filename, QString& _directory, bool asSheet = true /* for OSX only */);

    typedef std::vector<std::pair<QString, Ui::KeyToSendMessage>> SendKeysIndex;

    const SendKeysIndex& getSendKeysIndex();


    void post_stats_with_settings();
    QRect GetMainRect();
    QPoint GetMainWindowCenter();

    void UpdateProfile(const std::vector<std::pair<std::string, QString>>& _fields);

    QString getItemSafe(const std::vector<QString>& _values, size_t _selected, QString _default);

    Ui::GeneralDialog *NameEditorDialog(
        QWidget* _parent,
        const QString& _chatName,
        const QString& _buttonText,
        const QString& _headerText,
        Out QString& resultChatName,
        bool acceptEnter = true);

    bool NameEditor(
        QWidget* _parent,
        const QString& _chatName,
        const QString& _buttonText,
        const QString& _headerText,
        Out QString& resultChatName,
        bool acceptEnter = true);

    bool GetConfirmationWithTwoButtons(const QString& _buttonLeft, const QString& _buttonRight,
        const QString& _messageText, const QString& _labelText, QWidget* _parent);

    bool GetErrorWithTwoButtons(const QString& _buttonLeftText, const QString& _buttonRightText,
        const QString& _messageText, const QString& _labelText, const QString& _errorText, QWidget* _parent);

    struct ProxySettings
    {
        const static int invalidPort = -1;

        core::proxy_types type_;
        QString username_;
        bool needAuth_;
        QString password_;
        QString proxyServer_;
        int port_;

        ProxySettings(core::proxy_types _type, QString _username, QString _password,
            QString _proxy, int _port, bool _needAuth);

        ProxySettings();

        void postToCore();
    };

    ProxySettings* get_proxy_settings();

    bool loadPixmap(const QString& _path, Out QPixmap& _pixmap);

    bool loadPixmap(const QByteArray& _data, Out QPixmap& _pixmap);

    bool dragUrl(QWidget* _parent, const QPixmap& _preview, const QString& _url);

    bool extractUinFromIcqLink(const QString &_uri, Out QString &_uin);

    class StatsSender : public QObject
    {
        Q_OBJECT
    public :
        StatsSender();

    public Q_SLOTS:
        void recvGuiSettings() { guiSettingsReceived_ = true; trySendStats(); }
        void recvThemeSettings() { themeSettingsReceived_ = true; trySendStats(); }

    public:
        void trySendStats() const;

    private:
        bool guiSettingsReceived_;
        bool themeSettingsReceived_;
    };

    StatsSender* getStatsSender();

    int GetMinWidthOfMainWindow();

    int GetDragDistance();

    bool haveText(const QMimeData *);
}
